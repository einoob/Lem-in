/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:45:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/27 17:16:22 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		exact_same_path(t_info *info, int path_i)
{
	int		y;
	int		t;

	y = 0;
	t = 0;
//	if (info->path_amount_1 == 0)
//		return (0);
	while (info->valid_indexes[y][0] != EMPTY)
	{
		while (info->valid_indexes[y][t] == info->index_stack[path_i][t])
		{
			t++;
			if (info->valid_indexes[y][t] == EMPTY
			&& info->index_stack[path_i][t] == EMPTY)
				return (1);
		}
		t = 0;
		y++;
	}
	return (0);
}

void	create_fork(t_info *info, int room_i, int y, int t)
{
	int		s;
	int		note;
	int		fork;

	fork = 0;
	note = y;
	while (info->rooms[room_i]->links[t] != NULL && fork == 0)
	{
		s = find_a_room(info, info->rooms[room_i]->links[t]);
		if ((info->rooms[room_i]->level <= info->rooms[s]->level
		|| info->rooms[s]->level == -1) && s != info->end_index)
			fork++;
		else if (info->phase == 2 && s != info->end_index)
			fork++;
		t++;
	}
	if (fork > 0)
	{
		t = 0;
		while (info->index_stack[y][0] != EMPTY)
			y++;
		while (info->index_stack[note][t] != EMPTY)
		{
			info->index_stack[y][t] = info->index_stack[note][t];
			t++;
		}
	}
}

int		last_on_path(int *path)
{
	int		i;

	i = 0;
	while (path[i + 1] != EMPTY)
		i++;
	return (path[i]);
}

void	add_to_path(t_info *info, int last, int next, int y)
{
	int		last_room;
	int		i;

	i = 0;
	if (info->rooms[last]->flow == 1 && info->rooms[next]->flow == 1)
		return ;
//	if (next == info->end_index && info->phase == 2)
//		ft_printf("%d=2 %d=-1\n", info->phase, info->rooms[last]->path_2);
		//	ft_printf("%d=2 %d=-1 %d=%d\n", info->phase, info->rooms[last]->path_2, last_room, last);
	while (info->index_stack[++y][0] != EMPTY)
	{
		last_room = last_on_path(info->index_stack[y]);
		if ((info->phase == 1 && info->rooms[last]->path < 0 && last_room
		== last) || (info->phase == 2 && info->rooms[last]->path_2 < 0
		&& last_room == last))
		{
		//	if (info->round > 0)
		//		ft_printf("%s %d %d %s %d %d\n", info->rooms[last]->name, info->rooms[last]->level, info->rooms[last]->visited, info->rooms[next]->name, info->rooms[next]->level, info->rooms[next]->visited);
			create_fork(info, last, y, 0);
			while (info->index_stack[y][i] != EMPTY)
				i++;
			info->index_stack[y][i] = next;
			if (next == info->end_index)
				save_path(info, y);
			return ;
		}
	}
}
