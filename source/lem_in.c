/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:26:57 by elindber          #+#    #+#             */
/*   Updated: 2020/07/27 20:13:42 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			init_info(t_info *info)
{
	int i;

	i = 0;
	while (i < 513)
		info->tmp_string[i++] = EMPTY;
	if (!info->flags->ants)
		info->ants = -1;
	info->ants_at_start = 0;
	info->ants_at_end = 0;
	info->last_found_used = 1;
	info->last_found_used_2 = 1;
	info->path_amount_1 = 0;
	info->path_amount_2 = 0;
	info->phase = 1;
	info->level = 1;
	info->lines = 1;
	info->link_amnt = 0;
	info->max_paths = INT_MAX;
	info->path_saved = 0;
	info->path_stack = 0;
	info->rooms_to_check = (char**)malloc(sizeof(char*) * 1);
	info->rooms_to_check[0] = NULL;
	info->round = 0;
}

void	print_paths(t_info *info)
{
	int		y;
	int		i;

	y = 0;
	while (info->valid_indexes[y][0] != EMPTY)
	{
		i = 0;
		ft_putchar('[');
		while (info->valid_indexes[y][i] != EMPTY)
		{
			ft_printf("%s ", info->rooms[info->valid_indexes[y][i]]->name);
			i++;
		}
		ft_putstr("]\n");
		y++;
	}
	ft_putchar('\n');
	if (info->path_amount_2 > 0)
	{
		i = 0;
		y = 0;
		ft_printf("OR\n");
		while (info->valid_indexes_2[y][0] != EMPTY)
		{
			ft_putchar('[');
			while (info->valid_indexes_2[y][i] != EMPTY)
			{
				ft_printf("%s ", info->rooms[info->valid_indexes_2[y][i]]->name);
				i++;
			}
			ft_putstr("]\n");
			i = 0;
			y++;
		}
	}
	ft_putchar('\n');
}

void	second_round(t_info *info)
{
	int		i;

	i = 0;
	info->phase = 2;
	info->level = 1;
	info->path_amount_2 = 0;
	if (info->path_amount_1 < 1)
		exit_error(ERR_NO_PATH, info);
	reset_tmp_stacks(info);
	while (info->rooms[i] != NULL)
	{
		info->rooms[i]->visited = 0;
		i++;
	}
	get_links_for_start(info, 0, 0, 0);
	find_paths(info, -1, 0, 0);
	calculate_moves(info);
}

void	all_ants_to_end_at_once(t_info *info)
{
	int		i;

	i = 1;
	ft_printf("\n");
	while (i <= info->ants)
	{
		ft_printf("L%d-%s ", i, info->end);
		i++;
	}
	ft_printf("\n");
}

void	save_first_level_rooms(t_info *info)
{
	int		i;

	i = -1;
	while (++i < 513)
	{
		info->lvl_1_rooms[i] = info->check_rooms[i];
	//	if (info->check_rooms[i] > 0)
	//		ft_printf("lvl_1_room[%d] %s\n", i, info->rooms[info->lvl_1_rooms[i]]->name);
		info->check_rooms[i] = EMPTY;
	}
}

void	third_round(t_info *info)
{
	int		i;

	info->round = 1;
	while (info->round < 5)
	{
		i = -1;
		info->phase = 2;
		info->level = 1;
		info->path_amount_2 = 0;
		info->path_saved = 0;
		reset_tmp_stacks(info);
		while (info->rooms[++i] != NULL)
		{
			info->rooms[i]->visited = 0;
			info->rooms[i]->flow = 0;
			info->rooms[i]->path_2 = -1;
		}
		get_links_for_start(info, 0, 0, 0);
		save_first_level_rooms(info);
		dfs_search(info, -1);
	//	sort_paths(info);
		print_paths(info);
		calculate_moves(info);
		info->round++;
	}
	info->round++;
}

static void		lem_in(int ac, char *av, t_info *info)
{
	t_output		*output;
	char			*line;

	if (!(output = (t_output*)malloc(sizeof(t_output))))
		exit_error(ERR_MALLOC, info);
	if (ac > 1)
	{
		ac += 0;
		av[0] += 0;
	}
	info->tmpfd = 0;
//	info->tmpfd = open(av, O_RDONLY);
	init_info(info);
	get_next_line(info->tmpfd, &line);
	output->line = ft_strdup(line);
	parse_ants(info, output);
	free(line);
	if (!parse_v2(output, info))
		exit_error(ERR_PARSE_V2, info);
	if (info->start_end_link)
		all_ants_to_end_at_once(info);
//	first_round(info);
	else
	{
		get_links(info);
		second_round(info);
		third_round(info);
		sort_paths(info);
		ft_printf("><><><><><><\n><><><><><><\nants: %d\nPATHS  SAVED:\n", info->ants);
		print_paths(info);
		//write(1, "\n", 1);
		ant_flow(info);
	}
	ft_printf("lines: %d\n", info->lines);
	free_memory(output);
}

int				main(int ac, char **av)
{
	t_info			*info;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit_error_no_info(ERR_MALLOC);
	parse_flags(ac, av, info);
	if (ac > 0 && !info->flags->help)
	{
		if (info->flags->verbose)
			ft_printf("Verbose mode activated!\n");
		lem_in(ac, av[1], info);
	}
	else if (info->flags->help)
		ft_printf("HELP!\n");
	else
		exit_error(ERR_USAGE, info);
	return (0);
}
