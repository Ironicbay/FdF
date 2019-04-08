/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:13:17 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:34:25 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Picks a determined color for all drawn pixels
*/

static void		basic_colors(t_data *e)
{
	if (e->display == 0)
		e->color = C_WHITE;
	if (e->display == 1)
		e->color = C_RED;
	if (e->display == 2)
		e->color = C_YELLOW;
	if (e->display == 3)
		e->color = C_GREEN;
	if (e->display == 4)
		e->color = C_TURQUOISE;
	if (e->display == 5)
		e->color = C_BLUE;
	if (e->display == 6)
		e->color = C_PURPLE;
}

/*
** Calculates the point's color relative to its height,
**	and max and min map's heights
*/

static double	get_ratio(t_data *e, double height)
{
	double		ratio;

	if (e->display != 10)
		e->color = 0;
	if (e->display == 7)
		ratio = 1 - (((double)e->max_h - height) /
				((double)e->max_h - (double)e->min_h));
	if (e->display == 8)
		ratio = fabs(height / (double)e->max_h);
	if (e->display == 9 || e->display == 10)
		ratio = ((double)e->max_h - height) /
				((double)e->max_h - (double)e->min_h);
	return (ratio);
}

/*
** Core is for rainbow colors, calculating which color to pick relative to
** 	point's height on the map
*/

void			next_color(t_data *e, double height)
{
	double		ratio;

	if (e->display >= 7 && e->display <= 10 && e->min_h != e->max_h)
	{
		ratio = get_ratio(e, height);
		if (ratio < 0.2)
			e->color += C_BLACK + C_RED +
				(int)(ratio * (double)C_GREEN / 256 * 5.0) * 256;
		if (ratio >= 0.2 && ratio < 0.4)
		{
			e->color += C_WHITE - C_BLUE -
				((int)((ratio - 0.2) * C_RED / 65536 * 5.0)) * 65536;
		}
		if (ratio >= 0.4 && ratio < 0.6)
			e->color += C_BLACK + C_GREEN +
				(int)((ratio - 0.4) * (double)C_BLUE * 5.0);
		if (ratio >= 0.6 && ratio < 0.8)
			e->color += C_WHITE - C_RED -
				((int)((ratio - 0.6) * C_GREEN / 256 * 5.0)) * 256;
		if (ratio >= 0.8)
			e->color += C_BLACK + C_BLUE + 65536 *
				(int)((ratio - 0.8) * (double)C_RED / 65536 * 10.0 / 3.0);
	}
	else
		basic_colors(e);
}

void			get_color(t_data *e, int index, int diff)
{
	double		ratio;
	double		height_between_ab;
	double		height;
	double		min;

	ratio = (double)index / (double)diff;
	height_between_ab = fabs(e->height_b - e->height_a);
	min = e->height_a > e->height_b ? e->height_b : e->height_a;
	height = (min + (ratio * height_between_ab));
	next_color(e, height);
}
