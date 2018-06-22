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
		if (FLAGS & F_ZERO && !(FLAGS & F_PRECI || FLAGS & F_MINUS))
			ft_memset(width, '0', len);
		else
			ft_memset(width, ' ', len);
		return (width);
	}
	else
		return (ft_strdup(""));
}

static char	*get_prefix(t_par *par)
{
	if (FLAGS & F_HASH)
	{
		if (TYPE == 'x')
			return (ft_strdup("0x"));
		else if (TYPE == 'X')
			return (ft_strdup("0X"));
		else if (TYPE == 'o' || TYPE == 'O')
			return (ft_strdup("0"));
		else if (TYPE == 'B')
			return (ft_strdup("0b"));
		else
			return (ft_chardup(SIGN));
	}
	else
		return (ft_chardup(SIGN));
}

static int	add_precision(t_par *par)
{
	char	*preci;
	int		len;

	len = PRECI - LEN;
	if (FLAGS & F_PRECI && len > 0)
	{
		if (!(preci = ft_strnew(len)))
			return (0);
		ft_memset(preci, '0', len);
		if (!(CONTENT = ft_strjoin_f(preci, CONTENT, 3)))
			return (0);
	}
	LEN = ft_strlen(CONTENT);
	return (1);
}

static int	assemble_string(t_par *par, char *prefix, char *width)
{
	if (FLAGS & F_PRECI || FLAGS & F_MINUS || !(FLAGS & F_ZERO))
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
	return (1);
}

int			ftpf_handle_int(va_list ap, t_par *par)
{
	char	*prefix;
	char	*width;

	if (ft_findchar("oOuUxXB", TYPE) >= 0 || FLAGS & F_BIN)
		ftpf_convert_unsigned(ap, par);
	else
		ftpf_convert_int(ap, par);
	if (!(add_precision(par)))
		return (ftpf_error(par, 0));
	if (!(prefix = get_prefix(par)))
		return (ftpf_error(par, 0));
	if (!(width = get_width(par, ft_strlen(prefix))))
		return (ftpf_error(par, 1, &prefix));
	if (!(assemble_string(par, prefix, width)))
		return (ftpf_error(par, 2, width, &prefix));
	return (1);
}
