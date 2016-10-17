/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   already_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:44:09 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 21:50:53 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int			already_exist(t_lmdata *data)
{
	t_roomnode	*tmproom;
	t_roomnode	*tmp;
	int			i;

	tmproom = data->tmproom.start;
	while (tmproom)
	{
		i = 0;
		tmp = data->tmproom.start;
		while (tmp)
		{
			if (!ft_strcmp(tmproom->name, tmp->name))
				i++;
			tmp = tmp->next;
		}
		if (i > 1)
			return (1);
		tmproom = tmproom->next;
	}
	return (0);
}

int			lm_norme(t_lmdata *data, char *line)
{
	if (data->var_room && !lm_pushback_room(data, line))
	{
		if (data->tmproom.size < 2 || data->end < 0 || data->start < 0)
			return (2);
		data->var_room = 0;
	}
	if (!data->var_room && !lm_pushback_pipe(data, line) && (data->file = \
		ft_strsub(data->file, 0, ft_strlen(data->file) - \
			ft_strlen(line) - 1, 1)))
		return (1);
	return (0);
}
