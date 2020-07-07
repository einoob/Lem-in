/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:34:22 by elindber          #+#    #+#             */
/*   Updated: 2020/07/07 16:48:50 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	copy_room(t_room *src, t_room *dst)
{
	dst->name = ft_strdup(src->name);
	dst->link_string = ft_strdup(src->link_string);
	dst->start_or_end = src->start_or_end;
	dst->visited = src->visited;
	dst->path = src->path;
	dst->level = src->level;
	dst->y = src->y;
	dst->x = src->x;
}

void	swap_rooms(t_info *info, int a, int b)
{
	t_room	*swap;

	if (!(swap = (t_room*)malloc(sizeof(t_room))))
		exit_error(ERR_MALLOC);
	copy_room(info->rooms[a], swap);
	copy_room(info->rooms[b], info->rooms[a]);
	copy_room(swap, info->rooms[b]);
	free(swap);
}

void	first_from_index(t_info *info, int i)
{
	int		first;
	int		placement;
	
	first = i + 1;
	placement = i;
	while (info->rooms[i] != NULL)
	{
		if (ft_strcmp(info->rooms[i]->name, info->rooms[first]->name) < 0)
			first = i;
		i++;
	}
	swap_rooms(info, first, placement);
	if (info->rooms[placement + 1] != NULL)
	{
		info->rooms[placement]->links = ft_strsplit(info->rooms[placement]->link_string, ' ');
		if (info->rooms[placement]->start_or_end != 0)
		{
			if (info->rooms[placement]->start_or_end == 1)
				info->start_index = placement;
			else
				info->end_index = placement;
		}
	}
}

void	sort_rooms(t_info *info)
{
	int		i;
	int		x;
	
	i = 0;
	x = 0;
	while (info->rooms[i + 1] != NULL)
	{
		first_from_index(info, i);
		i++;
	}
	info->rooms[i]->links = ft_strsplit(info->rooms[i]->link_string, ' ');
	if (info->rooms[i]->start_or_end != 0)
	{
		if (info->rooms[i]->start_or_end == 1)
			info->start_index = i;
		else
			info->end_index = i;
	}
	i = 0;
	while (info->rooms[info->start_index]->links[i] != NULL)
		i++;
	while (info->rooms[info->end_index]->links[x] != NULL)
		x++;
	info->max_paths = i < x ? i : x;
	if (!(info->valid_paths = (char**)malloc(sizeof(char*) * info->max_paths + 1)))
		exit_error(ERR_MALLOC);
	i = 0;
	while (i < info->max_paths + 1)
	{
		info->valid_paths[i] = NULL;
		i++;
	}
}
