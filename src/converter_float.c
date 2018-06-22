#include "ft_printf.h"

static double		ft_pow10(int pow)
{
	int		i;
	double	result;
	double	nb;

	i = 1;
	result = 1.0;
	nb = 10.0;
	if (pow < 0)
		return 0;
	while (i <= pow)
	{
		result = result * nb;
		++i;
	}
	return (result);
}

static uintmax_t	ftpf_dectoi(double f, t_par *par)
{
	uintmax_t	n;
	size_t		i;
	uintmax_t	tmp;
	
	f-= (double)(long)f;
	i = 1;
	n = 0;
	while (i <= PRECI)
	{
		n = n* 10 + ((uintmax_t)(f * ft_pow10(i)) % 10);
		++i;
	}
	tmp = (uintmax_t)(f * ft_pow10(i));
	if (tmp % 10 > 5)
		++n;
	else if (tmp % 10 == 5)
	{
		tmp = (uintmax_t)(f * ft_pow10(i + 2));
		if (tmp % 100 > 0)
			++n;
	}
	return (n);
}

static char			*ftpf_ftoa(double f, t_par *par)
{
	char	*ret;
	char	*tmp;
	char	*padding;

	f = f < 0 ? -f : f;
	ret = ft_umaxtoa_base((uintmax_t)f, BASE, TYPE);
	ret = ft_strjoin_f(ret, ".", 1);
	tmp = ft_umaxtoa_base(ftpf_dectoi(f, par), BASE, TYPE);
	if (!(padding = ft_strnew(PRECI - ft_strlen(tmp))))
		return (NULL);
	ft_memset(padding, '0', PRECI - ft_strlen(tmp));
	tmp = ft_strjoin_f(padding, tmp, 3);
	ret = ft_strjoin_f(ret, tmp, 3);
	return (ret);
}

void				ftpf_convert_float(va_list ap, t_par *par)
{
	double	f;

	f = va_arg(ap, double);
	if (FLAGS & F_BIN)
		CONTENT = ftpf_handle_bin(&f, par);
	else
		CONTENT = ftpf_ftoa(f, par);
	LEN = ft_strlen(CONTENT);
	if (f < 0)
		SIGN = '-';
}
