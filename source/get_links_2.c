/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:52:21 by elindber          #+#    #+#             */
/*   Updated: 2020/07/06 18:26:56 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*void	get_links_for_room(t_info *info, char *room, int r)
{
	char	*link_list;
	char	*tmp;
	char	*add;
	int		i;

	i = 0;
	link_list = ft_strnew(0);
	while (info->links[i] != NULL)
	{
		if (ft_strequ(room, info->links[i][0]))
		{
			add = ft_strjoin(info->links[i][1], " ");
			tmp = ft_strjoin(link_list, add);
			free(link_list);
			link_list = ft_strdup(tmp);
			free(add);
			free(tmp);
		}
		else if (ft_strequ(room, info->links[i][1]))
		{
			add = ft_strjoin(info->links[i][0], " ");
			tmp = ft_strjoin(link_list, add);
			free(link_list);
			link_list = ft_strdup(tmp);
			free(add);
			free(tmp);
		}
		i++;
	}
	tmp = ft_strtrim(link_list);
	info->rooms[r]->links = ft_strsplit(tmp, ' ');
	free(tmp);
	free(link_list);
}*/


void	get_links(t_info *info)
{
	int		i;
	int		t;
	
	i = 0;
	t = 0;
	while (info->rooms[i] != NULL)
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