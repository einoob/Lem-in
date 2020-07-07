/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:45:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/07 17:34:37 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	create_fork(t_info *info, int room_i, int y)
{
	int		t;
	int		note;

	t = 0;
	note = y;
	while (info->rooms[room_i]->links[t] != NULL)
		t++;
	if (t > 2)
	{
		while (info->paths[y] != NULL)
			y++;
		info->paths[y] = ft_strdup(info->paths[note]);
	}
}

char	*last_on_path(char *path)
{
	char	*res;
	char	*tmp;
	int		i;
	
	tmp = ft_strtrim(path);
	i = ft_strlen(tmp);
	if (i == 0)
	    return (NULL);
	while (i > -1 && tmp[i] != ' ')
		i--;
	i++;
	res = ft_strsub(tmp, i, ft_strlen(tmp) - i);
	ft_strdel(&tmp);
	return (res);
}

void	add_to_path(t_info *info, int last, int next)
{
	char	*last_room;
	char	*tmp;
	char	*add;
	int		y;
	
	y = 0;
	while (info->paths[y] != NULL)
	{
		last_room = last_on_path(info->paths[y]);
	//	ft_printf("%s\n", info->paths[y]);
		if (/*(info->rooms[last]->level >= info->rooms[next]->level
		|| info->rooms[last]->level == info->rooms[next]->level + 1)
		&& */info->paths[y][0] != '#' && ft_strequ(last_room, info->rooms[last]->name))
		{
			create_fork(info, last, y);
			add = ft_strjoin(info->rooms[next]->name, " ");
			tmp = ft_strjoin(info->paths[y], add);
			free(info->paths[y]);
			info->paths[y] = ft_strdup(tmp);
			free(add);
			free(tmp);
	//		ft_printf("path[%d] %s [%s]\n", y, info->paths[y], info->rooms[next]->name);
			if (ft_strequ(info->end, info->rooms[next]->name))
				save_path(info, y);
			free(last_room);
			return ;
		}
		free(last_room);
		y++;
	}
}

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