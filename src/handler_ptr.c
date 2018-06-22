#include "ft_printf.h"

int		ftpf_handle_pointer(va_list ap, t_par *par)
{
	void	*ptr;

	ptr = va_arg(ap, void*);
	if (!(CONTENT = ft_umaxtoa_base((unsigned long)ptr, 16, TYPE)))
		return (-1);
	CONTENT = ft_strjoin_f("0x", CONTENT, 2);
	LEN = ft_strlen(CONTENT);
	return (CONTENT ? 1 : 0);
}
