#include "ft_printf.h"

void	ftpf_get_type(const char **format, t_par *par)
{
	if (ft_findchar("cCsSpPdDioOuUxXbBfFaA%", **format) >= 0)
	{
		TYPE = **format;
		++*format;
	}
	else if (**format == '}' && FLAGS & F_DISPLAY)
		TYPE = '{';
	else
		TYPE = '%';
	if (TYPE == 'x' || TYPE == 'X' || TYPE == 'a' || TYPE == 'A')
		BASE = 16;
	else if (TYPE == 'o' || TYPE == 'O')
		BASE = 8;
	else if (TYPE == 'b' || TYPE == 'B')
		BASE = 2;
	else
		BASE = 10;
	if (ft_findchar("CSPDOU", TYPE) >= 0 && LEN_MOD < LL)
		++LEN_MOD;
}

void	ftpf_get_size_flags(char const **format, t_par *par)
{
	if (**format == 'j' || **format == 'z'
		|| **format == 'h' || **format == 'l')
	{
		if (**format == 'j')
			LEN_MOD = J;
		else if (**format == 'z')
			LEN_MOD = Z;
		else if (**format == 'h')
			LEN_MOD = H;
		else if (**format == 'l')
			LEN_MOD = L;
		if (**format == 'h' && *(*format + 1) == 'h')
		{
			LEN_MOD = HH;
			++*format;
		}
		else if (**format == 'l' && *(*format + 1) == 'l')
		{
			LEN_MOD = LL;
			++*format;
		}
		++*format;
	}
	else
		LEN_MOD = NONE;
}

void	ftpf_get_precision(va_list ap, const char **format, t_par *par)
{
	PRECI = 0;
	if (**format == '.')
	{
		FLAGS |= F_PRECI;
		++*format;
		if (**format == '*')
		{
			PRECI = va_arg(ap, int);
			++*format;
		}
		else
		{
			PRECI = ft_atoi(*format);
			while (**format >= '0' && **format <= '9')
				++*format;
		}
	}
	else
		PRECI = 0;
}

void	ftpf_get_width(va_list ap, const char **format, t_par *par)
{
	WIDTH = 0;
	if (**format == '*')
	{
		WIDTH = va_arg(ap, int);
		FLAGS |= F_WIDTH;
		++*format;
	}
	else if (**format >= '1' && **format <= '9')
	{
		WIDTH = ft_atoi(*format);
		while (**format >= '0' && **format <= '9')
			++*format;
		FLAGS |= F_WIDTH;
	}
}

void	ftpf_get_format_flags(const char **format, t_par *par)
{
	FLAGS = 0;
	while (**format == '#' || **format == '0' || **format == '-'
		|| **format == '+' || **format == ' ' || **format == '&')
	{
		if (**format == '#')
			FLAGS |= F_HASH;
		else if (**format == '0')
			FLAGS |= F_ZERO;
		else if (**format == '-')
			FLAGS |= F_MINUS;
		else if (**format == '+')
			FLAGS |= F_PLUS;
		else if (**format == ' ')
			FLAGS |= F_SPACE;
		else if (**format == '&')
			FLAGS |= F_BIN;
		else if (**format == '{')
			FLAGS |= F_DISPLAY;
		if (FLAGS & F_PLUS || FLAGS & F_SPACE)
			SIGN = **format;
		++*format;
	}
}
