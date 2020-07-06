/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:01:15 by elindber          #+#    #+#             */
/*   Updated: 2020/07/06 18:13:00 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
/*
int		first_on_path(t_info *info, char *path, int i, int h)
{
	char	*first;
	char	*cmp;

	if (info->path_amount < 2)
		return (0);
	while (path[i] != ' ')
		i++;
	if (!(first = ft_strsub(path, 0, i)))
		exit_error(ERR_MALLOC);
	i = 0;
	while (info->valid_paths[i + 1] != NULL)
	{
		while (info->valid_paths[i][h] != ' ')
			h++;
		cmp = ft_strsub(info->valid_paths[i], 0, h);
		if (ft_strequ(first, cmp))
		{
			ft_strdel(&first);
			ft_strdel(&cmp);
			return (1);
		}
		h = 0;
		i++;
	}
	ft_strdel(&first);
	ft_strdel(&cmp);
	return (0);
}

void	clear_tmp_paths(t_info *info)
{
	int		y;

	y = 0;
	while (y < info->link_amnt)
	{
		ft_strdel(&info->paths[y]);
		y++;
	}
*//*	y = 0;
	while (y < info->link_amnt)
	{
		ft_printf("%s\n", info->paths[y]);
		y++;
	}
}

int		double_check(t_info *info, char	*valid_path)
{
	int		y;

	y = 0;
	if (info->path_amount == 0)
		return (1);
	while (y < info->max_paths)
	{
		if (ft_strequ(valid_path, info->valid_paths[y])) //|| first_on_path(info, valid_path, 0, 0))
			return (0);
		y++;
	}
	return (1);
}

void	save_path(t_info *info)
{
	char	*last;
	int		y;

	y = 0;
//	ft_printf("mystinen 2: [%d] %s\n", 2, info->valid_paths[2]);
	while (info->paths[y] != NULL)
	{
		ft_printf("path[%d] %s\n", y, info->paths[y]);
		last = last_on_path(info->paths[y]);
		if (ft_strequ(last, info->end) && double_check(info, info->paths[y]))
		{
			info->valid_paths[info->path_amount] = ft_strdup(info->paths[y]);
			ft_printf("Save path: [%d] %s\n", info->path_amount, info->valid_paths[info->path_amount]);
			free(last);
			break ;
		}
		free(last);
		y++;
	}
//	if (info->valid_paths[info->path_amount] == NULL)
//		info->path_amount = info->max_paths;
	if (info->path_amount > 0 && ft_strequ(info->valid_paths[info->path_amount], info->valid_paths[info->path_amount - 1])) //&& first_on_path(info, info->valid_paths[info->path_amount], 0, 0))
	{
		ft_printf("DELETE: [%d] [%d] %s\n", info->path_amount - 1, info->path_amount, info->valid_paths[info->path_amount]);
		ft_strdel(&info->valid_paths[info->path_amount]);
		info->path_amount = info->max_paths;
	}
	else
	{
		ft_printf("S A V I N G: [%d] %s\n", info->path_amount, info->valid_paths[info->path_amount]);
		info->path_amount++;
	}
	clear_tmp_paths(info);
	if (info->path_amount < info->max_paths)
	{
		reset_rooms(info);
		info->end_reached--;
		get_links(info);
	}
}
*/