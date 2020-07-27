/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_path_finding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:56:46 by elindber          #+#    #+#             */
/*   Updated: 2020/07/27 19:14:38 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	from_the_middle(t_info *info, int direction)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
//	direction == 2 ? ft_printf("third round\n") : ft_printf("fourth round\n");
	while (info->check_rooms[i] != EMPTY)
	{
		info->tmp_string[i] = info->check_rooms[i];
		info->check_rooms[i] = EMPTY;
		i++;
	}
	i /= 2;
	while (direction == 2 && info->tmp_string[i] != EMPTY)
	{
		info->check_rooms[t] = info->tmp_string[i];
		info->tmp_string[i] = EMPTY;
		i++;
		t++;
		i = info->tmp_string[i] == EMPTY ? 0 : i;
	}
	while (direction == 1 && i >= 0)
	{
		info->check_rooms[t] = info->tmp_string[i];
		info->tmp_string[i] = EMPTY;
		i--;
		t++;
		if (i == -1)
		{
			i = 512;
			while (info->tmp_string[i] == EMPTY)
				i--;
		}
	}
}

void	reorder_check_rooms(t_info *info)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	if (info->round == 2)
	{
//		ft_printf("second round\n");
		while (info->check_rooms[i] != EMPTY)
		{
			info->tmp_string[i] = info->check_rooms[i];
			i++;
		}
		while (--i >= 0)
			info->check_rooms[i] = info->tmp_string[t++];
	}
	else if (info->round == 3)
		from_the_middle(info, 2);
	else
		from_the_middle(info, 1);
	i = -1;
	while (++i < 513)
		info->tmp_string[i] = EMPTY;
}

void	find_paths(t_info *info, int i, int j, int s)
{
	int		l;

	while (info->check_rooms[++i] != EMPTY && info->path_saved == 0)
	{
		s = info->check_rooms[i];
		while (info->rooms[s]->links[j] != NULL
		&& info->path_saved == 0)
		{
			l = find_a_room(info,
			info->rooms[s]->links[j++]);
			if (info->rooms[l]->visited == 0)
				set_visited(info, s, l);
			if (l == info->end_index)
				break ;
		}
		info->rooms[s]->visited++;
		j = 0;
	}
	start_over_or_continue(info, l);
}

void	get_links_for_start(t_info *info, int i, int s, int t)
{
	while (s < 513)
	{
		info->check_rooms[s] = EMPTY;
		s++;
	}
	while (info->rooms[info->start_index]->links[i] != NULL)
	{
		s = find_a_room(info, info->rooms[info->start_index]->links[i]);
		if (info->rooms[s]->visited == 0)
		{
			info->rooms[s]->visited = 1;
			info->rooms[s]->level = info->level;
			info->index_stack[t][0] = s;
			info->check_rooms[t] = s;
			t++;
		}
		i++;
	}
	if (info->round > 1)
	{
	//	ft_printf("reordering\n");
		reorder_check_rooms(info);
	}
	info->rooms[info->start_index]->visited = 2;
	info->level++;
	i = 0;
//	ft_printf("check rooms: ");
	while (info->check_rooms[i] != EMPTY)
	{
	//	ft_printf("[%s]", info->rooms[info->check_rooms[i]]->name);
		i++;
	}
//	ft_putchar('\n');
}
