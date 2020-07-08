/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:45:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/08 14:05:26 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	create_fork(t_info *info, int room_i, int y)
{
	int		t;
	int		s;
	int		note;
	int		fork;

	t = 0;
	fork = 0;
	note = y;
	while (info->rooms[room_i]->links[t] != NULL)
	{
		s = find_a_room(info, info->rooms[room_i]->links[t]);
		ft_printf("[%d][%s] [%d][%s]\n", info->rooms[room_i]->level, info->rooms[room_i]->name, info->rooms[s]->level, info->rooms[s]->name);
		if (info->rooms[room_i]->level < info->rooms[s]->level &&
		s != info->end_index)
		{
			fork++;
			ft_printf("%d\n", fork);
		}
		t++;
	}
	if (fork > 0)
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
//	ft_printf("info->rooms[next] [%d] %s \n", next, info->rooms[next]->name);
//	ft_printf("info->rooms[last] [%d] %s \n", last, info->rooms[last]->name);
	while (info->paths[y] != NULL)
	{
	//	ft_printf("%s\n", info->paths[y]);
		last_room = last_on_path(info->paths[y]);
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
//		ft_putendl("segg");
		free(last_room);
		y++;
	}
}
