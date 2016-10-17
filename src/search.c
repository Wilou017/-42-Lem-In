/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 19:33:16 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 15:15:22 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int			lm_searchindex(t_roomdata roomdata, char *name)
{
	t_roomnode	*tmp;
	int			i;

	tmp = roomdata.start;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

char		*lm_searchname(t_roomdata roomdata, int index)
{
	t_roomnode	*tmp;
	int			i;

	tmp = roomdata.start;
	i = 0;
	while (tmp)
	{
		if (i == index)
			return (tmp->name);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

int			extractant(t_lmdata *data, char *line)
{
	char	*al;
	int		ret;

	ret = 0;
	al = NULL;
	if (data->ant == -1)
	{
		data->ant = (ft_strisdigit(line)) ? ft_atoi(line) : -1;
		al = ft_itoa(data->ant, 10);
		if (data->ant < 1 || ft_strcmp(al, line))
			ret = 3;
		else
			ret = 2;
		free(al);
	}
	return (ret);
}
