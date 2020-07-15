/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:26:57 by elindber          #+#    #+#             */
/*   Updated: 2020/07/14 16:38:09 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			free_memory(t_info *info, int i)
{
	free(info->start);
	free(info->end);
	while (info->rooms[i] != NULL)
	{
		free(info->rooms[i]->name);
		i++;
	}
	free_2d_array(info->paths);
}

void			free_2d_array(char **arr)
{
	int				i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void			init_info(t_info *info)
{
	int i;

	i = 0;
	while (i < 513)
		info->tmp_string[i++] = EMPTY;
	info->ants = -1;
	info->ants_at_start = 0;
	info->ants_at_end = 0;
	info->path_amount = 0;
	info->phase = 1;
	info->level = 1;
	info->lines = 1;
	info->link_amnt = 0;
	info->max_paths = INT_MAX;
	info->path_saved = 0;
	info->path_stack = 0;
	info->rooms_to_check = (char**)malloc(sizeof(char*) * 1);
	info->rooms_to_check[0] = NULL;
}

void	print_paths(t_info *info)
{
	int				i;

	i = 0;
	while (info->valid_paths[i] != NULL)
	{
		ft_printf("[%s]\n", ft_strtrim(info->valid_paths[i]));
		i++;
	}
	ft_putchar('\n');
}

static void		lem_in(int ac, char *av)
{
	t_ant			*ant;
	t_info			*info;
	t_link			*link;
	t_output		*output;
	char			*line;

	if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
		exit_error(ERR_MALLOC);
	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit_error(ERR_MALLOC);
	if (!(link = (t_link*)malloc(sizeof(t_link))))
		exit_error(ERR_MALLOC);
	if (!(output = (t_output*)malloc(sizeof(t_output))))
		exit_error(ERR_MALLOC);
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
	// info->ants = ft_atoi(output->line);
	// info->ants_at_start = info->ants;
	free(line);
	if (!parse_v2(output, info, 1))
		exit_error(ERR_PARSE_V2);
	get_links(info);
	ft_printf("><><><><><><\n><><><><><><\nants: %d\nPATHS  SAVED:\n", info->ants);
	print_paths(info);
	ant_flow(info);
	ft_printf("lines: %d\n", info->lines);
//	take_turns(info);
//	free_memory(info, 0);
}

/*
int				main(int ac, char **av)
{

	t_bool			help;
	t_bool			verbose;
	t_ant			*ant;
	t_info			*info;
	t_link			*link;
	t_output		*output;
	char			*line;

	if (!(ant = (t_ant*)malloc(sizeof(t_ant))))
		exit_error(ERR_MALLOC);
	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit_error(ERR_MALLOC);
	if (!(link = (t_link*)malloc(sizeof(t_link))))
		exit_error(ERR_MALLOC);
	if (!(output = (t_output*)malloc(sizeof(t_output))))
		exit_error(ERR_MALLOC);

	help = FALSE;
	verbose = FALSE;

	// Parse flags
	while (ac >= 2 && (!ft_strcmp(av[1], "-h") || !ft_strcmp(av[1], "-v")))
	{
		if (ft_strequ(av[1], "-h"))
			help = TRUE;
		else if (ft_strequ(av[1], "-v"))
			verbose = TRUE;
		av++;
		ac--;
	}
//	info->tmpfd = open(av[1], O_RDONLY);
	info->tmpfd = 0;
	if (ac > 0 && !help)
	{
		if (verbose)
			ft_printf("Verbose mode activated!\n");
		init_info(info);
		get_next_line(info->tmpfd, &line);
		output->line = ft_strdup(line);
		info->ants = ft_atoi(output->line);
		free(line);
		if (!parse_v2(output, info, 1))
			return (-1);
		get_links(info);
	}
	else if (help)
		ft_printf("HELP!\n");
	else
	 	exit_error(ERR_USAGE);
	ft_printf("><><><><><><\n><><><><><><\nPATHS  SAVED:\n");
	print_paths(info);
	free_memory(info, 0);
//	while (1);
	return (0);
}
*/

int				main(int ac, char **av)
{
	t_bool			help;
	t_bool			verbose;

	help = FALSE;
	verbose = FALSE;
	while (ac >= 2 && (!ft_strcmp(av[1], "-h") || !ft_strcmp(av[1], "-v")))
	{
		if (ft_strequ(av[1], "-h"))
			help = TRUE;
		else if (ft_strequ(av[1], "-v"))
			verbose = TRUE;
		av++;
		ac--;
	}
	if (ac > 0 && !help)
	{
		if (verbose)
			ft_printf("Verbose mode activated!\n");
		lem_in(ac, av[1]);
	}
	else if (help)
		ft_printf("HELP!\n");
	else
		exit_error(ERR_USAGE);
//	while (1);
	return (0);
}
