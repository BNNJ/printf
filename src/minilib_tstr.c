#include "ft_printf.h"
#include <stdio.h>

t_string		*ft_tstr_new(size_t size)
{
	t_string	*str;

	if (!(str = (t_string*)malloc(sizeof(t_string))))
		return (0);
	if (!(str->content = ft_strnew(size)))
		return (0);
	str->len = size;
	return (str);
}

void			ft_tstr_del(t_string **str)
{
	if (str && *str)
	{
		if ((*str)->content)
			ft_strdel(&((*str)->content));
		free(*str);
		*str = NULL;
	}
}

t_string	*ft_tstr_dup(t_string *s1)
{
	size_t		i;
	t_string	*new;

	i = 0;
	if (!s1)
		return (0);
	if (!(new = ft_tstr_new(s1->len)))
		return (0);
	while (i < s1->len)
	{
		new->content[i] = s1->content[i];
		++i;
	}
	new->len = s1->len;
	return (new);
}

static t_string	*help_join(t_string *s1, t_string *s2)
{
	t_string	*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!(str = ft_tstr_new(s1->len + s2->len)))
		return (NULL);
	while (i < s1->len)
	{
		str->content[i] = s1->content[i];
		++i;
	}
	while (j < s2->len)
	{
		str->content[i + j] = s2->content[j];
		++j;
	}
	return (str);
}

t_string		*ft_tstr_join(t_string *s1, t_string *s2, int opt)
{
	t_string	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (opt == 1 || opt == 3 ? s1 : ft_tstr_dup(s1));
	else if (!s1 && s2)
		return (opt == 2 || opt == 3 ? s2 : ft_tstr_dup(s2));
	str = help_join(s1, s2);
	str->len = s1->len + s2->len;
	if (opt == 1 || opt == 3)
		ft_tstr_del(&s1);
	if (opt == 2 || opt == 3)
		ft_tstr_del(&s2);
	return (str);
}
