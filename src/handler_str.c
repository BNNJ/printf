#include "ft_printf.h"

static int	ft_wstrlen(wchar_t *str)
{
	int	len;

	len = 0;
	if (str)
		while (str[len])
			++len;
	return (len);
}

static int	get_precision(t_par *par)
{
	size_t	i;
	size_t	k;

	i = 0;
	while (i <= PRECI)
	{
		k = 0;
		while (CONTENT[i] & (128 >> k))
			++k;
		if (i + k > PRECI)
			return (i);
		i += k;
	}
	return (i);
}

static int	ftpf_finalize_string(t_par *par)
{
	char	*tmp;

	tmp = NULL;
	if (FLAGS & F_PRECI && PRECI < LEN)
	{
		CONTENT = LEN_MOD > NONE
			? ft_strsub_f(CONTENT, 0, get_precision(par), 1)
			: ft_strsub_f(CONTENT, 0, PRECI, 1);
		LEN = ft_strlen(CONTENT);
	}
	if (FLAGS & F_WIDTH && WIDTH > LEN)
	{
		if (!(tmp = ft_strnew(WIDTH - LEN)))
			return (-1);
		ft_memset(tmp, ' ', WIDTH - LEN);
		CONTENT = FLAGS & F_MINUS
			? ft_strjoin_f((const char*)CONTENT, (const char*)tmp, 3)
			: ft_strjoin_f((const char*)tmp, (const char*)CONTENT, 3);
		LEN = ft_strlen(CONTENT);
	}
	return (1);
}

static int	ftpf_handle_wide_string(va_list ap, t_par *par)
{
	wchar_t	*tmp;
	char	*str;
	int		i;
	int		check;

	i = 0;
	check = 0;
	tmp = va_arg(ap, wchar_t*);
	if (!tmp)
		PRECI = PRECI >= 6 ? PRECI : 0;
	else
	{
		if (!(str = ft_strnew(sizeof(wchar_t) * ft_wstrlen(tmp))))
			return (ftpf_error(par, 0));
		while (*tmp)
		{
			if (!(check = ftpf_convert_wide_char(*tmp, str + i)))
				return (ftpf_error(par, 1, str));
			i += check;
			++tmp;
		}
	}
	LEN_MOD = !tmp ? NONE : L;
	CONTENT = !tmp ? ft_strdup("(null)") : str;
	LEN = ft_strlen(CONTENT);
	printf("## %S ##\n", CONTENT);
	return (1);
}

int		ftpf_handle_string(va_list ap, t_par *par)
{
	char	*str;

	str = NULL;
	if (LEN_MOD > NONE)
		ftpf_handle_wide_string(ap, par);
	else
	{
		str = va_arg(ap, char*);
		if (!str)
		{
			CONTENT = ft_strdup("(null)");
			PRECI = PRECI >= 6 ? PRECI : 0;
		}
		else
			CONTENT = ft_strdup(str);
	}
	if (!(CONTENT))
		return (-1);
	LEN = ft_strlen(CONTENT);
	ftpf_finalize_string(par);
	return (1);
}
