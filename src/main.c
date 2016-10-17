/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 16:39:45 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 19:05:21 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static void	lm_init(t_lmdata *data, int ac, t_tab av)
{
	data->ant = -1;
	data->path.size = 0;
	data->path.start = NULL;
	data->path.end = NULL;
	data->lstant.size = 0;
	data->lstant.start = NULL;
	data->lstant.end = NULL;
	data->tmproom.size = 0;
	data->tmproom.start = NULL;
	data->tmproom.end = NULL;
	data->tmppipe.size = 0;
	data->tmppipe.start = NULL;
	data->tmppipe.end = NULL;
	data->start = -1;
	data->end = -1;
	data->var_room = 1;
	data->cmd = 0;
	data->color = 0;
	data->antinend = 0;
	data->file = ft_strnew(0);
	if (ac > 1 && !ft_strcmp(av[1], "-color"))
		data->color = 1;
}

static void	run_boby_run(t_lmdata *data)
{
	t_antnode	*ant;
	char		*endname;

	ant = data->lstant.start;
	endname = lm_searchname(data->tmproom, data->end);
	ft_putchar('\n');
	while (ant)
	{
		ft_printf("\033[%dmL%d-%s \033[0m", (data->color) ? \
			((ant->index + 1) % 6) + 90 : 37, ant->index + 1, endname);
		ant = ant->next;
	}
	ft_putchar('\n');
}

int			main(int ac, t_tab av)
{
	t_lmdata	data;

	lm_init(&data, ac, av);
	if (lm_reed(&data) == 2)
		return (ft_putstr("ERROR"));
	data.map = ft_tabmalloc(data.tmproom.size, '.');
	if (already_exist(&data))
		return (ft_putstr("ERROR"));
	if (lm_filltab(&data) == 0)
		lm_solve(&data);
	if (data.path.size < 1)
		return (ft_putstr("ERROR"));
	ft_putstr(data.file);
	(data.path.start->size == 2) ? run_boby_run(&data) : lm_crossing(&data);
	free_all(&data);
	return (0);
}
