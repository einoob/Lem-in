/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:01:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/10 17:40:39 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	reset_tmp_stacks(t_info *info)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (info->tmp_string[i] != EMPTY)
	{
		info->tmp_string[i] = EMPTY;
		i++;
	}
	i = 0;
	while (info->check_rooms[i] != EMPTY)
	{
		info->check_rooms[i] = EMPTY;
		i++;
	}
	i = 0;
	while (y < info->link_amnt)
	{
		while (i < 513)
		{
			info->index_stack[y][i] = EMPTY;
			i++;
		}
		i = 0;
		y++;
	}
}

int		check_end(t_info *info)
{
	int		y;

	y = 0;
	if (info->path_amount == info->max_paths)
	{
		info->path_saved = 2;
		return (1);
	}
	while (info->index_stack[y][0] != EMPTY)
	{
		if (info->index_stack[y][0] != LOCKED)
			return (0);
		y++;
	}
	info->path_saved = 2;
	return (1);
}

void	delete_duplicates(t_info *info, int *path)
{
	int		i;
	int		t;
	int		u;
	
	i = 0;
	t = 0;
	u = 0;
	while (path[i] != EMPTY)
	{
		while (info->index_stack[t][0] != EMPTY)
		{
			while (info->index_stack[t][u] != EMPTY)
			{
				if (info->index_stack[t][u] == path[i])
				{
					info->index_stack[t][0] = LOCKED;
					u = 126;
				}
				u++;
			}
			u = 0;
			t++;
		}
		i++;
	}
}

void	save_path(t_info *info, int path_i)
{
	char	*add;
	char	*tmp;
	int		i;
	int		t;
	int		u;
	
	u = info->path_amount;
	i = 0;
	t = 0;
	info->valid_paths[u] = ft_strnew(0);
	while (info->index_stack[path_i][i] != EMPTY)
	{
		info->valid_indexes[info->path_amount][i] = info->index_stack[path_i][i];
		if (info->index_stack[path_i][i] != info->end_index)
			info->rooms[info->index_stack[path_i][i]]->path = info->path_amount;
		i++;
	}
	info->rooms[info->index_stack[path_i][0]]->length = i - 1;
	i = 0;
	while (info->valid_indexes[info->path_amount][i] != EMPTY)
	{
		add = ft_strjoin(info->rooms[info->valid_indexes[u][i]]->name, " ");
		tmp = ft_strjoin(info->valid_paths[u], add);
		ft_strdel(&info->valid_paths[u]);
		info->valid_paths[u] = ft_strdup(tmp);
		ft_strdel(&add);
		ft_strdel(&tmp);
		i++;
	}
//	ft_printf("S A V I N G:\n[%s]\n", info->valid_paths[info->path_amount]);
	info->path_amount++;
	info->path_saved = 1;
	if (!(check_end(info)))
	{
		reset_rooms(info);
		reset_tmp_stacks(info);
	}
}
