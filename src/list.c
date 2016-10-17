/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 19:19:45 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/22 19:18:55 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

t_roomnode	*lm_selectnode(t_lmdata *data, int state)
{
	t_roomnode	*tmp;

	tmp = data->tmproom.start;
	while (tmp)
	{
		if (tmp->state == state)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void		swapdata(t_pathnode *node1, t_pathnode *node2)
{
	t_pathnode tmp;

	tmp.inttab = node1->inttab;
	tmp.size = node1->size;
	node1->inttab = node2->inttab;
	node1->size = node2->size;
	node2->inttab = tmp.inttab;
	node2->size = tmp.size;
}

int			lstissort(t_pathnode *node)
{
	while (node && node->next)
	{
		if (node->size > node->next->size)
			return (0);
		node = node->next;
	}
	return (1);
}

void		sortpath(t_pathdata data)
{
	t_pathnode *tmp;

	while (lstissort(data.start) == 0)
	{
		tmp = data.start;
		while (tmp && tmp->next)
		{
			if (tmp->size > tmp->next->size)
				swapdata(tmp, tmp->next);
			tmp = tmp->next;
		}
	}
}

void		deletepathnode(t_pathdata *data, int index)
{
	t_pathnode	*node;
	int			i;

	node = data->start;
	i = 0;
	while (node && i < index)
	{
		node = node->next;
		i++;
	}
	if (node && i == index)
	{
		free(node->inttab);
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		else
			data->end = node->prev;
		free(node);
		data->size--;
	}
}
