/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:01:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/07 18:06:56 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_end(t_info *info)
{
	int		y;

	y = 0;
	if (info->path_amount == info->max_paths)
	{
		info->end_reached = 1;
		return ;
	}
	while (info->paths[y] != NULL)
	{
		if (info->paths[y][0] != '#')
			return ;
		y++;
	}
	info->end_reached = 1;
}

void	delete_duplicates(t_info *info, char *path)
{
	char	**valid_path;
	char	**cmp;
	int		i;
	int		y;
	int		t;

	i = 0;
	y = 0;
	t = 0;
	valid_path = ft_strsplit(path, ' ');
	while (valid_path[t] != NULL)
	{
		while (info->paths[y] != NULL)
		{
			cmp = ft_strsplit(info->paths[y], ' ');
			while (cmp[i] != NULL)
			{
				if (ft_strequ(valid_path[t], cmp[i]))
				{
					info->paths[y] = ft_memmove(info->paths[y], "#", 1);
					while (cmp[i + 1] != NULL)
						i++;
				}
				i++;
			}
			i = 0;
			y++;
			free_2d_array(cmp);
		}
		y = 0;
		t++;
	}
	free_2d_array(valid_path);
}

void	save_path(t_info *info, int path_i)
{
	info->valid_paths[info->path_amount] = ft_strdup(info->paths[path_i]);
	ft_printf("S A V I N G: [%s]\n", info->valid_paths[info->path_amount]);
	delete_duplicates(info, info->valid_paths[info->path_amount]);
	check_end(info);
	info->path_amount++;
}
