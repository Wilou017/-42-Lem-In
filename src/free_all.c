/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:13:24 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 15:23:42 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static void	free_map(t_lmdata *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
}

static void	free_pipe(t_lmdata *data)
{
	t_pipenode	*pipetmp;
	t_pipenode	*pipetmp2;

	pipetmp = data->tmppipe.start;
	while (pipetmp)
	{
		free(pipetmp->from);
		free(pipetmp->to);
		pipetmp2 = pipetmp->next;
		free(pipetmp);
		pipetmp = pipetmp2;
	}
}

static void	free_room(t_lmdata *data)
{
	t_roomnode	*roomtmp;
	t_roomnode	*roomtmp2;

	roomtmp = data->tmproom.start;
	while (roomtmp)
	{
		free(roomtmp->name);
		roomtmp2 = roomtmp->next;
		free(roomtmp);
		roomtmp = roomtmp2;
	}
}

void		free_all(t_lmdata *data)
{
	t_pathnode	*pathtmp;
	t_pathnode	*pathtmp2;
	t_antnode	*anttmp;
	t_antnode	*anttmp2;

	pathtmp = data->path.start;
	while (pathtmp)
	{
		free(pathtmp->inttab);
		pathtmp2 = pathtmp->next;
		free(pathtmp);
		pathtmp = pathtmp2;
	}
	anttmp = data->lstant.start;
	while (anttmp)
	{
		anttmp2 = anttmp->next;
		free(anttmp);
		anttmp = anttmp2;
	}
	free_room(data);
	free_pipe(data);
	free_map(data);
	free(data->file);
}
