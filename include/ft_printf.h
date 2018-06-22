#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define COLOR_ENABLED 1

# define FLAGS par->flags
# define LEN_MOD par->e_mod
# define WIDTH par->width
# define PRECI par->precision
# define STRING par->string
# define CONTENT par->string->content
# define LEN par->string->len
# define STATUS par->e_status
# define TYPE par->type
# define SIGN par->sign
# define BASE par->base

# define F_ZERO 1
# define F_HASH 2
# define F_PLUS 4
# define F_MINUS 8
# define F_SPACE 16
# define F_BIN 32

# define F_PRECI 64
# define F_WIDTH 128
# define F_DISPLAY 256

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdint.h>
# include <stdio.h>

typedef struct	s_string
{
	char		*content;
	size_t		len;
}				t_string;

typedef struct	s_par
{
	t_string	*string;
	int			flags;
	size_t		width;
	size_t		precision;
	enum
	{
		OK,
		ERROR
	}			e_status;
	char		type;
	char		sign;
	int			base;
	enum
	{
		H,
		HH,
		NONE,
		L,
		LL,
		Z,
		J
	}			e_mod;
}				t_par;

/*
** ft_printf.c
*/

int				ft_vdprintf(int fd, const char *format, va_list ap);
int				ft_printf(const char *format, ...);

/*
** parser.c && handler_error.c
*/

int				ftpf_groundcontrol(const char *format,
					va_list ap, t_string **str);
int				ftpf_error(t_par *par, int nbf, ...);

/*
** parser_flags.c
*/

#include "ft_printf.h"

void			ftpf_get_type(const char **format, t_par *par);
void			ftpf_get_size_flags(char const **format, t_par *par);
void			ftpf_get_precision(va_list ap, const char **format, t_par *par);
void			ftpf_get_width(va_list ap, const char **format, t_par *par);
void			ftpf_get_format_flags(const char **format, t_par *par);

/*
** handler_char.c && converter_char.c
*/

int				ftpf_handle_char(va_list ap, t_par *par);

int				ftpf_convert_wide_char(wchar_t c, char *str);
int				ftpf_convert_char(char c, t_par *par);

/*
** handler_str.c && handler_litteral.c
*/

int				ftpf_handle_string(va_list ap, t_par *par);
int				ftpf_handle_litteral(char *str, t_par *par);

/*
** handler_int.c && converter_int.c
*/

int				ftpf_handle_int(va_list ap, t_par *par);

char			*ft_umaxtoa_base(uintmax_t nb, char base_len, char type);
void			ftpf_convert_int(va_list ap, t_par *par);
void			ftpf_convert_unsigned(va_list ap, t_par *par);

/*
** handler_float.c && converter_float.c
*/

int				ftpf_handle_float(va_list ap, t_par *par);

void			ftpf_convert_float(va_list ap, t_par *par);

/*
** handler_ptr.c && handler_binflag.c
*/

int				ftpf_handle_pointer(va_list ap, t_par *par);

char			*ftpf_handle_bin(void *ptr, t_par *par);

/*
** minilibft && str && tstr
*/

int				ft_atoi(const char *str);
void			*ft_memset(void *b, int c, size_t n);
int				ft_findchar(const char *str, char c);
int				ft_strlen(const char *str);
char			*ft_chardup(char c);

char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
char			*ft_strsub_f(const char *s, unsigned int start,
					size_t len, char opt);
char			*ft_strjoin_f(const char *s1, const char *s2, int opt);
char			*ft_strdup(const char *s1);


t_string		*ft_tstr_new(size_t size);
void			ft_tstr_del(t_string **str);
t_string		*ft_tstr_dup(t_string *s1);
t_string		*ft_tstr_join(t_string *s1, t_string *s2, int opt);

#endif
