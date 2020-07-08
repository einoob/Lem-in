/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:52:21 by elindber          #+#    #+#             */
/*   Updated: 2020/07/08 14:04:14 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_to_next_round(t_info *info, int i)
{
	char	*add;
	char	*tmp;

	if (i == info->end_index)
		return ;
	add = ft_strjoin(info->rooms[i]->name, " ");
	tmp = ft_strjoin(info->tmp_string, add);
	free(info->tmp_string);
	info->tmp_string = ft_strdup(tmp);
	free(add);
	free(tmp);
}

void	find_paths(t_info *info)
{
	int		i;
	int		j;
	int		l;
	int		s;

	i = 0;
	j = 0;
	while (info->rooms_to_check[i] != NULL && info->end_reached == 0)
	{
		s = find_a_room(info, info->rooms_to_check[i]);
		if (s < 0)
		{
			ft_printf("looking for [%s] at [%d], got index %d\n", info->rooms_to_check[i], i, s);
		    return ;
		}
		while (info->rooms[s]->links[j] != NULL)
		{
			l = find_a_room(info, info->rooms[s]->links[j]);
			if (info->rooms[l]->visited == 0)
			{
				info->rooms[l]->visited = info->rooms[l]->start_or_end == 2 ? 0 : 1;
				info->rooms[l]->level = info->rooms[l]->start_or_end == 2 ? INT_MAX : info->level;
			//	ft_printf("[%d][%s] to [%d][%s]\n", info->rooms[s]->level, info->rooms[s]->name, info->rooms[l]->level, info->rooms[l]->name);
				add_to_path(info, s, l);
				add_to_next_round(info, l);
			}
			j++;
		}
		j = 0;
		i++;
	}
	free_2d_array(info->rooms_to_check);
	if (info->tmp_string[0] != '\0')
	{
		info->rooms_to_check = ft_strsplit(info->tmp_string, ' ');
		free(info->tmp_string);
		info->tmp_string = ft_strnew(0);
	}
	info->level++;
	if (info->end_reached == 0)
		find_paths(info);
}

int		get_links_for_start(t_info *info)
{
	char	*tmp;
	char	*add;
	char	*room_list;
	int		i;
	int		s;

	i = 0;
	room_list = ft_strnew(0);
	while (info->rooms[info->start_index]->links[i] != NULL)
	{
		s = find_a_room(info, info->rooms[info->start_index]->links[i]);
	//	ft_printf("room %s is in index %d\n", info->rooms[info->start_index]->links[i], s);
		if (info->rooms[s]->visited == 0)
		{
			info->rooms[s]->visited = 1;
			info->rooms[s]->level = info->level;
			info->paths[i] = ft_strjoin(info->rooms[s]->name, " ");
			add = ft_strjoin(info->rooms[s]->name, " ");
			tmp = ft_strjoin(room_list, add);
			free(room_list);
			room_list = ft_strdup(tmp);
			free(tmp);
			free(add);
		}
		i++;
	}
	info->rooms[info->start_index]->visited = 2;
	info->rooms_to_check = ft_strsplit(room_list, ' ');
	free(room_list);
	info->level++;
	return (1);
}

void	get_links(t_info *info)
{
	int		i;
	int		t;
	
	i = 0;
	t = 0;
	if (!(info->paths = (char**)malloc(sizeof(char*) * info->link_amnt + 1)))
		exit_error(ERR_MALLOC);
	get_links_for_start(info);
//	while (info->end_reached == 0)
		find_paths(info);
}
