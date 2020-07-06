/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:45:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/06 18:11:44 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
/*
int		link_level(t_info *info, char *cmp_room, int level)
{
	int	i;

	i = 0;
	while (info->rooms[i] != NULL)
	{
		if (ft_strequ(info->rooms[i]->name, cmp_room))
		{
			return(info->rooms[i]->level >= level);
		}
		i++;
	}
	return (0);
}

int		link_not_visited(t_info *info, char *cmp_room, int level)
{
	int		i;

	i = 0;
	level++;
	while (info->rooms[i] != NULL)
	{
		if (ft_strequ(info->rooms[i]->name, cmp_room))
		{
			return (info->rooms[i]->visited > 0
			|| info->rooms[i]->start_or_end == 2);
		}
		i++;
	}
	return (0);
}

void	create_fork(t_info *info, int i, int y)
{
	char	*duplicate;
	char	*tmp;
	int		x;

	x = 0;
	duplicate = ft_strdup(info->paths[y]);
	y = 0;
//	ft_printf("room: %s\n", info->rooms[i]->name);
	while (info->rooms[i]->links[x] != NULL)
	{
		if (link_not_visited(info, info->rooms[i]->links[x], info->rooms[i]->level))
		{
			while (info->paths[y] != NULL)
				y++;
			tmp = ft_strdup(duplicate);
			info->paths[y] = ft_strdup(tmp);
			free(tmp);
			info->path_stack++;
		}
		x++;
	}
//	ft_putchar('\n');
	free(duplicate);
}

void	add_to_path(t_info *info, char *add_room, int i)
{
	char	*tmp;
	char	*add;
	char	*last;
	int		y;

	y = 0;
//	ft_printf("room[%s] level[%d]\n", info->rooms[i]->name, info->rooms[i]->level);
	while (info->paths[y] != NULL) //&& !(ft_strequ(add_room, info->start)))
	{
//		ft_printf("%d %d\n", y, info->path_stack);
   //     ft_printf("%s\n", info->paths[y]);
		last = last_on_path(info->paths[y]);
		if (ft_strequ(last, info->rooms[i]->name)
		&& link_level(info, add_room, info->rooms[i]->level))
		{
			create_fork(info, i, y);
			add = ft_strjoin(add_room, " ");
			tmp = ft_strjoin(info->paths[y], add);
			free(info->paths[y]);
			info->paths[y] = ft_strdup(tmp);
			free(tmp);
			free(add);
			break ;
		}
//		ft_printf("path[%d] %s\tlast: [%s]\n", y, info->paths[y], last);
		free(last);
		y++;
	}
//	y = 0;
//	while (y < info->path_stack)
//	{
//		ft_printf("path[%d] %s\tlast: [%s]\n", y, info->paths[y], last);
//		y++;
//	}
}
*/