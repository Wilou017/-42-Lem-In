/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 19:30:58 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 15:51:39 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int			lm_rec(t_lmdata *data, int line, int col, int *path)
{
	if (line == data->end)
	{
		path[path[0] + 1] = line;
		lm_pb_path(data, ft_inttabdup(&path[1], path[0] + 1), path[0] + 1);
		path[path[0] + 1] = -1;
		return (1);
	}
	while (data->map[line][col])
	{
		if (data->map[line][col] == 'x')
		{
			data->map[line][col] = '.';
			data->map[col][line] = '.';
			path[0]++;
			path[path[0]] = line;
			lm_rec(data, col, 0, path);
			path[path[0]] = -1;
			path[0]--;
			data->map[line][col] = 'x';
			data->map[col][line] = 'x';
		}
		col++;
	}
	return (0);
}

static int	comptab(int *tab1, int size1, int *tab2, int size2)
{
	while (--size2 >= 0)
		if (ft_intinarray(tab1, tab2[size2], size1))
			return (0);
	return (1);
}

static void	cleanpath(t_pathdata *data, int ant)
{
	t_pathnode	*tmp;
	int			*ur;
	int			urs;
	int			index;

	tmp = data->start->next;
	index = 1;
	ur = ft_inttabdup(data->start->inttab, data->start->size);
	urs = data->start->size;
	while (tmp)
	{
		if (data->start->size > 2 && index < ant &&
			comptab(ur, urs, &tmp->inttab[1], tmp->size - 2))
		{
			ur = ft_inttabjoin(ur, urs, &tmp->inttab[1], tmp->size - 2);
			urs += tmp->size - 2;
			tmp = tmp->next;
			index++;
		}
		else
		{
			deletepathnode(data, index);
			tmp = tmp->prev->next;
		}
	}
}

void		lm_solve(t_lmdata *data)
{
	int *path;

	path = ft_inttabnew(data->tmproom.size);
	path[0] = 0;
	lm_rec(data, data->start, 0, path);
	if (data->path.size > 1)
	{
		sortpath(data->path);
		cleanpath(&data->path, data->ant);
	}
}
