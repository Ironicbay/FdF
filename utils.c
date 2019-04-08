/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:13:42 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:37:26 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function to free map and eventually exit the program in case of error
*/

void	free_map(t_data *e, int error, char *message)
{
	int	i;

	i = -1;
	while (++i < e->line_nbr)
		free(e->map[i]);
	free(e->map);
	if (error)
		ft_error(message);
}

/*
** Exiting function if no error was encountered
*/

void	free_and_exit(t_data *e)
{
	free(e->trigrid);
	exit(0);
}

/*
** e->map allocation, see parse_file.c
*/

void	alloc_map(t_data *e)
{
	int	line_stock;

	line_stock = e->line_nbr;
	if (!(e->map = (int**)malloc(sizeof(int*) * e->line_nbr)))
		ft_error("Failed allocation");
	while (e->line_nbr > 0)
	{
		if (!(e->map[--e->line_nbr] = (int*)malloc(sizeof(int) * e->col_nbr)))
		{
			while (++e->line_nbr < line_stock)
				free(e->map[e->line_nbr]);
			free(e->map);
			ft_error("Failed allocation");
		}
	}
}
