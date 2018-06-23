#include "ft_printf.h"

int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	int			ret;
	t_string	*str;

	if (!(str = ft_tstr_new(0)))
		return (-1);
	if (!format)
		return (-1);
	ret = ftpf_groundcontrol(format, ap, &str);
	if (str->content)
		write(fd, str->content, str->len);
	ft_tstr_del(&str);
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (ret);
}
