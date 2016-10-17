/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 18:51:31 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 18:28:47 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int			lm_pushback_room(t_lmdata *data, char *line)
{
	t_roomnode	*new;
	t_tab		split;

	new = (t_roomnode*)malloc(sizeof(t_roomnode));
	split = ft_strsplit(line, ' ');
	if (ft_countchar(line, ' ') != 2 || ft_tablen(split, 0) != 3)
		return (0);
	new->name = split[0];
	new->x = ft_atoi(split[1]);
	new->y = ft_atoi(split[2]);
	ft_strdel(&split[1]);
	ft_strdel(&split[2]);
	new->state = data->cmd;
	(data->cmd == 1 && data->start < 0) ? data->start = data->tmproom.size : 0;
	(data->cmd == 2 && data->end < 0) ? data->end = data->tmproom.size : 0;
	new->prev = data->tmproom.end;
	new->next = NULL;
	data->tmproom.size++;
	(data->tmproom.end) ? data->tmproom.end->next = new : 0;
	data->tmproom.end = new;
	(data->tmproom.start == NULL) ? data->tmproom.start = new : 0;
	data->cmd = 0;
	return (1);
}

int			lm_pushback_pipe(t_lmdata *data, char *line)
{
	t_pipenode	*new;
	char		**split;

	new = (t_pipenode*)malloc(sizeof(t_pipenode));
	split = ft_strsplit(line, '-');
	if (ft_countchar(line, '-') != 1 || ft_tablen(split, 0) != 2 ||
		lm_searchindex(data->tmproom, split[0]) < 0 ||
		lm_searchindex(data->tmproom, split[1]) < 0)
		return (0);
	new->from = split[0];
	new->to = split[1];
	new->prev = data->tmppipe.end;
	new->next = NULL;
	data->tmppipe.size++;
	if (data->tmppipe.end)
		data->tmppipe.end->next = new;
	data->tmppipe.end = new;
	if (data->tmppipe.start == NULL)
		data->tmppipe.start = new;
	return (1);
}

int			lm_pb_path(t_lmdata *data, int *inttab, int size)
{
	t_pathnode	*new;

	new = (t_pathnode*)malloc(sizeof(t_pathnode));
	new->inttab = inttab;
	new->size = size;
	new->prev = data->path.end;
	new->next = NULL;
	data->path.size++;
	if (data->path.end)
		data->path.end->next = new;
	data->path.end = new;
	if (data->path.start == NULL)
		data->path.start = new;
	return (1);
}

int			lm_pb_ant(t_lmdata *data, int index)
{
	t_antnode	*new;

	new = (t_antnode*)malloc(sizeof(t_antnode));
	new->index = index;
	new->roomid = data->start;
	new->tabindex = 0;
	new->prev = data->lstant.end;
	new->next = NULL;
	data->lstant.size++;
	if (data->lstant.end)
		data->lstant.end->next = new;
	data->lstant.end = new;
	if (data->lstant.start == NULL)
		data->lstant.start = new;
	return (1);
}
