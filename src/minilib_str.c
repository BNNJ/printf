#include "ft_printf.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)malloc(size + 1)))
		return (0);
	ft_memset(str, 0, size + 1);
	return (str);
}

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = (NULL);
	}
}

char	*ft_strsub_f(const char *s, unsigned int start, size_t len, char opt)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(substr = malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		++i;
	}
	substr[i] = '\0';
	if (opt == 1)
		ft_strdel((char**)&s);
	return (substr);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dest;

	len = 0;
	while (s1[len])
		++len;
	if (!(dest = (char*)malloc(len + 1)))
		return (NULL);
	while (*s1)
		*dest++ = *s1++;
	*dest = '\0';
	return (dest - len);
}

char		*ft_strjoin_f(const char *s1, const char *s2, int opt)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (opt == 1 || opt == 3 ? (char*)s1 : ft_strdup(s1));
	else if (!s1 && s2)
		return (opt == 2 || opt == 3 ? (char*)s2 : ft_strdup(s2));
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	if (opt == 1 || opt == 3)
		ft_strdel((char**)&s1);
	if (opt == 2 || opt == 3)
		ft_strdel((char**)&s2);
	return (str);
}
