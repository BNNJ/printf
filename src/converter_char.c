#include "ft_printf.h"

int		ftpf_convert_wide_char(wchar_t c, char *str)
{
	if (c <= 0x7F || (MB_CUR_MAX == 1 && c <= 0xFF))
		str[0] = (char)c;
	else if (c <= 0x7FF && MB_CUR_MAX >= 2)
	{
		str[0] = (c >> 6 | 0xC0) & 0xDF;
		str[1] = (c | 0x80) & 0xBF;
	}
	else if (c <= 0xFFFF && MB_CUR_MAX >= 3)
	{
		str[0] = (c >> 12 | 0xE0) & 0xEF;
		str[1] = (c >> 6 | 0x80) & 0xBF;
		str[2] = (c | 0x80) & 0xBF;
	}
	else if (c <= 0x10FFFF && MB_CUR_MAX >= 4)
	{
		str[0] = (c >> 18 | 0xF0) & 0xF7;
		str[1] = (c >> 12 | 0x80) & 0xBF;
		str[2] = (c >> 6 | 0x80) & 0xBF;
		str[3] = (c | 0x80) & 0xBF;
	}
	else
		return (0);
	return (ft_strlen(str);
}

int		ftpf_convert_char(char c, t_par *par)
{
	if (FLAGS & F_BIN)
	{
		CONTENT = ftpf_handle_bin(&c, par);
		LEN = ft_strlen(CONTENT);
	}
	else
	{
		if (!(STRING = ft_tstr_new(1)))
			return (-1);
		CONTENT[0] = c;
		CONTENT[1] = '\0';
		LEN = 1;
	}
	return (1);
}
