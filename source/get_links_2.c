/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:52:21 by elindber          #+#    #+#             */
/*   Updated: 2020/07/06 18:36:30 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	get_links(t_info *info)
{
	int		i;
	int		t;
	
	i = 0;
	t = 0;
	while (info->rooms[i] != NULL) // just checking
	{
		ft_printf("room: %s ", info->rooms[i]->name);
		ft_printf("link_string: %s\n", info->rooms[i]->link_string);
		while (info->rooms[i]->links[t] != NULL)
		{
			ft_printf("[%s]\n", info->rooms[i]->links[t]);
			t++;
		}
		t = 0;
		i++;
	}
//	get_links_for_start(info);
//	find_paths(info);
}