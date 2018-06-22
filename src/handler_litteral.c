#include "ft_printf.h"

int		ftpf_handle_litteral(char *str, t_par *par)
{
	if (!str)
	{
		CONTENT = ft_strdup("");
		STATUS = ERROR;
		return (-1);
	}
	CONTENT = str;
	LEN = ft_strlen(CONTENT);
	TYPE = 't';
	return (LEN);
}
