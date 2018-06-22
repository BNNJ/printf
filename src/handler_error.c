#include "ft_printf.h"

/*
** nbf is the number of strings that should be freed.
*/

int	ftpf_error(t_par *par, int nbf, ...)
{
	va_list	ap;
	char	*tmp;

	STATUS = ERROR;
	tmp = NULL;
	va_start(ap, nbf);
	while (nbf)
	{
		tmp = va_arg(ap, char*);
		if (tmp != NULL)
			ft_strdel(&tmp);
		--nbf;
	}
	va_end(ap);
	return (-1);
}
