/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <elindber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 09:21:32 by mlindhol          #+#    #+#             */
/*   Updated: 2020/07/27 12:17:41 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Frees memory allocated to t_output *op linked list.
*/

void			lst_free(t_output *op)
{
	t_output	*current;
	t_output	*tmp;

	current = op;
	while (current->next)
	{
		tmp = current;
		current = current->next;
		free(tmp->line);
		free(tmp);
	}
	free(current->line);
	free(current);
}

/*
**	Free memory dispatcher.
*/

void			free_memory(t_output *op)
{
	lst_free(op);
}

/*
**	Free memory allocated to 2D array.
*/

void			free_2d_array(char **arr)
{
	int			i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
