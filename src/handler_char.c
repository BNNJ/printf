#include "ft_printf.h"

static int	ftpf_handle_wchar(va_list ap, t_par *par)
{
	char	str[5];
	wchar_t	c;

	ft_memset(str, 0, 5);
	c = va_arg(ap, wchar_t);
	if (c < -1 || (c >= 0xD800 && c <= 0xDFFF) || c > 0x10FFFF)
		return (ftpf_error(par, 0));
	if (!(ftpf_convert_wide_char(c, str)))
		return (ftpf_error(par, 0));
	if (FLAGS & F_BIN)
		CONTENT = ftpf_handle_bin(&c, par);
	else
	{
		CONTENT = ft_strdup(str);
		LEN = ft_strlen(CONTENT);
	}
	if (!CONTENT)
		return (ftpf_error(par, 0));
	return (1);
}

int			ftpf_handle_char(va_list ap, t_par *par)
{
	char	c;

	if (LEN_MOD > NONE)
		return (ftpf_handle_wchar(ap, par));
	else
	{
		c = (char)va_arg(ap, int);
		return (ftpf_convert_char(c, par));
	}
}
