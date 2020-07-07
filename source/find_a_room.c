/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_a_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 14:15:12 by elindber          #+#    #+#             */
/*   Updated: 2020/07/07 14:31:03 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		find_a_room(t_info *info, char *to_find)
{
	int		start;
	int		end;
	int		cmp;

	start = 0;
	end = info->room_amnt - 1;
	cmp = end / 2;
	while (start <= end)
	{
		if (ft_strcmp(info->rooms[cmp]->name, to_find) == 0)
			return (cmp);
		else if (ft_strcmp(info->rooms[cmp]->name, to_find) > 0)
		{
			end = cmp - 1;
			cmp /= 2;
		}
		else
		{
			start = cmp + 1;
			cmp = start + ((end - start) / 2); 
		}
	}
	return (-1);
}