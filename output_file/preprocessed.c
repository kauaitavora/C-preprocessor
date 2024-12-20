#ifndef _STDIO_H
#define _STDIO_H	1
#define __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#include <bits/libc-header-start.h>
__BEGIN_DECLS
#define __need_size_t
#define __need_NULL
#include <stddef.h>
#define __need___va_list
#include <stdarg.h>
#include <bits/types.h>
#include <bits/types/__fpos_t.h>
#include <bits/types/__fpos64_t.h>
#include <bits/types/__FILE.h>
#include <bits/types/FILE.h>
#include <bits/types/struct_FILE.h>
#ifdef __USE_MISC
# include <bits/types/cookie_io_functions_t.h>
#endif
#if defined __USE_XOPEN || defined __USE_XOPEN2K8
# ifdef __GNUC__
#  ifndef _VA_LIST_DEFINED
typedef __gnuc_va_list va_list;
#   define _VA_LIST_DEFINED
#  endif
# else
#  include <stdarg.h>
# endif
#endif
#if defined __USE_UNIX98 || defined __USE_XOPEN2K
# ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
# else
typedef __off64_t off_t;
# endif
# define __off_t_defined
# endif
# if defined __USE_LARGEFILE64 && !defined __off64_t_defined
typedef __off64_t off64_t;
# define __off64_t_defined
# endif
#endif
#ifdef __USE_XOPEN2K8
# ifndef __ssize_t_defined
typedef __ssize_t ssize_t;
# define __ssize_t_defined
# endif
#endif
#ifndef __USE_FILE_OFFSET64
typedef __fpos_t fpos_t;
#else
typedef __fpos64_t fpos_t;
#endif
#ifdef __USE_LARGEFILE64
typedef __fpos64_t fpos64_t;
#endif
#define _IOFBF 0		
#define _IOLBF 1		
#define _IONBF 2		
#define BUFSIZ 8192
#define EOF (-1)
#define SEEK_SET	0	
#define SEEK_CUR	1	
#define SEEK_END	2	
#ifdef __USE_GNU
# define SEEK_DATA	3	
# define SEEK_HOLE	4	
#endif
#if defined __USE_MISC || defined __USE_XOPEN
# define P_tmpdir	"/tmp"
#endif
#define L_tmpnam 20
#define TMP_MAX 238328
#include <bits/stdio_lim.h>
#ifdef __USE_POSIX
# define L_ctermid 9
# if !defined __USE_XOPEN2K || defined __USE_GNU
#  define L_cuserid 9
# endif
#endif
#undef  FOPEN_MAX
#define FOPEN_MAX 16
#if __GLIBC_USE (ISOC23)
# define _PRINTF_NAN_LEN_MAX 4
#endif
extern FILE *stdin;		
extern FILE *stdout;		
extern FILE *stderr;		
#define stdin stdin
#define stdout stdout
#define stderr stderr
extern int remove (const char *__filename) __THROW;
extern int rename (const char *__old, const char *__new) __THROW;
#ifdef __USE_ATFILE
extern int renameat (int __oldfd, const char *__old, int __newfd,
		     const char *__new) __THROW;
#endif
#ifdef __USE_GNU
# define RENAME_NOREPLACE (1 << 0)
# define RENAME_EXCHANGE (1 << 1)
# define RENAME_WHITEOUT (1 << 2)
extern int renameat2 (int __oldfd, const char *__old, int __newfd,
		      const char *__new, unsigned int __flags) __THROW;
#endif
extern int fclose (FILE *__stream) __nonnull ((1));
#undef __attr_dealloc_fclose
#define __attr_dealloc_fclose __attr_dealloc (fclose, 1)
#ifndef __USE_FILE_OFFSET64
extern FILE *tmpfile (void)
  __attribute_malloc__ __attr_dealloc_fclose __wur;
#else
# ifdef __REDIRECT
extern FILE *__REDIRECT (tmpfile, (void), tmpfile64)
  __attribute_malloc__ __attr_dealloc_fclose __wur;
# else
#  define tmpfile tmpfile64
# endif
#endif
#ifdef __USE_LARGEFILE64
extern FILE *tmpfile64 (void)
   __attribute_malloc__ __attr_dealloc_fclose __wur;
#endif
extern char *tmpnam (char[L_tmpnam]) __THROW __wur;
#ifdef __USE_MISC
extern char *tmpnam_r (char __s[L_tmpnam]) __THROW __wur;
#endif
#if defined __USE_MISC || defined __USE_XOPEN
extern char *tempnam (const char *__dir, const char *__pfx)
   __THROW __attribute_malloc__ __wur __attr_dealloc_free;
#endif
extern int fflush (FILE *__stream);
#ifdef __USE_MISC
extern int fflush_unlocked (FILE *__stream);
#endif
#ifdef __USE_GNU
extern int fcloseall (void);
#endif
#ifndef __USE_FILE_OFFSET64
extern FILE *fopen (const char *__restrict __filename,
		    const char *__restrict __modes)
  __attribute_malloc__ __attr_dealloc_fclose __wur;
extern FILE *freopen (const char *__restrict __filename,
		      const char *__restrict __modes,
		      FILE *__restrict __stream) __wur __nonnull ((3));
#else
# ifdef __REDIRECT
extern FILE *__REDIRECT (fopen, (const char *__restrict __filename,
				 const char *__restrict __modes), fopen64)
  __attribute_malloc__ __attr_dealloc_fclose __wur;
extern FILE *__REDIRECT (freopen, (const char *__restrict __filename,
				   const char *__restrict __modes,
				   FILE *__restrict __stream), freopen64)
  __wur __nonnull ((3));
# else
#  define fopen fopen64
#  define freopen freopen64
# endif
#endif
#ifdef __USE_LARGEFILE64
extern FILE *fopen64 (const char *__restrict __filename,
		      const char *__restrict __modes)
  __attribute_malloc__ __attr_dealloc_fclose __wur;
extern FILE *freopen64 (const char *__restrict __filename,
			const char *__restrict __modes,
			FILE *__restrict __stream) __wur __nonnull ((3));
#endif
#ifdef	__USE_POSIX
extern FILE *fdopen (int __fd, const char *__modes) __THROW
  __attribute_malloc__ __attr_dealloc_fclose __wur;
#endif
#ifdef	__USE_MISC
extern FILE *fopencookie (void *__restrict __magic_cookie,
			  const char *__restrict __modes,
			  cookie_io_functions_t __io_funcs) __THROW
  __attribute_malloc__ __attr_dealloc_fclose __wur;
#endif
#if defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2)
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __THROW __attribute_malloc__ __attr_dealloc_fclose __wur;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __THROW
  __attribute_malloc__ __attr_dealloc_fclose __wur;
#ifdef _WCHAR_H
extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) __THROW
  __attribute_malloc__ __attr_dealloc_fclose;
# endif
#endif
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __THROW
  __nonnull ((1));
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
		    int __modes, size_t __n) __THROW __nonnull ((1));
#ifdef	__USE_MISC
extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
		       size_t __size) __THROW __nonnull ((1));
extern void setlinebuf (FILE *__stream) __THROW __nonnull ((1));
#endif
extern int fprintf (FILE *__restrict __stream,
		    const char *__restrict __format, ...) __nonnull ((1));
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
		    const char *__restrict __format, ...) __THROWNL;
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
		     __gnuc_va_list __arg) __nonnull ((1));
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
		     __gnuc_va_list __arg) __THROWNL;
#if defined __USE_ISOC99 || defined __USE_UNIX98
extern int snprintf (char *__restrict __s, size_t __maxlen,
		     const char *__restrict __format, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
		      const char *__restrict __format, __gnuc_va_list __arg)
     __THROWNL __attribute__ ((__format__ (__printf__, 3, 0)));
#endif
#if defined (__USE_MISC) || __GLIBC_USE (LIB_EXT2)
extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
		      __gnuc_va_list __arg)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 0))) __wur;
extern int __asprintf (char **__restrict __ptr,
		       const char *__restrict __fmt, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 3))) __wur;
extern int asprintf (char **__restrict __ptr,
		     const char *__restrict __fmt, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 3))) __wur;
#endif
#ifdef __USE_XOPEN2K8
extern int vdprintf (int __fd, const char *__restrict __fmt,
		     __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));
#endif
extern int fscanf (FILE *__restrict __stream,
		   const char *__restrict __format, ...) __wur __nonnull ((1));
extern int scanf (const char *__restrict __format, ...) __wur;
extern int sscanf (const char *__restrict __s,
		   const char *__restrict __format, ...) __THROW;
#include <bits/floatn.h>
#if !__GLIBC_USE (DEPRECATED_SCANF) && !defined __LDBL_COMPAT \
    && __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI == 0
# if __GLIBC_USE (C23_STRTOL)
#  ifdef __REDIRECT
extern int __REDIRECT (fscanf, (FILE *__restrict __stream,
				const char *__restrict __format, ...),
		       __isoc23_fscanf) __wur __nonnull ((1));
extern int __REDIRECT (scanf, (const char *__restrict __format, ...),
		       __isoc23_scanf) __wur;
extern int __REDIRECT_NTH (sscanf, (const char *__restrict __s,
				    const char *__restrict __format, ...),
			   __isoc23_sscanf);
#  else
extern int __isoc23_fscanf (FILE *__restrict __stream,
			    const char *__restrict __format, ...) __wur
  __nonnull ((1));
extern int __isoc23_scanf (const char *__restrict __format, ...) __wur;
extern int __isoc23_sscanf (const char *__restrict __s,
			    const char *__restrict __format, ...) __THROW;
#   define fscanf __isoc23_fscanf
#   define scanf __isoc23_scanf
#   define sscanf __isoc23_sscanf
#  endif
# else
#  ifdef __REDIRECT
extern int __REDIRECT (fscanf, (FILE *__restrict __stream,
				const char *__restrict __format, ...),
		       __isoc99_fscanf) __wur __nonnull ((1));
extern int __REDIRECT (scanf, (const char *__restrict __format, ...),
		       __isoc99_scanf) __wur;
extern int __REDIRECT_NTH (sscanf, (const char *__restrict __s,
				    const char *__restrict __format, ...),
			   __isoc99_sscanf);
#  else
extern int __isoc99_fscanf (FILE *__restrict __stream,
			    const char *__restrict __format, ...) __wur
  __nonnull ((1));
extern int __isoc99_scanf (const char *__restrict __format, ...) __wur;
extern int __isoc99_sscanf (const char *__restrict __s,
			    const char *__restrict __format, ...) __THROW;
#   define fscanf __isoc99_fscanf
#   define scanf __isoc99_scanf
#   define sscanf __isoc99_sscanf
#  endif
# endif
#endif
#ifdef	__USE_ISOC99
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
		    __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __wur __nonnull ((1));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) __wur;
extern int vsscanf (const char *__restrict __s,
		    const char *__restrict __format, __gnuc_va_list __arg)
     __THROW __attribute__ ((__format__ (__scanf__, 2, 0)));
# if !__GLIBC_USE (DEPRECATED_SCANF)
#  if __GLIBC_USE (C23_STRTOL)
#   if defined __REDIRECT && !defined __LDBL_COMPAT	\
      && __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI == 0
extern int __REDIRECT (vfscanf,
		       (FILE *__restrict __s,
			const char *__restrict __format, __gnuc_va_list __arg),
		       __isoc23_vfscanf)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __wur __nonnull ((1));
extern int __REDIRECT (vscanf, (const char *__restrict __format,
				__gnuc_va_list __arg), __isoc23_vscanf)
     __attribute__ ((__format__ (__scanf__, 1, 0))) __wur;
extern int __REDIRECT_NTH (vsscanf,
			   (const char *__restrict __s,
			    const char *__restrict __format,
			    __gnuc_va_list __arg), __isoc23_vsscanf)
     __attribute__ ((__format__ (__scanf__, 2, 0)));
#   elif !defined __REDIRECT
extern int __isoc23_vfscanf (FILE *__restrict __s,
			     const char *__restrict __format,
			     __gnuc_va_list __arg) __wur __nonnull ((1));
extern int __isoc23_vscanf (const char *__restrict __format,
			    __gnuc_va_list __arg) __wur;
extern int __isoc23_vsscanf (const char *__restrict __s,
			     const char *__restrict __format,
			     __gnuc_va_list __arg) __THROW;
#    define vfscanf __isoc23_vfscanf
#    define vscanf __isoc23_vscanf
#    define vsscanf __isoc23_vsscanf
#   endif
#  else
#   if defined __REDIRECT && !defined __LDBL_COMPAT	\
      && __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI == 0
extern int __REDIRECT (vfscanf,
		       (FILE *__restrict __s,
			const char *__restrict __format, __gnuc_va_list __arg),
		       __isoc99_vfscanf)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __wur __nonnull ((1));
extern int __REDIRECT (vscanf, (const char *__restrict __format,
				__gnuc_va_list __arg), __isoc99_vscanf)
     __attribute__ ((__format__ (__scanf__, 1, 0))) __wur;
extern int __REDIRECT_NTH (vsscanf,
			   (const char *__restrict __s,
			    const char *__restrict __format,
			    __gnuc_va_list __arg), __isoc99_vsscanf)
     __attribute__ ((__format__ (__scanf__, 2, 0)));
#   elif !defined __REDIRECT
extern int __isoc99_vfscanf (FILE *__restrict __s,
			     const char *__restrict __format,
			     __gnuc_va_list __arg) __wur __nonnull ((1));
extern int __isoc99_vscanf (const char *__restrict __format,
			    __gnuc_va_list __arg) __wur;
extern int __isoc99_vsscanf (const char *__restrict __s,
			     const char *__restrict __format,
			     __gnuc_va_list __arg) __THROW;
#    define vfscanf __isoc99_vfscanf
#    define vscanf __isoc99_vscanf
#    define vsscanf __isoc99_vsscanf
#   endif
#  endif
# endif
#endif 
extern int fgetc (FILE *__stream) __nonnull ((1));
extern int getc (FILE *__stream) __nonnull ((1));
extern int getchar (void);
#ifdef __USE_POSIX199506
extern int getc_unlocked (FILE *__stream) __nonnull ((1));
extern int getchar_unlocked (void);
#endif 
#ifdef __USE_MISC
extern int fgetc_unlocked (FILE *__stream) __nonnull ((1));
#endif 
extern int fputc (int __c, FILE *__stream) __nonnull ((2));
extern int putc (int __c, FILE *__stream) __nonnull ((2));
extern int putchar (int __c);
#ifdef __USE_MISC
extern int fputc_unlocked (int __c, FILE *__stream) __nonnull ((2));
#endif 
#ifdef __USE_POSIX199506
extern int putc_unlocked (int __c, FILE *__stream) __nonnull ((2));
extern int putchar_unlocked (int __c);
#endif 
#if defined __USE_MISC \
    || (defined __USE_XOPEN && !defined __USE_XOPEN2K)
extern int getw (FILE *__stream) __nonnull ((1));
extern int putw (int __w, FILE *__stream) __nonnull ((2));
#endif
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __wur __fortified_attr_access (__write_only__, 1, 2) __nonnull ((3));
#if __GLIBC_USE (DEPRECATED_GETS)
extern char *gets (char *__s) __wur __attribute_deprecated__;
#endif
#ifdef __USE_GNU
extern char *fgets_unlocked (char *__restrict __s, int __n,
			     FILE *__restrict __stream) __wur
    __fortified_attr_access (__write_only__, 1, 2) __nonnull ((3));
#endif
#if defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2)
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) __wur __nonnull ((4));
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) __wur __nonnull ((4));
extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) __wur __nonnull ((3));
#endif
extern int fputs (const char *__restrict __s, FILE *__restrict __stream)
  __nonnull ((2));
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream) __nonnull ((2));
extern size_t fread (void *__restrict __ptr, size_t __size,
		     size_t __n, FILE *__restrict __stream) __wur
  __nonnull((4));
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
		      size_t __n, FILE *__restrict __s) __nonnull((4));
#ifdef __USE_GNU
extern int fputs_unlocked (const char *__restrict __s,
			   FILE *__restrict __stream) __nonnull ((2));
#endif
#ifdef __USE_MISC
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
			      size_t __n, FILE *__restrict __stream) __wur
  __nonnull ((4));
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
			       size_t __n, FILE *__restrict __stream)
  __nonnull ((4));
#endif
extern int fseek (FILE *__stream, long int __off, int __whence)
  __nonnull ((1));
extern long int ftell (FILE *__stream) __wur __nonnull ((1));
extern void rewind (FILE *__stream) __nonnull ((1));
#if defined __USE_LARGEFILE || defined __USE_XOPEN2K
# ifndef __USE_FILE_OFFSET64
extern int fseeko (FILE *__stream, __off_t __off, int __whence)
  __nonnull ((1));
extern __off_t ftello (FILE *__stream) __wur __nonnull ((1));
# else
#  ifdef __REDIRECT
extern int __REDIRECT (fseeko,
		       (FILE *__stream, __off64_t __off, int __whence),
		       fseeko64) __nonnull ((1));
extern __off64_t __REDIRECT (ftello, (FILE *__stream), ftello64)
  __nonnull ((1));
#  else
#   define fseeko fseeko64
#   define ftello ftello64
#  endif
# endif
#endif
#ifndef __USE_FILE_OFFSET64
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos)
  __nonnull ((1));
extern int fsetpos (FILE *__stream, const fpos_t *__pos) __nonnull ((1));
#else
# ifdef __REDIRECT
extern int __REDIRECT (fgetpos, (FILE *__restrict __stream,
				 fpos_t *__restrict __pos), fgetpos64)
  __nonnull ((1));
extern int __REDIRECT (fsetpos,
		       (FILE *__stream, const fpos_t *__pos), fsetpos64)
  __nonnull ((1));
# else
#  define fgetpos fgetpos64
#  define fsetpos fsetpos64
# endif
#endif
#ifdef __USE_LARGEFILE64
extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence)
  __nonnull ((1));
extern __off64_t ftello64 (FILE *__stream) __wur __nonnull ((1));
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos)
  __nonnull ((1));
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos) __nonnull ((1));
#endif
extern void clearerr (FILE *__stream) __THROW __nonnull ((1));
extern int feof (FILE *__stream) __THROW __wur __nonnull ((1));
extern int ferror (FILE *__stream) __THROW __wur __nonnull ((1));
#ifdef __USE_MISC
extern void clearerr_unlocked (FILE *__stream) __THROW __nonnull ((1));
extern int feof_unlocked (FILE *__stream) __THROW __wur __nonnull ((1));
extern int ferror_unlocked (FILE *__stream) __THROW __wur __nonnull ((1));
#endif
extern void perror (const char *__s) __COLD;
#ifdef	__USE_POSIX
extern int fileno (FILE *__stream) __THROW __wur __nonnull ((1));
#endif 
#ifdef __USE_MISC
extern int fileno_unlocked (FILE *__stream) __THROW __wur __nonnull ((1));
#endif
#ifdef __USE_POSIX2
extern int pclose (FILE *__stream) __nonnull ((1));
extern FILE *popen (const char *__command, const char *__modes)
  __attribute_malloc__ __attr_dealloc (pclose, 1) __wur;
#endif
#ifdef	__USE_POSIX
extern char *ctermid (char *__s) __THROW
  __attr_access ((__write_only__, 1));
#endif 
#if (defined __USE_XOPEN && !defined __USE_XOPEN2K) || defined __USE_GNU
extern char *cuserid (char *__s)
  __attr_access ((__write_only__, 1));
#endif 
#ifdef	__USE_GNU
struct obstack;			
extern int obstack_printf (struct obstack *__restrict __obstack,
			   const char *__restrict __format, ...)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
			    const char *__restrict __format,
			    __gnuc_va_list __args)
     __THROWNL __attribute__ ((__format__ (__printf__, 2, 0)));
#endif 
#ifdef __USE_POSIX199506
extern void flockfile (FILE *__stream) __THROW __nonnull ((1));
extern int ftrylockfile (FILE *__stream) __THROW __wur __nonnull ((1));
extern void funlockfile (FILE *__stream) __THROW __nonnull ((1));
#endif 
#if defined __USE_XOPEN && !defined __USE_XOPEN2K && !defined __USE_GNU
# include <bits/getopt_posix.h>
#endif
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
# include <bits/stdio2-decl.h>
#endif
#if defined __LDBL_COMPAT || __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI == 1
# include <bits/stdio-ldbl.h>
#endif
#ifdef __USE_EXTERN_INLINES
# include <bits/stdio.h>
#endif
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
# include <bits/stdio2.h>
#endif
__END_DECLS
#endif 
#ifndef	_STDLIB_H
#define __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#include <bits/libc-header-start.h>
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#include <stddef.h>
__BEGIN_DECLS
#define	_STDLIB_H	1
#if (defined __USE_XOPEN || defined __USE_XOPEN2K8) && !defined _SYS_WAIT_H
# include <bits/waitflags.h>
# include <bits/waitstatus.h>
# define WEXITSTATUS(status)	__WEXITSTATUS (status)
# define WTERMSIG(status)	__WTERMSIG (status)
# define WSTOPSIG(status)	__WSTOPSIG (status)
# define WIFEXITED(status)	__WIFEXITED (status)
# define WIFSIGNALED(status)	__WIFSIGNALED (status)
# define WIFSTOPPED(status)	__WIFSTOPPED (status)
# ifdef __WIFCONTINUED
#  define WIFCONTINUED(status)	__WIFCONTINUED (status)
# endif
#endif	
#include <bits/floatn.h>
typedef struct
  {
    int quot;			
    int rem;			
  } div_t;
#ifndef __ldiv_t_defined
typedef struct
  {
    long int quot;		
    long int rem;		
  } ldiv_t;
# define __ldiv_t_defined	1
#endif
#if defined __USE_ISOC99 && !defined __lldiv_t_defined
__extension__ typedef struct
  {
    long long int quot;		
    long long int rem;		
  } lldiv_t;
# define __lldiv_t_defined	1
#endif
#define	RAND_MAX	2147483647
#define	EXIT_FAILURE	1	
#define	EXIT_SUCCESS	0	
#define	MB_CUR_MAX	(__ctype_get_mb_cur_max ())
extern size_t __ctype_get_mb_cur_max (void) __THROW __wur;
extern double atof (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
extern int atoi (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
extern long int atol (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
#ifdef __USE_ISOC99
__extension__ extern long long int atoll (const char *__nptr)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
#endif
extern double strtod (const char *__restrict __nptr,
		      char **__restrict __endptr)
     __THROW __nonnull ((1));
#ifdef	__USE_ISOC99
extern float strtof (const char *__restrict __nptr,
		     char **__restrict __endptr) __THROW __nonnull ((1));
extern long double strtold (const char *__restrict __nptr,
			    char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT16 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float16 strtof16 (const char *__restrict __nptr,
			  char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT32 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float32 strtof32 (const char *__restrict __nptr,
			  char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT64 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float64 strtof64 (const char *__restrict __nptr,
			  char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT128 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float128 strtof128 (const char *__restrict __nptr,
			    char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT32X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float32x strtof32x (const char *__restrict __nptr,
			    char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT64X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float64x strtof64x (const char *__restrict __nptr,
			    char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
#if __HAVE_FLOAT128X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern _Float128x strtof128x (const char *__restrict __nptr,
			      char **__restrict __endptr)
     __THROW __nonnull ((1));
#endif
extern long int strtol (const char *__restrict __nptr,
			char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
extern unsigned long int strtoul (const char *__restrict __nptr,
				  char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
#ifdef __USE_MISC
__extension__
extern long long int strtoq (const char *__restrict __nptr,
			     char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
				       char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
#endif 
#ifdef __USE_ISOC99
__extension__
extern long long int strtoll (const char *__restrict __nptr,
			      char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
					char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
#endif 
#if __GLIBC_USE (C23_STRTOL)
# ifdef __REDIRECT
extern long int __REDIRECT_NTH (strtol, (const char *__restrict __nptr,
					 char **__restrict __endptr,
					 int __base), __isoc23_strtol)
     __nonnull ((1));
extern unsigned long int __REDIRECT_NTH (strtoul,
					 (const char *__restrict __nptr,
					  char **__restrict __endptr,
					  int __base), __isoc23_strtoul)
     __nonnull ((1));
#  ifdef __USE_MISC
__extension__
extern long long int __REDIRECT_NTH (strtoq, (const char *__restrict __nptr,
					      char **__restrict __endptr,
					      int __base), __isoc23_strtoll)
     __nonnull ((1));
__extension__
extern unsigned long long int __REDIRECT_NTH (strtouq,
					      (const char *__restrict __nptr,
					       char **__restrict __endptr,
					       int __base), __isoc23_strtoull)
     __nonnull ((1));
#  endif
__extension__
extern long long int __REDIRECT_NTH (strtoll, (const char *__restrict __nptr,
					       char **__restrict __endptr,
					       int __base), __isoc23_strtoll)
     __nonnull ((1));
__extension__
extern unsigned long long int __REDIRECT_NTH (strtoull,
					      (const char *__restrict __nptr,
					       char **__restrict __endptr,
					       int __base), __isoc23_strtoull)
     __nonnull ((1));
# else
extern long int __isoc23_strtol (const char *__restrict __nptr,
				 char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
extern unsigned long int __isoc23_strtoul (const char *__restrict __nptr,
					   char **__restrict __endptr,
					   int __base)
     __THROW __nonnull ((1));
__extension__
extern long long int __isoc23_strtoll (const char *__restrict __nptr,
				       char **__restrict __endptr, int __base)
     __THROW __nonnull ((1));
__extension__
extern unsigned long long int __isoc23_strtoull (const char *__restrict __nptr,
						 char **__restrict __endptr,
						 int __base)
     __THROW __nonnull ((1));
#  define strtol __isoc23_strtol
#  define strtoul __isoc23_strtoul
#  ifdef __USE_MISC
#   define strtoq __isoc23_strtoll
#   define strtouq __isoc23_strtoull
#  endif
#  define strtoll __isoc23_strtoll
#  define strtoull __isoc23_strtoull
# endif
#endif
#if __GLIBC_USE (IEC_60559_BFP_EXT_C23)
extern int strfromd (char *__dest, size_t __size, const char *__format,
		     double __f)
     __THROW __nonnull ((3));
extern int strfromf (char *__dest, size_t __size, const char *__format,
		     float __f)
     __THROW __nonnull ((3));
extern int strfroml (char *__dest, size_t __size, const char *__format,
		     long double __f)
     __THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT16 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf16 (char *__dest, size_t __size, const char * __format,
		       _Float16 __f)
     __THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT32 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf32 (char *__dest, size_t __size, const char * __format,
		       _Float32 __f)
     __THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT64 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf64 (char *__dest, size_t __size, const char * __format,
		       _Float64 __f)
     __THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT128 && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf128 (char *__dest, size_t __size, const char * __format,
			_Float128 __f)
     __THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT32X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf32x (char *__dest, size_t __size, const char * __format,
			_Float32x __f)
     __THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT64X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf64x (char *__dest, size_t __size, const char * __format,
			_Float64x __f)
     __THROW __nonnull ((3));
#endif
#if __HAVE_FLOAT128X && __GLIBC_USE (IEC_60559_TYPES_EXT)
extern int strfromf128x (char *__dest, size_t __size, const char * __format,
			 _Float128x __f)
     __THROW __nonnull ((3));
#endif
#ifdef __USE_GNU
# include <bits/types/locale_t.h>
extern long int strtol_l (const char *__restrict __nptr,
			  char **__restrict __endptr, int __base,
			  locale_t __loc) __THROW __nonnull ((1, 4));
extern unsigned long int strtoul_l (const char *__restrict __nptr,
				    char **__restrict __endptr,
				    int __base, locale_t __loc)
     __THROW __nonnull ((1, 4));
__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
				char **__restrict __endptr, int __base,
				locale_t __loc)
     __THROW __nonnull ((1, 4));
__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
					  char **__restrict __endptr,
					  int __base, locale_t __loc)
     __THROW __nonnull ((1, 4));
# if __GLIBC_USE (C23_STRTOL)
#  ifdef __REDIRECT
extern long int __REDIRECT_NTH (strtol_l, (const char *__restrict __nptr,
					   char **__restrict __endptr,
					   int __base, locale_t __loc),
				__isoc23_strtol_l)
     __nonnull ((1, 4));
extern unsigned long int __REDIRECT_NTH (strtoul_l,
					 (const char *__restrict __nptr,
					  char **__restrict __endptr,
					  int __base, locale_t __loc),
					 __isoc23_strtoul_l)
     __nonnull ((1, 4));
__extension__
extern long long int __REDIRECT_NTH (strtoll_l, (const char *__restrict __nptr,
						 char **__restrict __endptr,
						 int __base,
						 locale_t __loc),
				     __isoc23_strtoll_l)
     __nonnull ((1, 4));
__extension__
extern unsigned long long int __REDIRECT_NTH (strtoull_l,
					      (const char *__restrict __nptr,
					       char **__restrict __endptr,
					       int __base, locale_t __loc),
					      __isoc23_strtoull_l)
     __nonnull ((1, 4));
#  else
extern long int __isoc23_strtol_l (const char *__restrict __nptr,
				   char **__restrict __endptr, int __base,
				   locale_t __loc) __THROW __nonnull ((1, 4));
extern unsigned long int __isoc23_strtoul_l (const char *__restrict __nptr,
					     char **__restrict __endptr,
					     int __base, locale_t __loc)
     __THROW __nonnull ((1, 4));
__extension__
extern long long int __isoc23_strtoll_l (const char *__restrict __nptr,
					 char **__restrict __endptr,
					 int __base, locale_t __loc)
     __THROW __nonnull ((1, 4));
__extension__
extern unsigned long long int __isoc23_strtoull_l (const char *__restrict __nptr,
						   char **__restrict __endptr,
						   int __base, locale_t __loc)
     __THROW __nonnull ((1, 4));
#   define strtol_l __isoc23_strtol_l
#   define strtoul_l __isoc23_strtoul_l
#   define strtoll_l __isoc23_strtoll_l
#   define strtoull_l __isoc23_strtoull_l
#  endif
# endif
extern double strtod_l (const char *__restrict __nptr,
			char **__restrict __endptr, locale_t __loc)
     __THROW __nonnull ((1, 3));
extern float strtof_l (const char *__restrict __nptr,
		       char **__restrict __endptr, locale_t __loc)
     __THROW __nonnull ((1, 3));
extern long double strtold_l (const char *__restrict __nptr,
			      char **__restrict __endptr,
			      locale_t __loc)
     __THROW __nonnull ((1, 3));
# if __HAVE_FLOAT16
extern _Float16 strtof16_l (const char *__restrict __nptr,
			    char **__restrict __endptr,
			    locale_t __loc)
     __THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT32
extern _Float32 strtof32_l (const char *__restrict __nptr,
			    char **__restrict __endptr,
			    locale_t __loc)
     __THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT64
extern _Float64 strtof64_l (const char *__restrict __nptr,
			    char **__restrict __endptr,
			    locale_t __loc)
     __THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT128
extern _Float128 strtof128_l (const char *__restrict __nptr,
			      char **__restrict __endptr,
			      locale_t __loc)
     __THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT32X
extern _Float32x strtof32x_l (const char *__restrict __nptr,
			      char **__restrict __endptr,
			      locale_t __loc)
     __THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT64X
extern _Float64x strtof64x_l (const char *__restrict __nptr,
			      char **__restrict __endptr,
			      locale_t __loc)
     __THROW __nonnull ((1, 3));
# endif
# if __HAVE_FLOAT128X
extern _Float128x strtof128x_l (const char *__restrict __nptr,
				char **__restrict __endptr,
				locale_t __loc)
     __THROW __nonnull ((1, 3));
# endif
#endif 
#ifdef __USE_EXTERN_INLINES
__extern_inline int
__NTH (atoi (const char *__nptr))
{
  return (int) strtol (__nptr, (char **) NULL, 10);
}
__extern_inline long int
__NTH (atol (const char *__nptr))
{
  return strtol (__nptr, (char **) NULL, 10);
}
# ifdef __USE_ISOC99
__extension__ __extern_inline long long int
__NTH (atoll (const char *__nptr))
{
  return strtoll (__nptr, (char **) NULL, 10);
}
# endif
#endif 
#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
extern char *l64a (long int __n) __THROW __wur;
extern long int a64l (const char *__s)
     __THROW __attribute_pure__ __nonnull ((1)) __wur;
#endif	
#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
# include <sys/types.h>	
extern long int random (void) __THROW;
extern void srandom (unsigned int __seed) __THROW;
extern char *initstate (unsigned int __seed, char *__statebuf,
			size_t __statelen) __THROW __nonnull ((2));
extern char *setstate (char *__statebuf) __THROW __nonnull ((1));
# ifdef __USE_MISC
struct random_data
  {
    int32_t *fptr;		
    int32_t *rptr;		
    int32_t *state;		
    int rand_type;		
    int rand_deg;		
    int rand_sep;		
    int32_t *end_ptr;		
  };
extern int random_r (struct random_data *__restrict __buf,
		     int32_t *__restrict __result) __THROW __nonnull ((1, 2));
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __THROW __nonnull ((2));
extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
			size_t __statelen,
			struct random_data *__restrict __buf)
     __THROW __nonnull ((2, 4));
extern int setstate_r (char *__restrict __statebuf,
		       struct random_data *__restrict __buf)
     __THROW __nonnull ((1, 2));
# endif	
#endif	
extern int rand (void) __THROW;
extern void srand (unsigned int __seed) __THROW;
#ifdef __USE_POSIX199506
extern int rand_r (unsigned int *__seed) __THROW;
#endif
#if defined __USE_MISC || defined __USE_XOPEN
extern double drand48 (void) __THROW;
extern double erand48 (unsigned short int __xsubi[3]) __THROW __nonnull ((1));
extern long int lrand48 (void) __THROW;
extern long int nrand48 (unsigned short int __xsubi[3])
     __THROW __nonnull ((1));
extern long int mrand48 (void) __THROW;
extern long int jrand48 (unsigned short int __xsubi[3])
     __THROW __nonnull ((1));
extern void srand48 (long int __seedval) __THROW;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __THROW __nonnull ((1));
extern void lcong48 (unsigned short int __param[7]) __THROW __nonnull ((1));
# ifdef __USE_MISC
struct drand48_data
  {
    unsigned short int __x[3];	
    unsigned short int __old_x[3]; 
    unsigned short int __c;	
    unsigned short int __init;	
    __extension__ unsigned long long int __a;	
  };
extern int drand48_r (struct drand48_data *__restrict __buffer,
		      double *__restrict __result) __THROW __nonnull ((1, 2));
extern int erand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      double *__restrict __result) __THROW __nonnull ((1, 2));
extern int lrand48_r (struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));
extern int nrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));
extern int mrand48_r (struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));
extern int jrand48_r (unsigned short int __xsubi[3],
		      struct drand48_data *__restrict __buffer,
		      long int *__restrict __result)
     __THROW __nonnull ((1, 2));
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __THROW __nonnull ((2));
extern int seed48_r (unsigned short int __seed16v[3],
		     struct drand48_data *__buffer) __THROW __nonnull ((1, 2));
extern int lcong48_r (unsigned short int __param[7],
		      struct drand48_data *__buffer)
     __THROW __nonnull ((1, 2));
extern __uint32_t arc4random (void)
     __THROW __wur;
extern void arc4random_buf (void *__buf, size_t __size)
     __THROW __nonnull ((1));
extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
     __THROW __wur;
# endif	
#endif	
extern void *malloc (size_t __size) __THROW __attribute_malloc__
     __attribute_alloc_size__ ((1)) __wur;
extern void *calloc (size_t __nmemb, size_t __size)
     __THROW __attribute_malloc__ __attribute_alloc_size__ ((1, 2)) __wur;
extern void *realloc (void *__ptr, size_t __size)
     __THROW __attribute_warn_unused_result__ __attribute_alloc_size__ ((2));
extern void free (void *__ptr) __THROW;
#ifdef __USE_MISC
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __THROW __attribute_warn_unused_result__
     __attribute_alloc_size__ ((2, 3))
    __attr_dealloc_free;
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __THROW __attr_dealloc (reallocarray, 1);
#endif
#ifdef __USE_MISC
# include <alloca.h>
#endif 
#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K) \
    || defined __USE_MISC
extern void *valloc (size_t __size) __THROW __attribute_malloc__
     __attribute_alloc_size__ ((1)) __wur;
#endif
#ifdef __USE_XOPEN2K
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __THROW __nonnull ((1)) __wur;
#endif
#ifdef __USE_ISOC11
extern void *aligned_alloc (size_t __alignment, size_t __size)
     __THROW __attribute_malloc__ __attribute_alloc_align__ ((1))
     __attribute_alloc_size__ ((2)) __wur;
#endif
extern void abort (void) __THROW __attribute__ ((__noreturn__));
extern int atexit (void (*__func) (void)) __THROW __nonnull ((1));
#if defined __USE_ISOC11 || defined __USE_ISOCXX11
# ifdef __cplusplus
extern "C++" int at_quick_exit (void (*__func) (void))
     __THROW __asm ("at_quick_exit") __nonnull ((1));
# else
extern int at_quick_exit (void (*__func) (void)) __THROW __nonnull ((1));
# endif
#endif
#ifdef	__USE_MISC
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __THROW __nonnull ((1));
#endif
extern void exit (int __status) __THROW __attribute__ ((__noreturn__));
#if defined __USE_ISOC11 || defined __USE_ISOCXX11
extern void quick_exit (int __status) __THROW __attribute__ ((__noreturn__));
#endif
#ifdef __USE_ISOC99
extern void _Exit (int __status) __THROW __attribute__ ((__noreturn__));
#endif
extern char *getenv (const char *__name) __THROW __nonnull ((1)) __wur;
#ifdef __USE_GNU
extern char *secure_getenv (const char *__name)
     __THROW __nonnull ((1)) __wur;
#endif
#if defined __USE_MISC || defined __USE_XOPEN
extern int putenv (char *__string) __THROW __nonnull ((1));
#endif
#ifdef __USE_XOPEN2K
extern int setenv (const char *__name, const char *__value, int __replace)
     __THROW __nonnull ((2));
extern int unsetenv (const char *__name) __THROW __nonnull ((1));
#endif
#ifdef	__USE_MISC
extern int clearenv (void) __THROW;
#endif
#if defined __USE_MISC \
    || (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8)
extern char *mktemp (char *__template) __THROW __nonnull ((1));
#endif
#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
# ifndef __USE_FILE_OFFSET64
extern int mkstemp (char *__template) __nonnull ((1)) __wur;
# else
#  ifdef __REDIRECT
extern int __REDIRECT (mkstemp, (char *__template), mkstemp64)
     __nonnull ((1)) __wur;
#  else
#   define mkstemp mkstemp64
#  endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkstemp64 (char *__template) __nonnull ((1)) __wur;
# endif
#endif
#ifdef __USE_MISC
# ifndef __USE_FILE_OFFSET64
extern int mkstemps (char *__template, int __suffixlen) __nonnull ((1)) __wur;
# else
#  ifdef __REDIRECT
extern int __REDIRECT (mkstemps, (char *__template, int __suffixlen),
		       mkstemps64) __nonnull ((1)) __wur;
#  else
#   define mkstemps mkstemps64
#  endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkstemps64 (char *__template, int __suffixlen)
     __nonnull ((1)) __wur;
# endif
#endif
#ifdef __USE_XOPEN2K8
extern char *mkdtemp (char *__template) __THROW __nonnull ((1)) __wur;
#endif
#ifdef __USE_GNU
# ifndef __USE_FILE_OFFSET64
extern int mkostemp (char *__template, int __flags) __nonnull ((1)) __wur;
# else
#  ifdef __REDIRECT
extern int __REDIRECT (mkostemp, (char *__template, int __flags), mkostemp64)
     __nonnull ((1)) __wur;
#  else
#   define mkostemp mkostemp64
#  endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkostemp64 (char *__template, int __flags) __nonnull ((1)) __wur;
# endif
# ifndef __USE_FILE_OFFSET64
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     __nonnull ((1)) __wur;
# else
#  ifdef __REDIRECT
extern int __REDIRECT (mkostemps, (char *__template, int __suffixlen,
				   int __flags), mkostemps64)
     __nonnull ((1)) __wur;
#  else
#   define mkostemps mkostemps64
#  endif
# endif
# ifdef __USE_LARGEFILE64
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __nonnull ((1)) __wur;
# endif
#endif
extern int system (const char *__command) __wur;
#ifdef	__USE_GNU
extern char *canonicalize_file_name (const char *__name)
     __THROW __nonnull ((1)) __attribute_malloc__
     __attr_dealloc_free __wur;
#endif
#if defined __USE_MISC || defined __USE_XOPEN_EXTENDED
extern char *realpath (const char *__restrict __name,
		       char *__restrict __resolved) __THROW __wur;
#endif
#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T
typedef int (*__compar_fn_t) (const void *, const void *);
# ifdef	__USE_GNU
typedef __compar_fn_t comparison_fn_t;
# endif
#endif
#ifdef __USE_GNU
typedef int (*__compar_d_fn_t) (const void *, const void *, void *);
#endif
extern void *bsearch (const void *__key, const void *__base,
		      size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __nonnull ((1, 2, 5)) __wur;
#ifdef __USE_EXTERN_INLINES
# include <bits/stdlib-bsearch.h>
#endif
extern void qsort (void *__base, size_t __nmemb, size_t __size,
		   __compar_fn_t __compar) __nonnull ((1, 4));
#ifdef __USE_GNU
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
		     __compar_d_fn_t __compar, void *__arg)
  __nonnull ((1, 4));
#endif
extern int abs (int __x) __THROW __attribute__ ((__const__)) __wur;
extern long int labs (long int __x) __THROW __attribute__ ((__const__)) __wur;
#ifdef __USE_ISOC99
__extension__ extern long long int llabs (long long int __x)
     __THROW __attribute__ ((__const__)) __wur;
#endif
extern div_t div (int __numer, int __denom)
     __THROW __attribute__ ((__const__)) __wur;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __THROW __attribute__ ((__const__)) __wur;
#ifdef __USE_ISOC99
__extension__ extern lldiv_t lldiv (long long int __numer,
				    long long int __denom)
     __THROW __attribute__ ((__const__)) __wur;
#endif
#if (defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K8) \
    || defined __USE_MISC
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign) __THROW __nonnull ((3, 4)) __wur;
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign) __THROW __nonnull ((3, 4)) __wur;
extern char *gcvt (double __value, int __ndigit, char *__buf)
     __THROW __nonnull ((3)) __wur;
#endif
#ifdef __USE_MISC
extern char *qecvt (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign)
     __THROW __nonnull ((3, 4)) __wur;
extern char *qfcvt (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign)
     __THROW __nonnull ((3, 4)) __wur;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __THROW __nonnull ((3)) __wur;
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign, char *__restrict __buf,
		   size_t __len) __THROW __nonnull ((3, 4, 5));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
		   int *__restrict __sign, char *__restrict __buf,
		   size_t __len) __THROW __nonnull ((3, 4, 5));
extern int qecvt_r (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign,
		    char *__restrict __buf, size_t __len)
     __THROW __nonnull ((3, 4, 5));
extern int qfcvt_r (long double __value, int __ndigit,
		    int *__restrict __decpt, int *__restrict __sign,
		    char *__restrict __buf, size_t __len)
     __THROW __nonnull ((3, 4, 5));
#endif	
extern int mblen (const char *__s, size_t __n) __THROW;
extern int mbtowc (wchar_t *__restrict __pwc,
		   const char *__restrict __s, size_t __n) __THROW;
extern int wctomb (char *__s, wchar_t __wchar) __THROW;
extern size_t mbstowcs (wchar_t *__restrict  __pwcs,
			const char *__restrict __s, size_t __n) __THROW
    __attr_access ((__read_only__, 2));
extern size_t wcstombs (char *__restrict __s,
			const wchar_t *__restrict __pwcs, size_t __n)
     __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
#ifdef __USE_MISC
extern int rpmatch (const char *__response) __THROW __nonnull ((1)) __wur;
#endif
#if defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8
extern int getsubopt (char **__restrict __optionp,
		      char *const *__restrict __tokens,
		      char **__restrict __valuep)
     __THROW __nonnull ((1, 2, 3)) __wur;
#endif
#ifdef __USE_XOPEN2KXSI
extern int posix_openpt (int __oflag) __wur;
#endif
#ifdef __USE_XOPEN_EXTENDED
extern int grantpt (int __fd) __THROW;
extern int unlockpt (int __fd) __THROW;
extern char *ptsname (int __fd) __THROW __wur;
#endif
#ifdef __USE_GNU
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __fortified_attr_access (__write_only__, 2, 3);
extern int getpt (void);
#endif
#ifdef __USE_MISC
extern int getloadavg (double __loadavg[], int __nelem)
     __THROW __nonnull ((1));
#endif
#if defined __USE_XOPEN_EXTENDED && !defined __USE_XOPEN2K
extern int ttyslot (void) __THROW;
#endif
#include <bits/stdlib-float.h>
#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
# include <bits/stdlib.h>
#endif
#include <bits/floatn.h>
#if defined __LDBL_COMPAT || __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI == 1
# include <bits/stdlib-ldbl.h>
#endif
__END_DECLS
#endif 
void merge(int arr[],int l,int m,int r){int i,j,k;int n1=m-l+1;int n2=r-m;int L[n1],R[n2];for(i=0;i<n1;i++)L[i]=arr[l+i];for(j=0;j<n2;j++)R[j]=arr[m+1+j];i=0;j=0;k=l;while(i<n1&&j<n2){if(L[i]<=R[j]){arr[k]=L[i];i++;}else{arr[k]=R[j];j++;}k++;}while(i<n1){arr[k]=L[i];i++;k++;}while(j<n2){arr[k]=R[j];j++;k++;}}
void mergeSort(int arr[],int l,int r){if(l<r){int m=l+(r-l)/2;mergeSort(arr,l,m);mergeSort(arr,m+1,r);merge(arr,l,m,r);}}
void printArray(int A[],int size){int i;for(i=0;i<size;i++)printf("%d ",A[i]);printf("\n");}
int main(){int arr[]={12,11,13,5,6,7};int arr_size=sizeof(arr)/sizeof(arr[0]);printf("Given array is \n");printArray(arr,arr_size);mergeSort(arr,0,arr_size-1);printf("\nSorted array is \n");printArray(arr,arr_size);return 0;}
