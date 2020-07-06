/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:45:46 by elindber          #+#    #+#             */
/*   Updated: 2020/07/06 12:59:42 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		room_on_valid_path(t_info *info, char *room)
{
	char	**path;
	int		y;
	int		i;

	y = 0;
	i = 0;
//	ft_printf("%s\n", info->valid_paths[1]);
	while (y < info->path_amount)
	{
		path = ft_strsplit(info->valid_paths[y], ' ');
		while (path[i] != NULL)
		{
			if (ft_strequ(path[i], room) && !(ft_strequ(info->end, room)))
			{
			//	ft_printf("room deleting: [%s] [%s]\n", room, path[i]);
				free_2d_array(path);
				return (1);
			}
			i++;
		}
		free_2d_array(path);
		i = 0;
		y++;
	}
	return (0);
}

void	reset_rooms(t_info *info)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	info->level = 1;
	while (info->rooms[i] != NULL)
	{
		if (room_on_valid_path(info, info->rooms[i]->name))
			info->rooms[i]->visited = 3;
		else
			info->rooms[i]->visited = 0;
		i++;
	}
	info->path_stack = 0;
}
