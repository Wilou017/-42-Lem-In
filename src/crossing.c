/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 15:19:58 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 21:37:01 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static t_antnode	*i(t_antdata lstant, int idroom)
{
	t_antnode	*ant;
	int			index;

	ant = lstant.start;
	index = 0;
	while (ant)
	{
		if (ant->roomid == idroom)
			return (ant);
		ant = ant->next;
		index++;
	}
	return (NULL);
}

static void			printfourm(t_antnode *ant, t_lmdata *data)
{
	ft_printf("\033[%dmL%d-%s \033[0m", (data->color) ? \
		((ant->index + 1) % 6) + 90 : 37, ant->index + 1, \
		lm_searchname(data->tmproom, ant->roomid));
}

void				lm_crossing(t_lmdata *data)
{
	t_pathnode	*tmppath;
	int			index;
	t_antnode	*ant;

	while (data->antinend != data->ant)
	{
		ft_putchar('\n');
		tmppath = data->path.start;
		while (tmppath)
		{
			index = tmppath->size - 1;
			while (--index >= 0)
			{
				if ((ant = i(data->lstant, tmppath->inttab[index])) != NULL)
				{
					ant->roomid = tmppath->inttab[index + 1];
					(ant->roomid == data->end) ? data->antinend++ : 0;
					printfourm(ant, data);
				}
			}
			tmppath = tmppath->next;
		}
	}
	ft_putchar('\n');
}
