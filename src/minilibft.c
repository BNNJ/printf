#include "ft_printf.h"

int		ft_atoi(const char *str)
{
	short				sign;
	unsigned long long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	sign = (*str == '-' || *str == '+') ? -(*str++ - 44) : 1;
	while (*str && *str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

int		ft_findchar(const char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)(b + i) = (unsigned char)c;
		++i;
	}
	return (b);
}

int		ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

char	*ft_chardup(char c)
{
	char	*str;

	if (!(str = ft_strnew(1)))
		return (NULL);
	*str = c;
	return (str);
}
