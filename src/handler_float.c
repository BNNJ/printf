#include "ft_printf.h"

static char	*get_width(t_par *par, int pref_len)
{
	char	*width;
	int		len;

	len = WIDTH - (LEN + pref_len);
	if (FLAGS & F_WIDTH && len > 0)
	{
		if (!(width = ft_strnew(len)))
			return (NULL);
		if (FLAGS & F_ZERO && !(FLAGS & F_MINUS))
			ft_memset(width, '0', len);
		else
			ft_memset(width, ' ', len);
		return (width);
	}
	else
		return (ft_chardup(0));
}

static int	assemble_string(t_par *par, char *prefix, char *width)
{
	if (FLAGS & F_MINUS || !(FLAGS & F_ZERO))
	{
		if (!(CONTENT = ft_strjoin_f(prefix, CONTENT, 3)))
			return (0);
		if (!(CONTENT = (FLAGS & F_MINUS)
			? ft_strjoin_f(CONTENT, width, 3)
			: ft_strjoin_f(width, CONTENT, 3)))
			return (0);
	}
	else
	{
		if (!(CONTENT = ft_strjoin_f(width, CONTENT, 3)))
			return (0);
		if (!(CONTENT = ft_strjoin_f(prefix, CONTENT, 3)))
			return (0);
	}
	LEN = ft_strlen(CONTENT);
	return (1);
}

int		ftpf_handle_float(va_list ap, t_par *par)
{
	char	*prefix;
	char	*width;

	PRECI = FLAGS & F_PRECI ? PRECI : 6;
	prefix = NULL;
	width = NULL;
	ftpf_convert_float(ap, par);
	if (!(prefix = ft_chardup(SIGN)))
		return (ftpf_error(par, 0));
	if (!(width = get_width(par, ft_strlen(prefix))))
		return (ftpf_error(par, 1, &prefix));
	if (!(assemble_string(par, prefix, width)))
		return (ftpf_error(par, 2, width, &prefix));
	return (1);
}
