/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:30:44 by elindber          #+#    #+#             */
/*   Updated: 2020/07/14 17:57:21 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ant_to_first_room(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = 0;
	while (info->rooms[info->valid_indexes[i][0]]->ant_queue[t] == -1)
		t++;
	if (info->rooms[info->valid_indexes[i][0]]->ant_queue[t] <= 0)
		return ;
	ant = ft_itoa(info->rooms[info->valid_indexes[i][0]]->ant_queue[t]);
	ft_printf("L%s-%s ", ant, info->rooms[info->valid_indexes[i][0]]->name);
//	ft_printf("L%s-%s\n", ant, info->rooms[info->valid_indexes[i][0]]->name);
	free(ant);
	info->rooms[info->valid_indexes[i][0]]->visited = 1;
	info->rooms[info->valid_indexes[i][0]]->ant_id = info->rooms[info->valid_indexes[i][0]]->ant_queue[t];
	info->rooms[info->valid_indexes[i][0]]->ant_queue[t] = -1;
	info->ants_at_start--;
}

void	move_path(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = info->rooms[info->valid_indexes[i][0]]->length - 1;
	while (t >= 0)
	{
		if (info->rooms[info->valid_indexes[i][t]]->ant_id > 0 && /*info->rooms[info->valid_indexes[i][t]]->ant_id <= info->ants &&*/ info->rooms[info->valid_indexes[i][t]]->visited == 1 && info->rooms[info->valid_indexes[i][t + 1]]->visited == 0)
		{
			ant = ft_itoa(info->rooms[info->valid_indexes[i][t]]->ant_id);
			ft_printf("L%s-%s ", ant, info->rooms[info->valid_indexes[i][t + 1]]->name);
			free(ant);
			info->rooms[info->valid_indexes[i][t + 1]]->ant_id = info->rooms[info->valid_indexes[i][t]]->ant_id;
			info->rooms[info->valid_indexes[i][t + 1]]->visited = info->valid_indexes[i][t + 1] == info->end_index ? 0 : 1;
			if (info->valid_indexes[i][t + 1] == info->end_index)
				info->ants_at_end++;
			info->rooms[info->valid_indexes[i][t]]->visited = 0;
			info->rooms[info->valid_indexes[i][t]]->ant_id = 0;
		}
		t--;
	}
	if (info->ants_at_start > 0)
		ant_to_first_room(info, i);
}

void	print_turns(t_info *info)
{
	int		i;

	i = 0;
	while (info->ants_at_end < info->ants)
	{
		move_path(info, i);
		i++;
		if (info->ants_at_end == info->ants)
		{
			if (i != 0)
				ft_putchar('\n');
			return ;
		}
		if (i == info->path_amount)
		{
			i = 0;
			info->lines++;
			ft_putchar('\n');
		}
	}
}

void	divide_to_paths(t_info *info)
{
	int		i;
	int		ant_nbr;
	int		tab;
	int		cmp;

	i = 0;
	cmp = 0;
	ant_nbr = 1;
	while (info->ants_at_start > 0)
	{
		if (info->path_amount == 1)
		{
			tab = info->rooms[info->valid_indexes[i][0]]->ants;
			info->rooms[info->valid_indexes[i][0]]->ant_queue[tab] = ant_nbr;
			info->rooms[info->valid_indexes[i][0]]->ants++;
			info->rooms[info->valid_indexes[i][0]]->cost++;
			info->ants_at_start--;
			ant_nbr++;
		}
		else if (info->rooms[info->valid_indexes[i][0]]->cost <= info->rooms[info->valid_indexes[i + 1][0]]->cost)
		{
			if (info->rooms[info->valid_indexes[i][0]]->cost == info->rooms[info->valid_indexes[i + 1][0]]->cost)
			{
				cmp = info->rooms[info->valid_indexes[i][0]]->cost;
				i = 0;
				while (info->rooms[info->valid_indexes[i][0]]->cost > cmp)
					i++;
			}
			tab = info->rooms[info->valid_indexes[i][0]]->ants;
			info->rooms[info->valid_indexes[i][0]]->ant_queue[tab] = ant_nbr;
			info->rooms[info->valid_indexes[i][0]]->ants++;
			info->rooms[info->valid_indexes[i][0]]->cost++;
			info->ants_at_start--;
			ant_nbr++;
		}
		else if (info->rooms[info->valid_indexes[i][0]]->cost > info->rooms[info->valid_indexes[i + 1][0]]->cost)
		{
			i++;
			tab = info->rooms[info->valid_indexes[i][0]]->ants;
			info->rooms[info->valid_indexes[i][0]]->ant_queue[tab] = ant_nbr;
			info->rooms[info->valid_indexes[i][0]]->ants++;
			info->rooms[info->valid_indexes[i][0]]->cost++;
			info->ants_at_start--;
			ant_nbr++;
		}
		if (i == info->path_amount - 1 || info->rooms[info->valid_indexes[i][0]]->cost < info->rooms[info->valid_indexes[i + 1][0]]->cost)
			i = 0;
	}
	info->ants_at_start = info->ants;
}

void	reset_room_statuses(t_info *info)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (y < info->path_amount && info->valid_indexes[y][0] != EMPTY)
	{
		while (info->valid_indexes[y][i] != EMPTY)
		{
			info->rooms[info->valid_indexes[y][i]]->visited = 0;
			i++;
		}
		i = 0;
		y++;
	}
}

void	ant_flow(t_info *info)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	reset_room_statuses(info);
	info->ants_at_start = info->ants;
	divide_to_paths(info);
/*	while (info->valid_indexes[i][0] != EMPTY)
	{
		ft_printf("room[%s] queue: ", info->rooms[info->valid_indexes[i][0]]->name);
		while (info->rooms[info->valid_indexes[i][0]]->ant_queue[t] != 0)
		{
			ft_printf("[%d]", info->rooms[info->valid_indexes[i][0]]->ant_queue[t]);
			t++;
		}
		ft_putchar('\n');
		i++;
		t = 0;
	}*/
	print_turns(info);
}
