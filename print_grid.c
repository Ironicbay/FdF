/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:26:48 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:37:10 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Translates a (x, y, z) into a (x, y) for isometric projection
*/

static t_pos	grid_to_iso(t_data *e, int index)
{
	t_pos		new;
	t_pos		point;
	int			i;
	int			j;
	int			position;

	i = (e->trigrid[index]).y;
	j = (e->trigrid[index]).x;
	position = i * e->col_nbr + j;
	new.x = -((e->col_nbr / 2) - (e->line_nbr / 2) - (j - i)) * e->zoom / 40;
	new.y = -((e->line_nbr / 2) + (e->col_nbr / 2) - (j + i)) * e->zoom / 40;
	point.x = (int)(new.x * cos(e->angle) - new.y * sin(e->angle)) + (e->top).x;
	point.y = (int)(new.x * sin(e->angle) + new.y * cos(e->angle)) + (e->top).y;
	if (e->max_h != 0)
		point.y -= (e->trigrid[position]).z * (e->scale / e->max_h) / 10;
	return (point);
}

/*
** Translates a (x, y, z) into a (x, y) for a 3D-like projection
*/

static t_pos	grid_to_pers(t_data *e, int index)
{
	t_pos		new;
	t_pos		point;
	int			i;
	int			j;
	int			pos;

	i = (e->trigrid[index]).y;
	j = (e->trigrid[index]).x;
	pos = i * e->col_nbr + j;
	new.x = -((e->col_nbr / 2) - j) * e->zoom / 40;
	new.y = -((e->line_nbr / 2) - i) * e->zoom / 40;
	point.x = (int)(new.x * cos(e->angle) - new.y * sin(e->angle)) + (e->top).x;
	point.y = (int)(new.x * sin(e->angle) + new.y * cos(e->angle)) + (e->top).y;
	if (e->max_h != 0)
	{
		point.x -= (((e->trigrid[pos]).z) * ((WIN_W - (e->top).x - point.x))
			* (e->scale / e->max_h) / 1000);
		point.y -= (((e->trigrid[pos]).z) * ((WIN_H - (e->top).y - point.y))
				* (e->scale / e->max_h) / 1000);
	}
	return (point);
}

/*
** Transfers the map data into 3-dimensional coordinates for an easier handling
*/

void			make_grid(t_data *e)
{
	int			i;
	int			size;

	size = e->line_nbr * e->col_nbr;
	i = -1;
	while (++i < size)
	{
		(e->trigrid[i]).x = i % e->col_nbr;
		(e->trigrid[i]).y = (i / e->col_nbr) % e->line_nbr;
		(e->trigrid[i]).z = (e->map)[(e->trigrid[i]).y][(e->trigrid[i]).x];
	}
	free_map(e, 0, "");
}

/*
** Main function to display the visual grid, getting every vertex coordinate
**	depending on the type of display
** Then using the draw_segment function to form the edges
*/

void			print_grid(t_data *e, int size)
{
	int			i;
	t_pos		a;
	t_pos		b;

	i = -1;
	while (++i < size - 1)
	{
		e->height_a = (e->trigrid[i]).z;
		a = e->mode ? grid_to_pers(e, i) : grid_to_iso(e, i);
		if (i % e->col_nbr != e->col_nbr - 1)
		{
			b = e->mode ? grid_to_pers(e, i + 1) : grid_to_iso(e, i + 1);
			e->height_b = (e->trigrid[i + 1]).z;
			draw_segment(e, a, b);
		}
		if (i / e->col_nbr != e->line_nbr - 1)
		{
			b = e->mode ? grid_to_pers(e, i + e->col_nbr)
				: grid_to_iso(e, i + e->col_nbr);
			e->height_b = (e->trigrid[i + e->col_nbr]).z;
			draw_segment(e, a, b);
		}
	}
}
