/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:30:44 by elindber          #+#    #+#             */
/*   Updated: 2020/07/27 19:03:21 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Moves ant from the start to the queue.
*/

static void		ant_to_first_room(t_info *info, int i)
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
	free(ant);
	info->rooms[info->valid_indexes[i][0]]->visited = 1;
	info->rooms[info->valid_indexes[i][0]]->ant_id =
	info->rooms[info->valid_indexes[i][0]]->ant_queue[t];
	info->rooms[info->valid_indexes[i][0]]->ant_queue[t] = -1;
	info->ants_at_start--;
}

/*
**	Moves ants on path and prints the L1-2.
*/

static void		move_path(t_info *info, int i)
{
	char	*ant;
	int		t;

	t = info->rooms[info->valid_indexes[i][0]]->length;
	while (--t >= 0)
	{
		if (info->rooms[info->valid_indexes[i][t]]->visited == 1
		&& info->rooms[info->valid_indexes[i][t + 1]]->visited == 0)
		{
			ant = ft_itoa(info->rooms[info->valid_indexes[i][t]]->ant_id);
			ft_printf("L%s-%s ", ant,
			info->rooms[info->valid_indexes[i][t + 1]]->name);
			free(ant);
			info->rooms[info->valid_indexes[i][t + 1]]->ant_id =
			info->rooms[info->valid_indexes[i][t]]->ant_id;
			info->rooms[info->valid_indexes[i][t + 1]]->visited =
			info->valid_indexes[i][t + 1] == info->end_index ? 0 : 1;
			if (info->valid_indexes[i][t + 1] == info->end_index)
				info->ants_at_end++;
			info->rooms[info->valid_indexes[i][t]]->visited = 0;
			info->rooms[info->valid_indexes[i][t]]->ant_id = 0;
		}
	}
	if (info->ants_at_start > 0)
		ant_to_first_room(info, i);
}

/*
**	Runs turns of ant flow.
*/

static void		print_turns(t_info *info)
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
		if (i == info->path_amount_1)
		{
			i = 0;
			info->lines++;
			ft_putchar('\n');
		}
	}
}

/*
**	Helper for D_T_P1. Increment and decrement variables in struct.
*/

static int		divide_paths_1_data(t_info *info, int antnb, int i, int tab)
{
	tab = info->rooms[info->valid_indexes[i][0]]->ants;
	info->rooms[info->valid_indexes[i][0]]->ant_queue[tab] = antnb;
	info->rooms[info->valid_indexes[i][0]]->ants++;
	info->rooms[info->valid_indexes[i][0]]->cost++;
	info->ants_at_start--;
	return (tab);
}

/*
**	Helper for D_T_P2. Increment and decrement variables in struct.
*/

static int		divide_paths_2_data(t_info *info, int antnb, int i, int tab)
{
	tab = info->rooms[info->valid_indexes_2[i][0]]->ants_2;
	info->rooms[info->valid_indexes_2[i][0]]->ant_queue_2[tab] = antnb;
	info->rooms[info->valid_indexes_2[i][0]]->ants_2++;
	info->rooms[info->valid_indexes_2[i][0]]->cost_2++;
	info->ants_at_start--;
	return (tab);
}

/*
**	Helper for D_T_P1.
*/

// static int		cmp_loop_1(t_info *info, int cmp, int i)
// {
// 	cmp = info->rooms[info->valid_indexes[i][0]]->cost;
// 	i = 0;
// 	while (info->rooms[info->valid_indexes[i][0]]->cost > cmp)
// 		i++;
// 	return (i);
// }

/*
**	Helper for D_T_P2.
*/

// static int		cmp_loop_2(t_info *info, int cmp, int i)
// {
// 	cmp = info->rooms[info->valid_indexes_2[i][0]]->cost_2;
// 	i = 0;
// 	while (info->rooms[info->valid_indexes_2[i][0]]->cost_2 > cmp)
// 		i++;
// 	return (i);
// }

/*
**	Divides ants to paths during first ant flow.
*/

static void		divide_to_paths_1(t_info *info, int i, int tab, int cmp)
{
	int		antnb;

	antnb = 1;
	while (info->ants_at_start > 0)
	{
		if (info->path_amount_1 == 1)
			tab = divide_paths_1_data(info, antnb++, i, tab);
		else if (info->rooms[info->valid_indexes[i][0]]->cost
		<= info->rooms[info->valid_indexes[i + 1][0]]->cost)
		{
			if (info->rooms[info->valid_indexes[i][0]]->cost
			== info->rooms[info->valid_indexes[i + 1][0]]->cost)
			{
				cmp = info->rooms[info->valid_indexes[i][0]]->cost;
				i = 0;
				while (info->rooms[info->valid_indexes[i][0]]->cost > cmp)
					i++;
				// i = cmp_loop_1(info, cmp, i);
			}
			tab = divide_paths_1_data(info, antnb++, i, tab);
		}
		else if (info->rooms[info->valid_indexes[i][0]]->cost
		> info->rooms[info->valid_indexes[i + 1][0]]->cost)
			tab = divide_paths_1_data(info, antnb++, ++i, tab);
		if (i == info->path_amount_1 - 1
		|| info->rooms[info->valid_indexes[i][0]]->cost
		< info->rooms[info->valid_indexes[i + 1][0]]->cost)
			i = 0;
	}
}

/*
**	Divides ants to paths during first ant flow.
*/

void		divide_to_paths_2(t_info *info, int i, int tab, int cmp)
{
	int		antnb;

	antnb = 1;
	while (info->ants_at_start > 0)
	{
		if (info->path_amount_2 == 1)
			tab = divide_paths_2_data(info, antnb++, i, tab);
		else if (info->rooms[info->valid_indexes_2[i][0]]->cost_2
		<= info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
		{
			if (info->rooms[info->valid_indexes_2[i][0]]->cost_2
			== info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
			{
				cmp = info->rooms[info->valid_indexes_2[i][0]]->cost_2;
				i = 0;
				while (info->rooms[info->valid_indexes_2[i][0]]->cost_2 > cmp)
					i++;
				// i = cmp_loop_2(info, cmp, i);
			}
			tab = divide_paths_2_data(info, antnb++, i, tab);
		}
		else if (info->rooms[info->valid_indexes_2[i][0]]->cost_2
		> info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
			tab = divide_paths_2_data(info, antnb++, ++i, tab);
		if (i == info->path_amount_2 - 1
		|| info->rooms[info->valid_indexes_2[i][0]]->cost_2
		< info->rooms[info->valid_indexes_2[i + 1][0]]->cost_2)
			i = 0;
	}
}

/*
**	Resets rooms.
*/

static void		reset_room_statuses(t_info *info, int y, int i)
{
	while (info->valid_indexes[y][0] != EMPTY)
	{
		while (info->valid_indexes[y][i] != EMPTY)
		{
			info->rooms[info->valid_indexes[y][i]]->visited = 0;
			i++;
		}
		i = 0;
		y++;
	}
	y = 0;
	while (info->valid_indexes_2[y][0] != EMPTY)
	{
		while (info->valid_indexes_2[y][i] != EMPTY)
		{
			info->rooms[info->valid_indexes_2[y][i]]->visited = 0;
			i++;
		}
		i = 0;
		y++;
	}
}

/*
**	Main ant_flow dispatcher.
*/

void			ant_flow(t_info *info)
{
	int		i;
	int		t;

	i = 0;
	t = 0;
	reset_room_statuses(info, 0, 0);
	info->ants_at_start = info->ants;
	divide_to_paths_1(info, 0, 0, 0);
	info->ants_at_start = info->ants;
//	if (info->valid_indexes_2[0][0] != EMPTY)
///		divide_to_paths_2(info, 0, 0, 0);
	info->ants_at_start = info->ants;
//	if (info->path_amount_2 > 0 && info->rooms[info->valid_indexes[0][0]]->cost
//	> info->rooms[info->valid_indexes_2[0][0]]->cost_2)
//		print_turns_2(info);
//	else
		print_turns(info);
}
