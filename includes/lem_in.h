/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:42:05 by elindber          #+#    #+#             */
/*   Updated: 2020/07/06 17:54:29 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/includes/get_next_line.h"
# include "../libftprintf/libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h> //debug include
/*
**	Error Management
**
**	possible adds:
**					-Room name with # or L.
**					-more specific ant errors
**					-Locations: (L-1-3), (L11 with 10 ant map), (L0-3), (L1-X)
*/

# define ERR_ANTS			"Error: Ants must be positive int!"
# define ERR_BAD_LINK		"Error: Link to non-existing room detected!"
# define ERR_DUP_LINK		"Error: Duplicate link found!"
# define ERR_NO_PATH		"Error: No path found!"
# define ERR_OPEN			"Error: Failed to open!"
# define ERR_MALLOC			"Error: Failed to Malloc!"
# define ERR_USAGE			"USAGE: ./lem-in < [file]"
# define ERR_NO_EL			"Error: No empty line between links and locations"
# define ERR_ROOM_DUP_COORD	"Error: Duplicate room coordinates found!"
# define ERR_ROOM_M_END		"Error: Multiple ends found!"
# define ERR_ROOM_M_START	"Error: Multiple starts found!"
# define ERR_ROOM_DUP_NAME	"Error: Duplicate room names found!"
# define ERR_ROOM_NO_END	"Error: No end room!"
# define ERR_ROOM_NO_ROOMS	"Error: No rooms found!"
# define ERR_ROOM_NO_START	"Error: No start room!"

/*
**	Enums for boolean
*/

typedef enum
{
	FALSE,
	TRUE,
}		t_bool;

typedef struct 		s_lem_in
{
	t_bool			help;
	t_bool			verbose;
}					t_lem_in;

typedef struct		s_output
{
	char			*line;
	struct s_output	*next;
}					t_output;

typedef struct		s_room
{
	char			**links;
	char			*link_string;
	char			*name;
	int				start_or_end;
	int				visited;
	int				path;
	int				level;
	int				length;
	int				ants;
	int				y;
	int				x;
}					t_room;

typedef struct		s_route
{
	char			*name;
	int				ants;
	int				visited;
	int				path;
	int				start_or_end;
	int				level;
}					t_route;


typedef struct		s_ant
{
	int				number;
	int				path;
	char			*room;
}					t_ant;

typedef struct		s_info
{
	char			*start;
	char			*end;
	int				level;
	int				ants;
	int				path_amount;
	int				max_paths;
	int				end_reached;
	int				link_amnt;
	int				path_stack;
	char			**map;
	char			***links;
	char			**paths;
	char			**valid_paths;
	char			**rooms_to_check;
	char			*tmp_string;
	t_room			**rooms;
	t_room			***route;
	int             tmpfd;
}					t_info;

typedef struct		s_link
{
	t_room 			*room1;
	t_room			*room2;
	struct s_link	*next;
}					t_link;

typedef struct		s_path
{
	char			**rooms;
	int				length;
	int				ants_on_path;
	struct s_path	*next;
}					t_path;

/*
** Functions
*/

int					parse_v2(t_output *output, t_info *info, int count);
char				*last_on_path(char *path);
void				get_links(t_info *info);
void				save_path(t_info *info);
void				reset_rooms(t_info *info);
void				ant_flow(t_info *info);
void				exit_error(const char *str);
void				free_2d_array(char **arr);
void				add_to_path(t_info *info, char *add_room, int i);

void				print_paths(t_info *info);

#endif
