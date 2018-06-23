#include "ft_printf.h"

static int	ftpf_majortom(va_list ap, t_par *par)
{
	int	ret;

//	if (TYPE == '{')
//		ret = ftpf_handle_display(par);
	if (TYPE == 'c' || TYPE == 'C' )
		ret = ftpf_handle_char(ap, par);
	else if (ft_findchar("dDiuUoOxXbB", TYPE) >= 0)
		ret = ftpf_handle_int(ap, par);
	else if (TYPE == 's' || TYPE == 'S')
		ret = ftpf_handle_string(ap, par);
	else if (TYPE == 'p' || TYPE == 'P')
		ret = ftpf_handle_pointer(ap, par);
	else if (TYPE == 'f' || TYPE == 'F' || TYPE == 'a' || TYPE == 'A')
		ret = ftpf_handle_float(ap, par);
	else if (TYPE == '%')
		ret = ftpf_handle_litteral(ft_strdup("%"), par);
	else
		ret = 1;
	return (ret < 0 ? ftpf_error(par, 0) : 1);

}

static int	ftpf_get_flags(va_list ap, const char *format, t_par *par)
{
	char	*tmp;

	tmp = (char*)format;
	++format;
	ftpf_get_format_flags(&format, par);
	ftpf_get_width(ap, &format, par);
	ftpf_get_precision(ap, &format, par);
	ftpf_get_size_flags(&format, par);
	ftpf_get_type(&format, par);
	return (format - tmp);
}

static void	ftpf_init_par(t_par *par)
{
	FLAGS = 0;
	WIDTH = 0;
	PRECI = 0;
	LEN_MOD = NONE;
	STATUS = OK;
	CONTENT = NULL;
	LEN = 0;
	SIGN = 0;
	TYPE = 0;
	BASE = 10;
}

int			ftpf_groundcontrol(const char *format, va_list ap, t_string **str)
{
	int		i;
	t_par	par;

	if (!(par.string = (t_string*)malloc(sizeof(t_string))))
		return (-1);
	write(1, "\n", 1);
	while (*format)
	{
		ftpf_init_par(&par);
		if ((i = ft_findchar(format, '%')) < 0)
			i = ftpf_handle_litteral(ft_strdup(format), &par);
		else if (i > 0)
			i = ftpf_handle_litteral(ft_strsub_f(format, 0, i, 0), &par);
		else
			i = ftpf_get_flags(ap, format, &par);
		format += i;
		if (ftpf_majortom(ap, &par) < 0 || par.e_status == ERROR)
			return (ftpf_error(&par, 1, par.string->content));
		*str = ft_tstr_join(*str, par.string, 1);
		ft_strdel(&par.string->content);
	}
	ft_tstr_del(&par.string);
	return ((*str)->len);
}
