/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:04:26 by elindber          #+#    #+#             */
/*   Updated: 2020/07/06 18:10:40 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
void	set_visited(t_info *info, char *tmp_room, int i)
{
	while (info->rooms[i] != NULL)
	{
		if (ft_strequ(info->rooms[i]->name, tmp_room) && info->rooms[i]->visited == 0)
		{
		//	ft_printf("    setting visited:[%s] with lvl[%d]\n", tmp_room, info->level);
			info->rooms[i]->visited++;
			if (info->rooms[i]->level < 0)
			{
				info->rooms[i]->level = info->level;
			}
			return ;
		}
		i++;
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

void	get_paths(t_info *info, int h, int i)
{
	char	*tmp_room;
	int		y;

	y = 0;
	if (info->path_amount == info->max_paths)
		return ;
	while (info->rooms[i] != NULL && info->end_reached == 0)
	{
		if (ft_strequ(info->rooms_to_check[h], info->rooms[i]->name))
		{
		//	ft_printf("in room:[%s] lvl[%d]\n", info->rooms_to_check[h], info->rooms[i]->level);
			info->rooms[i]->visited++;
			while (info->rooms[i]->links[y] != NULL && info->end_reached == 0)
			{
				tmp_room = ft_strdup(info->rooms[i]->links[y]);
				set_visited(info, tmp_room, 0);
				if (ft_strequ(tmp_room, info->end))
				{
					info->end_reached++;
					ft_printf("\n\tEND IS: %s readched from %s [level:%d]\n", tmp_room, info->rooms[i]->name, info->rooms[i]->level);
				}
				add_to_path(info, tmp_room, i);
				free(tmp_room);
				y++;
			}
			y = 0;
		}
		i++;
	}
	h++;
	if (info->rooms_to_check[h] != NULL )
		get_paths(info, h, 0);
	else if (info->end_reached == 1)
		save_path(info);
}

void	rooms_to_check(t_info *info, int i)
{
	char	*room_list;
	char	*tmp;
	char	*add;
	int		count;

	count = 0;
	room_list = ft_strnew(0);
	free_2d_array(info->rooms_to_check);
	while (info->rooms[i] != NULL)
	{
		if (info->rooms[i]->visited == 1)
		{
			add = ft_strjoin(info->rooms[i]->name, " ");
			tmp = ft_strjoin(room_list, add);
			ft_strdel(&room_list);
			room_list = ft_strdup(tmp);
			free(tmp);
			free(add);
		}
		i++;
	}
	info->rooms_to_check = ft_strsplit(room_list, ' ');
	ft_strdel(&room_list);
}

int		not_on_valid_path(t_info *info, char *cmp)
{
	char	**path;
	int		y;

	y = 0;
	while (info->valid_paths[y] != NULL)
	{
		path = ft_strsplit(info->valid_paths[y], ' ');
		if (ft_strequ(path[0], cmp))
		{
			ft_printf("[%s] <-> [%s]\n", path[0], cmp);
			return (0);
		}
		free_2d_array(path);
		y++;
	}
	return (1);
}

void	get_links_for_start(t_info *info, int h, int i)
{
	char	*tmp_room;
	int		start;

	while (info->rooms[i] != NULL)
	{
		if (ft_strequ(info->rooms[i]->name, info->start))
		{
			info->rooms[i]->visited = 2;
			start = i;
		}
		i++;
	}
//	ft_printf("in start room [%s]\n", info->rooms[start]->name);
	while (info->rooms[start]->links[h] != NULL)
	{
		tmp_room = ft_strdup(info->rooms[start]->links[h]);
		if (h <= info->max_paths && not_on_valid_path(info, tmp_room))
		{
			info->paths[h] = ft_strjoin(tmp_room, " ");
			set_visited(info, tmp_room, 0);
		}
		free(tmp_room);
		h++;
		info->path_stack++;
	}
}

int		link_amount(t_info *info, int i)
{
	int		y;

	y = 0;
	while (info->rooms[i]->links[y] != NULL)
		y++;
	return (y);
}

void	get_links_for_room(t_info *info, int i)
{
	char	*links;
	char	*tmp;
	char	*add;
	int		x;

	x = 0;
	links = ft_strnew(0);
	while (info->links[x] != NULL)
	{
		if (ft_strequ(info->rooms[i]->name, info->links[x][0]))
		{
			add = ft_strjoin(info->links[x][1], " ");
			tmp = ft_strjoin(links, add);
			ft_strdel(&links);
			links = ft_strdup(tmp);
			free(tmp);
			free(add);
		}
		else if (ft_strequ(info->rooms[i]->name, info->links[x][1]))
		{
			add = ft_strjoin(info->links[x][0], " ");
			tmp = ft_strjoin(links, add);
			ft_strdel(&links);
			links = ft_strdup(tmp);
			free(tmp);
			free(add);
		}
		x++;
	}
	info->rooms[i]->links = ft_strsplit(links, ' ');
	ft_strdel(&links);
	if (info->rooms[i]->start_or_end > 0)
		info->max_paths = info->max_paths > link_amount(info, i) ? link_amount(info, i) : info->max_paths;
}

void	get_links_for_rooms(t_info *info, int i)
{
	while (info->rooms[i] != NULL)
	{
		get_links_for_room(info, i);
		i++;
	}
	i = info->link_amnt;
	ft_printf("max_paths %d\n", info->max_paths);
	if (!(info->paths = (char**)malloc(sizeof(char*) * (info->link_amnt + 1))) ||
	!(info->valid_paths = (char**)malloc(sizeof(char*) * info->max_paths + 1)))
		exit_error(ERR_MALLOC);
	while (i >= 0)
	{
		info->paths[i] = NULL;
		i--;
	}
	i = 0;
	while (i <= info->max_paths)
	{
		info->valid_paths[i] = NULL;
		i++;
	}
}

void	get_links(t_info *info)
{
	int		i;

	i = 0;
	if (info->path_amount == 0)
		get_links_for_rooms(info, i);
//	if (!(info->paths = (char**)malloc(sizeof(char*) * info->link_amnt + 1)))
//		exit_error(ERR_MALLOC);
	get_links_for_start(info, 0, 0);
//	ft_printf("max path amnt is %d round: %d\n", info->max_paths, info->path_amount);
	while (!info->end_reached)	//this condition will change maybe
	{
		info->level++;
		rooms_to_check(info, 0);
		int x = 0;
		ft_printf("checking rooms: ");
		while (info->rooms_to_check[x] != NULL)
		{
			ft_printf("[%s] ", info->rooms_to_check[x]);
			x++;
		}
		ft_putendl("\n");
		if (info->rooms_to_check[0] == NULL)
			break ;
		get_paths(info, 0, 0);
	}
//	print_paths(info);
//	ft_putchar('\n');
//	ant_flow(info);
}
*/
/*
		int x = 0;
		ft_printf("checking rooms: ");
		while (info->rooms_to_check[x] != NULL)
		{
			ft_printf("[%s] ", info->rooms_to_check[x]);
			x++;
		}
		ft_putchar('\n');
*/
