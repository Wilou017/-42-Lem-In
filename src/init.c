/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 18:32:48 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 21:50:57 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static int	lm_extractcmd(char *line, int *cmd)
{
	if (ft_strncmp(line, "##", 2))
		return (1);
	if (!ft_strcmp(&line[2], "start"))
		*cmd = 1;
	else if (!ft_strcmp(&line[2], "end"))
		*cmd = 2;
	return (1);
}

static int	lm_calcmaxpath(t_lmdata *data)
{
	t_roomnode	*s;
	t_roomnode	*e;
	t_pipenode	*tmp;
	int			i_start;
	int			i_end;

	s = lm_selectnode(data, 1);
	e = lm_selectnode(data, 2);
	i_start = 0;
	i_end = 0;
	tmp = data->tmppipe.start;
	while (tmp && e)
	{
		if (!ft_strcmp(e->name, tmp->from) || !ft_strcmp(e->name, tmp->to))
			i_end++;
		tmp = tmp->next;
	}
	tmp = data->tmppipe.start;
	while (tmp && s)
	{
		if (!ft_strcmp(s->name, tmp->from) || !ft_strcmp(s->name, tmp->to))
			i_start++;
		tmp = tmp->next;
	}
	return (ft_min(3, i_start, i_end, data->ant));
}

int			lm_reed(t_lmdata *data)
{
	char	*line;
	int		retant;

	while (get_next_line(0, &line) == 1)
	{
		data->file = ft_strjoin(data->file, ft_strjoin(line, "\n", 0), 3);
		data->var_diez = ft_countchar(line, '#');
		if ((data->var_diez == 2 && lm_extractcmd(line, &data->cmd)) ||
			data->var_diez == 1)
			continue ;
		retant = extractant(data, line);
		if (retant == 2)
			continue ;
		if (retant == 3 || (data->var_room && ft_countchar(line, ' ') > 2))
			return (2);
		if ((retant = lm_norme(data, line)))
			return (retant);
	}
	if (lm_calcmaxpath(data) < 1)
		return (1);
	return (0);
}

static void	creatlstant(t_lmdata *data)
{
	int i;

	i = 0;
	while (i < data->ant)
		lm_pb_ant(data, i++);
}

int			lm_filltab(t_lmdata *data)
{
	t_pipenode	*tmp2;
	int			x;
	int			y;

	tmp2 = data->tmppipe.start;
	while (tmp2)
	{
		x = lm_searchindex(data->tmproom, tmp2->from);
		y = lm_searchindex(data->tmproom, tmp2->to);
		if (x == -1 || y == -1)
			return (1);
		data->map[y][x] = 'x';
		data->map[x][y] = 'x';
		tmp2 = tmp2->next;
	}
	creatlstant(data);
	return (0);
}
