#include "ft_printf.h"

char	*ft_umaxtoa_base(uintmax_t nb, char base_len, char type)
{
	char		*str;
	int			len;
	uintmax_t	tmp;
	char		*base;

	tmp = nb;
	len = 1;
	if (!(base = ft_strdup(type >= 'A' && type <= 'Z'
		? "0123456789ABCDEF" : "0123456789abcdef")))
		return (NULL);
	while (tmp /= base_len)
		++len;
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (--len >= 0)
	{
		str[len] = base[nb % base_len];
		nb /= base_len;
	}
	ft_strdel(&base);
	return (str);
}

void		ftpf_convert_int(va_list ap, t_par *par)
{
	intmax_t	nb;
	uintmax_t	unb;

	if (LEN_MOD == HH)
		nb = (char)va_arg(ap, int);
	else if (LEN_MOD == H)
		nb = (short)va_arg(ap, int);
	else if (LEN_MOD == NONE)
		nb = va_arg(ap, int);
	else if (LEN_MOD == L)
		nb = (long)va_arg(ap, intmax_t);
	else if (LEN_MOD == LL)
		nb = (long long)va_arg(ap, intmax_t);
	else if (LEN_MOD == Z)
		nb = (ssize_t)va_arg(ap, intmax_t);
	else if (LEN_MOD == J)
		nb = va_arg(ap, intmax_t);
	unb = (nb >= 0) ? nb : -nb;
	if (nb < 0)
		SIGN = '-';
	CONTENT = ft_umaxtoa_base(unb, BASE, TYPE);
	LEN = ft_strlen(CONTENT);
}

void		ftpf_convert_unsigned(va_list ap, t_par *par)
{
	uintmax_t	nb;

	if (LEN_MOD == HH)
		nb = (unsigned char)va_arg(ap, unsigned int);
	else if (LEN_MOD == H)
		nb = (unsigned short)va_arg(ap, unsigned int);
	else if (LEN_MOD == NONE)
		nb = va_arg(ap, unsigned int);
	else if (LEN_MOD == L)
		nb = (unsigned long)va_arg(ap, uintmax_t);
	else if (LEN_MOD == LL)
		nb = (unsigned long long)va_arg(ap, uintmax_t);
	else if (LEN_MOD == Z)
		nb = (size_t)va_arg(ap, uintmax_t);
	else if (LEN_MOD == J)
		nb = va_arg(ap, uintmax_t);
	if (nb == 0 && (TYPE == 'o' || 'O'))
		FLAGS &= ~F_HASH;
	CONTENT = FLAGS & F_BIN
		? ftpf_handle_bin(&nb, par)
		: ft_umaxtoa_base(nb, BASE, TYPE);
	LEN = ft_strlen(CONTENT);
}
