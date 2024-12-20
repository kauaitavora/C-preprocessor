use std::{
    fs::{self, File},
    io::{self, BufRead, BufReader, BufWriter, Write},
    env::{self},
};
use regex::Regex;

fn write_line(line: &str, writer: &mut BufWriter<File>, concat: &mut bool, count: &mut usize) {
    
    let mut line_to_write: String = String::new();

    for char in line.chars() {
        if *concat == false {
            if char == '{' {
                *concat = true;
                *count += 1;
            }
            line_to_write.push(char);
        }else{
            line_to_write.push(char);
            if char == '{' {
                *count += 1;
            }else if char == '}' {    
                *count -= 1;
            }
            if *count == 0 {
                line_to_write.push('\n');
                *concat = false;
                break;
            }
        }
    }
    writer.write_all(line_to_write.as_bytes()).expect("could not write line");
}

fn format_line(line: &str) -> Option<String> {

    let special_chars = [' ', '+', '-', '/', '%', '=', '&', '|', '^', '<', '>', ':', '?', '.', ',', ';', '(', ')', '{', '}', '[', ']', '~', '#'];
    let mut chars = line.chars().peekable();
    let mut final_line: String = String::new();
    let mut prev_char: Option<char> = None;

    let line = line.trim();
    if !line.is_empty() {
        while let Some(char) = chars.next() {
            if char == ' ' {
                if let Some(next_char) = chars.peek() {
                    if special_chars.contains(&next_char) {
                        continue;
                    }
                    if prev_char != None && special_chars.contains(&prev_char.unwrap()){
                        continue;
                    } 
                    final_line.push(char)
                }
            }else {
                final_line.push(char);
            }
            prev_char = Some(char);
        }
        return Some(final_line);
    }
    None
}

fn remove_mlcomment(line: &str, is_multiline: &mut bool) -> String {

    let start_pattern = Regex::new(r"\/\*").unwrap();
    let end_pattern = Regex::new(r"\*\/").unwrap();

    if *is_multiline {
        if let Some(end) = end_pattern.find(line) {
            *is_multiline = false;
            return line[end.end()..].to_string();
        }
        return String::new();
    } else {
        if let Some(start) = start_pattern.find(line) {
            if let Some(end) = end_pattern.find(&line[start.end()..]) {
                let before_comment = &line[..start.start()];
                let after_comment = &line[(start.end() + end.end())..];
                return format!("{}{}", before_comment, after_comment);
            } else {
                *is_multiline = true;
                return line[..start.start()].to_string();
            }
        }
    }
    line.to_string()
}

fn remove_slcomment(line: &str) -> String {

    let rgx_pattern = Regex::new(r"\/\/.*").unwrap();
   
    if let Some(capture) = rgx_pattern.captures(line) {
        let comment = capture.get(0).unwrap().as_str();
        return line.replace(comment, "");
    }
    line.to_string()
}

fn get_macro_param(line: &str, start_index: usize) -> &str {
    let mut end_index = 0;
    let mut counter: usize = 0;
               
    for (i, c) in line[start_index..].char_indices() {
        if c == '(' {
            counter += 1;
        }else if c == ')' {
            counter -= 1;
        }
        if counter == 0 {
            end_index = i;
            break;
        }
    }
    return &line[start_index+1..start_index+end_index];
}

fn expand_define(line: String, defines: &Vec<(String, Vec<String>, String)>) -> String {
    for define in defines {
        if let Some(word_start) = line.find(&define.0){  
            let param_start = word_start + define.0.len();
 
            // handle macros
            if line.chars().nth(param_start) != Some('(') {
                // remember to check later if the name is inside double quotes 
                let new_line = line.replace(&define.0, &define.2);
                return expand_define(new_line, defines);
            }
            else {
                
                let param = get_macro_param(&line, param_start);
                let param_vec: Vec<&str> = param.split(",").collect();

                // replacing the content  
                if define.1.len() == param_vec.len() {
                    
                    let mut aux1: String = define.2.clone();

                    for i in 0..define.1.len() {
                        aux1 = aux1.replace(&define.1[i], param_vec[i]);
                    }

                    let full_param = define.0.clone() + "(" + param + ")";
                    let new_line = line.replace(&full_param, &aux1);
                    return expand_define(new_line, defines);
                }
            }
        }
    }
    line
}

fn store_define(mut line: &str) -> (String, Vec<String>, String) {
    
    line = line.strip_prefix("define").expect("").trim_start();
    let mut name: String = String::new();
    let mut name_len: usize = 0;

    for char in line.chars() {
        if char != ' ' && char != '(' {
            name.push(char);
            name_len += 1;
        }else {
            break;
        }
    }

    if line.chars().nth(name_len) != Some('(') {
        let value = line.strip_prefix(name.as_str()).expect("").trim_start().to_string();
        return (name, Vec::new(), value)
    }else {
        let param =  get_macro_param(line, name_len);
        let param_vec: Vec<&str> = param.split(",").collect();
        
        // casting from &str to String   
        let mut param_final_vec: Vec<String> = Vec::new();
        for p in param_vec  {
            param_final_vec.push(p.trim().to_string());
        }

        let value = line.strip_prefix(&(name.clone() + "(" + param + ")")).expect("").trim_start().to_string();
        return (name, param_final_vec, value)   
    }
}

fn get_include_name(line: &str) -> String {
    
    let mut store: bool = false;
    let mut name: String = String::new();
    
    for char in line.chars() {
        if store {
            if char == '>' || char == '"' {
                break;
            }
            name.push(char);
        } else if char == '<' || char == '"' {
            store = true;
        }
    }
    name
}

fn expand_include(writer: &mut BufWriter<File>, line: &str, local_path: &str) -> io::Result<()> {
    
    let dirs: [&str; 4] = [local_path, "/usr/include/", "/usr/local/include/", "/usr/lib/gcc/x86_64-pc-linux-gnu/14.2.1/include"];
    let file_name: String = get_include_name(line);
    
    for dir in dirs {
        let file_path = dir.to_string() + &file_name; 
        if fs::metadata(file_path.clone()).is_ok() {
            let lib_file: File = File::open(file_path).expect("Can't open file");    
            let lib_reader: BufReader<File> = BufReader::new(lib_file);
    
            // copy the include to the original file
            let mut is_multiline = false;
            for line in lib_reader.lines() {
                let mut line = line?;
                line = remove_slcomment(&line);
                line = remove_mlcomment(&line, &mut is_multiline);
                if !line.is_empty() {
                    writeln!(writer, "{}", line)?;
                }

            }
            writer.flush()?;
        }
    }
    Ok(())
}

fn main() -> io::Result<()> {

    // read file  
    let mut args = env::args().skip(1);
    let path = args.next().expect("Can't read arguments");
    let open_file: File = File::open(&path).expect("Can't open file");
    let reader: BufReader<File> = BufReader::new(open_file);
    
    // write file 
    let write_file: File = File::create("output_file/preprocessed.c").expect("Can't create file");
    let mut writer: BufWriter<File> = BufWriter::new(write_file);

    // tuple to store the defines
    let mut defines: Vec<(String, Vec<String>, String)> = Vec::new();
    // flag to check if the comment is multiline 
    let mut is_multiline: bool = false;
    // flag to concatenate lines
    let mut concat: bool = false;
    let mut count: usize = 0;
    
    for line in reader.lines() {
        
        let line: String = line.expect("Can't read line");
        let trimmed_line = line.trim();
        
        // handle includes or defines
        if  !is_multiline {
            if let Some(mut rest_line) = trimmed_line.strip_prefix('#') {
                rest_line = rest_line.trim_start();
                match rest_line.split_whitespace().next() {
                    Some("include") => expand_include(&mut writer, rest_line, &path)?,
                    Some("define") => defines.push(store_define(rest_line)),
                    _ => {}
                }
                continue;
            }
        }

        let mut mod_line = expand_define(trimmed_line.to_string(), &defines);
        mod_line = remove_slcomment(&mod_line);
        mod_line = remove_mlcomment(&mod_line, &mut is_multiline);
        match format_line(&mod_line) {
            Some(final_line) => write_line(&final_line, &mut writer, &mut concat, &mut count),
            None => {},
        }
    }
    Ok(())
}

