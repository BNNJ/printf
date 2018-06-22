#include "ft_printf.h"

static void	ftpf_convert_bin(void *ptr, int bits, t_par *par, char *str)
{
	while (bits--)
	{
		*str = *(unsigned long long*)ptr & (1LL << bits) ? '1' : '0';
		if (TYPE == 'f' && (bits == 31 || bits == 23) && FLAGS & F_HASH)
			*(++str) = ' ';
		else if (TYPE == 'F' && (bits == 63 || bits == 52) && FLAGS & F_HASH)
			*(++str) = ' ';
		else if (((TYPE != 'f' && TYPE != 'F') || !(FLAGS & F_HASH)) 
			&& bits % 8 == 0 && bits != 0)
			*(++str) = ' ';
		++str;
	}
}

char		*ftpf_handle_bin(void *ptr, t_par *par)
{
	int		bits;
	char	*str;

	if (TYPE == 'p' || TYPE == 'P' || TYPE == 'F'
		|| (LEN_MOD >= L && TYPE != 'c' && TYPE != 'C'))
		bits = 64;
	else if (LEN_MOD == HH || (TYPE == 'c' && LEN_MOD <= NONE))
		bits = 8;
	else if (LEN_MOD == H)
		bits = 16;
	else
		bits = 32;
	if (!(str = ft_strnew(bits + 7)))
	{
		STATUS = ERROR;
		return (NULL);
	}
	ftpf_convert_bin(ptr, bits, par, str);
	FLAGS &= (F_MINUS + F_WIDTH);
	return (str);
}
