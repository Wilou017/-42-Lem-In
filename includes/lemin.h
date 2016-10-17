/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitre <amaitre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:37:28 by amaitre           #+#    #+#             */
/*   Updated: 2016/09/29 21:49:32 by amaitre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <newlibft.h>

typedef struct			s_antnode
{
	int					roomid;
	int					index;
	int					tabindex;
	struct s_antnode	*next;
	struct s_antnode	*prev;
}						t_antnode;

typedef struct			s_antdata
{
	int					size;
	t_antnode			*start;
	t_antnode			*end;
}						t_antdata;

typedef struct			s_roomnode
{
	char				*name;
	int					x;
	int					y;
	int					state;
	struct s_roomnode	*next;
	struct s_roomnode	*prev;
}						t_roomnode;

typedef struct			s_roomdata
{
	int					size;
	t_roomnode			*start;
	t_roomnode			*end;
}						t_roomdata;

typedef struct			s_pipenode
{
	char				*from;
	char				*to;
	struct s_pipenode	*next;
	struct s_pipenode	*prev;
}						t_pipenode;

typedef struct			s_pipedata
{
	int					size;
	t_pipenode			*start;
	t_pipenode			*end;
}						t_pipedata;

typedef struct			s_pathnode
{
	int					*inttab;
	int					size;
	struct s_pathnode	*next;
	struct s_pathnode	*prev;
}						t_pathnode;

typedef struct			s_pathdata
{
	int					size;
	t_pathnode			*start;
	t_pathnode			*end;
}						t_pathdata;

typedef	struct			s_lmdata
{
	t_roomdata			tmproom;
	t_pipedata			tmppipe;
	t_antdata			lstant;
	t_pathdata			path;
	int					ant;
	int					antinend;
	int					start;
	int					end;
	t_tab				map;
	int					cmd;
	int					var_room;
	int					var_diez;
	int					color;
	char				*file;
}						t_lmdata;

int						lm_reed(t_lmdata *data);
int						lm_pushback_room(t_lmdata *data, char *line);
int						lm_pushback_pipe(t_lmdata *data, char *line);
t_roomnode				*lm_selectnode(t_lmdata *data, int state);
int						lm_pb_path(t_lmdata *data, int *inttab, int size);
void					swapdata(t_pathnode *node1, t_pathnode *node2);
int						lstissort(t_pathnode *node);
void					sortpath(t_pathdata data);
int						lm_rec(t_lmdata *data, int line, int col, int *path);
void					lm_solve(t_lmdata *data);
int						lm_searchindex(t_roomdata roomdata, char *name);
char					*lm_searchname(t_roomdata roomdata, int index);
void					deletepathnode(t_pathdata *data, int index);
int						lm_filltab(t_lmdata *data);
void					lm_crossing(t_lmdata *data);
int						lm_pb_ant(t_lmdata *data, int index);
void					free_all(t_lmdata *data);
int						extractant(t_lmdata *data, char *line);
int						already_exist(t_lmdata *data);
int						lm_norme(t_lmdata *data, char *line);

#endif
