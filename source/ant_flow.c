/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:30:44 by elindber          #+#    #+#             */
/*   Updated: 2020/07/07 13:04:48 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	route_info(t_info *info, char *name, int nbr, int i)
{
	ft_printf("route info: %d %d %s\n", nbr, i, name);
	if (!(info->route[nbr][i] = (t_room*)malloc(sizeof(t_room))))
			exit_error(ERR_MALLOC);
	ft_printf("JA %d %d %s\n", nbr, i, name);
	info->route[nbr][i]->name = ft_strdup(name);
	info->route[nbr][i]->ants = 0;
	info->route[nbr][i]->visited = 0;
	info->route[nbr][i]->path = nbr;
	if (ft_strequ(name, info->end))
	{
		info->route[nbr][i]->start_or_end = 2;
		info->route[nbr][i]->level = INT_MAX;
	}
	else
	{
		info->route[nbr][i]->start_or_end = 0;
		info->route[nbr][i]->level = i + 1;
	}
}

void	create_route(t_info *info, char	*path, int nbr)
{
	char	**table;
	int		y;

	y = 0;
	table = ft_strsplit(path, ' ');
	while (table[y] != NULL)
	{
		ft_printf("[%s]\n", table[y]);
		y++;
	}
	ft_printf("rooms on route %d: %d\n", nbr, y);
	if (!(info->route[nbr] != (t_room**)malloc(sizeof(t_room*) * (y + 1))))
		exit_error(ERR_MALLOC);
	y = 0;
	while (table[y] != NULL)
	{
		route_info(info, table[y], nbr, y);
		y++;
	}
	info->route[nbr][y] = NULL;
	free_2d_array(table);
}

void	ant_flow(t_info *info)
{
	int		y;
	
	y = 0;
	while (info->valid_paths[y] != NULL)
		y++;
	if (!(info->route = (t_room***)malloc(sizeof(t_room**) * (y + 1))))
		exit_error(ERR_MALLOC);
	ft_printf("routes: %d\n", y);
	y = 0;
	while (info->valid_paths[y] != NULL)
	{
		create_route(info, info->valid_paths[y], y);
		y++;
	}
	info->route[y] = NULL;
	y = 0;
	int x = 0;
	while (info->route[y] != NULL)
	{
		ft_printf("route nbr: %d\n", info->route[y][0]->path);
		while (info->route[y][x] != NULL)
		{
			ft_printf("%s->", info->route[y][x]->name);
			x++;
		}
		y++;
		x = 0;
	}
}