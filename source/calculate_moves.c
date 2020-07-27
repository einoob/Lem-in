/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:33:19 by elindber          #+#    #+#             */
/*   Updated: 2020/07/27 20:14:40 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		reset_valid_indexes_2(t_info *info)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (y < info->max_paths + 1)
	{
		while (i < 513)
		{
			if (info->valid_indexes_2[y][i] > 0)
			{
				info->rooms[info->valid_indexes_2[y][i]]->length_2 = 0;
				info->rooms[info->valid_indexes_2[y][i]]->cost_2 = 0;
				info->rooms[info->valid_indexes_2[y][i]]->path_2 = -1;
			}
			info->valid_indexes_2[y][i] = EMPTY;
			i++;
		}
		i = 0;
		y++;
	}
	info->path_amount_2 = 0;
}

void		change_path_sets(t_info *info)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (y < info->max_paths + 1)
	{
		while (i < 513)
		{
			info->valid_indexes[y][i] = info->valid_indexes_2[y][i];
			if (info->valid_indexes[y][i] != EMPTY)
			{
				info->rooms[info->valid_indexes[y][i]]->length = info->rooms[info->valid_indexes[y][i]]->length_2;
				info->rooms[info->valid_indexes[y][i]]->cost = info->rooms[info->valid_indexes[y][i]]->cost_2;
				info->rooms[info->valid_indexes[y][i]]->path = info->rooms[info->valid_indexes[y][i]]->path_2;
				info->rooms[info->valid_indexes[y][i]]->path_2 = -1;
			}
			info->valid_indexes_2[y][i] = EMPTY;
			i++;
		}
		y++;
		i = 0;
	}
	info->path_amount_1 = info->path_amount_2;
	info->last_found_used = info->last_found_used_2;
	info->last_found_used_2 = 1;
	info->path_amount_2 = 0;
}

void		calculate_moves(t_info *info)
{
	int		i;
	int		rooms;
	int		moves;
	int		cmp;
	int		div;

	i = 0;
	rooms = 0;
	if (info->path_amount_2 < 1)
	{
		reset_valid_indexes_2(info);
		return ;
	}
	ft_printf("using last path 1=%d 2=%d\n", info->last_found_used, info->last_found_used_2);
	while (i < info->path_amount_1)
	{
		rooms += info->rooms[info->valid_indexes[i][0]]->length;
		i++;
	}
	rooms -= info->last_found_used == 1 ? 0 : info->rooms[info->valid_indexes[i - 1][0]]->length;
	div = info->last_found_used == 1 ? info->path_amount_1 : info->path_amount_1 - 1;
	moves = (rooms + info->ants) / (div);
	moves += (rooms + info->ants) % (div) ? 1 : 0;
	i = 0;
	rooms = 0;
	while (i < info->path_amount_2)
	{
		rooms += info->rooms[info->valid_indexes_2[i][0]]->length_2;
		i++;
	}
	rooms -= info->last_found_used_2 == 1 ? 0 : info->rooms[info->valid_indexes_2[i - 1][0]]->length_2;
	div = info->last_found_used_2 == 1 ? info->path_amount_2 : info->path_amount_2 - 1;
	cmp = (rooms + info->ants) / (div);
	cmp += (rooms + info->ants) % (div) ? 1 : 0;
	ft_printf("%d %d\n", moves, cmp);
	if (cmp < moves)
	{
		ft_printf("><><><><><><><C H A N G I N G   P A T H   S E T><><><><><><><><><><\n");
		change_path_sets(info);
	}
	else
		reset_valid_indexes_2(info);
}