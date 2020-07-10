/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_turns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:27:35 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/10 12:18:48 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
/*
int				to_path_or_not_to_path(t_info *lem_in, char *path)
{
	int			calc;
	int			i;

	calc = 0;
	i = -1;
	while (lem_in->valid_paths[++i] != path)
	{
		calc += path - lem_in->valid_paths[i]->length
		move to next path

	}
	return (calc);
}

static void		ant_start_to_path(t_info *lem_in, char *path)
{
	// if (next room = end)
	// {
	// 	--lem_in->ants_start;
	// 	++lem_in->ants_end;
	// 	locations?
	// } should be if else with below.
	// else
	--lem_in->ants_start;
	// all location related here.
}
*/
/*
**	Check every path if ants should be inserted.
*/
/*
static void		ants_to_paths(t_info *lem_in, int n_of_paths)
{
	int		i;
	char	**path;

	i = -1;
	while (++i < n_of_paths)
	{
		path = ft_strsplit(lem_in->valid_paths[i], ' ');
		if (lem_in->ants > to_path_or_not_to_path(lem_in, path))
		{
			write(1, "Hello\n", 6);
			ant_start_to_path(lem_in, path);
		}
		//free_2d_array(path);
		free(path);
	}
}

static void		move_single_path(t_info *lem_in, char *path)
{
	int			room_i;

	room_i = path->length;
	while (--room_i >= 0)
	{
		if (isempty(path[room_i]))
			continue ;
		// found ant from the room, what next?
			// if last node of the path.
				// ++lem_in->ants_end;
				// clear room+update ant position?
			// else
				// ant position changes from path[room_i] to path[room_i + 1]
				// path[room_i] clear
	}
}

static void		move_existing_ants(t_info *lem_in, int n_of_paths)
{

	while (--n_of_paths >= 0)
	{
		move_single_path(lem_in, path);

	}
}

void			take_turns(t_info *lem_in)
{
	int			n_of_paths;

	while (lem_in->valid_paths[n_of_paths])
		++n_of_paths;
	while (lem_in->ants || lem_in->ants != lem_in->ants_end)
	{
		if (lem_in->ants != lem_in->ants_start)
			move_existing_ants(lem_in, n_of_paths);
		if (lem_in->ants_start > 0);
			ants_to_paths(lem_in, n_of_paths);
		print_locations(lem_in);
		free_used_stuff(lem_in);
	}
}
*/