/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:42:05 by elindber          #+#    #+#             */
/*   Updated: 2020/07/27 19:39:23 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/includes/get_next_line.h"
# include "../libftprintf/libft/libft.h"

# include <fcntl.h> //debug include
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*
**	Error Management
*/

# define ERR_ANTS			"Error: Ant amount must be between 1 and 999999"
# define ERR_BAD_LINK		"Error: Link to non-existing room detected"
# define ERR_DUP_LINK		"Error: Duplicate link found"
# define ERR_MALLOC			"Error: Failed to Malloc!"
# define ERR_NO_EL			"Error: No empty line between links and locations"
# define ERR_NO_LINK		"Error: No links found"
# define ERR_NO_PATH		"Error: No path found!"
# define ERR_OPEN			"Error: Failed to open!"
# define ERR_PARSE_V2		"Error: !Parse_v2"
# define ERR_ROOM_ARGS_FEW	"Error: Too few room arguments"
# define ERR_ROOM_ARGS_MANY	"Error: Too many room arguments"
# define ERR_ROOM_DUP_COORD	"Error: Duplicate room coordinates found!"
# define ERR_ROOM_DUP_NAME	"Error: Duplicate room names found!"
# define ERR_ROOM_M_END		"Error: Multiple ends found!"
# define ERR_ROOM_M_START	"Error: Multiple starts found!"
# define ERR_ROOM_NAME_DASH	"Error: Room name including '-'"
# define ERR_ROOM_NO_END	"Error: No end room!"
# define ERR_ROOM_NO_ROOMS	"Error: No rooms found!"
# define ERR_ROOM_NO_START	"Error: No start room!"
# define ERR_ROOM_STARTS_L	"Error: Room name starting with 'L'"
# define ERR_ROOM_STARTS_SH	"Error: Room name starting with '#'"
# define ERR_USAGE			"USAGE: ./lem-in < [file]"

/*
**	Other defined values
*/

# define EMPTY -1
# define LOCKED -2

/*
**	Enums for boolean
*/

// typedef enum
// {
// 		FALSE,
// 		TRUE,
// }		t_bool;

typedef struct			s_flags
{
	int					ants;
	int					error;
	int					help;
	int					lines;
	int					paths;
	int					verbose;
}						t_flags;

typedef struct			s_output
{
	char				*line;
	struct s_output		*next;
}						t_output;

typedef struct			s_room
{
	char				*link_string;
	char				**links;
	char				*name;
	int					ant_id;
	int					*ant_queue;
	int					*ant_queue_2;
	int					ants;
	int					ants_2;
	int					flow;
	int					cost;
	int					cost_2;
	int					length;
	int					length_2;
	int					level;
	int					path;
	int					path_2;
	int					start_or_end;
	int					visited;
	int					x;
	int					y;
}						t_room;

typedef struct			s_ant
{
	char				*room;
	int					number;
	int					path;
}						t_ant;

typedef struct			s_location
{
	int					ant_number;
	struct s_location	*next;
	struct s_location	*previous;
	t_room				*room;
}						t_location;

typedef struct			s_link
{
	int					flow;
	int					next;
	int					prev;
}						t_link;

typedef struct			s_info
{
	char				*end;
	char				***links;
	char				**rooms_to_check;
	char				*start;
	char				**valid_paths;
	char				**valid_paths_2;
	int					ants;
	int					ants_at_end;
	int					ants_at_start;
	int					check_rooms[513];
	int					lvl_1_rooms[513];
	int					end_index;
	int					**index_stack;
	int					level;
	int					lines;
	int					link_amnt;
	int					max_paths;
	int					path_amount_1;
	int					path_amount_2;
	int					path_saved;
	int					path_stack;
	int					phase;
	int					round;
	int					room_amnt;
	int					start_index;
	int					tmp_string[513];
	int					tmpfd;
	int					start_end_link;
	int					last_found_used;
	int					last_found_used_2;
	int					**valid_indexes;
	int					**valid_indexes_2;
	t_ant				*ant;
	t_flags				*flags;
	t_location			*location;
	t_room				**rooms;
	t_link				***link_tubes;
}						t_info;

typedef struct			s_path
{
	char				**rooms;
	int					length;
	int					ants_on_path;
	struct s_path		*next;
}						t_path;

/*
** Misc functions
*/

int						ft_isint(char *str);
void					reset_tmp_stacks(t_info *info);
void					start_over_or_continue(t_info *info, int index);

/*
**	Link related functions
*/

void					get_links(t_info *info);
void					get_links_for_start(t_info *info, int i, int s, int t);

/*
**	Parsing functions
*/

void					parse_ants(t_info *info, t_output *output);
void					parse_flags(int ac, char **av, t_info *info);
int						parse_v2(t_output *output, t_info *info);

/*
**	Path related functions
*/

void					add_to_path(t_info *info, int s, int i, int y);
void					find_paths(t_info *info, int i, int j, int l);
void					dfs_search(t_info *info, int i);
void					search_from_room(t_info *info);
int						last_on_path(int *path);
void					print_paths(t_info *info);
void					save_path(t_info *info, int path_i);
void					sort_paths(t_info *info);
void					calculate_moves(t_info *info);

/*
**	Room related functions
*/

int						find_a_room(t_info *info, char *to_find);
void					reset_rooms(t_info *info);
void					set_visited(t_info *info, int s, int l);
void					sort_rooms(t_info *info);
void					reorder_check_rooms(t_info *info);
void					copy_check_rooms(t_info *info);

/*
**	Ant turns functions
*/

//void					print_locations(t_info *info);
//void					take_turns(t_info *info);
void					ant_flow(t_info *info);
void					print_turns_2(t_info *info);

/*
**	Memory allocation freeage
*/

void					free_2d_array(char **arr);
void					free_memory(t_output *op);
void					lst_free(t_output *op);

/*
**	Error management functions
*/

void					exit_error(const char *str, t_info *info);
void					exit_error_no_info(const char *str);

#endif
