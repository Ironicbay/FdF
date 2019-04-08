/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:54:19 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:35:17 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_segment_on_x(t_data *e, t_pos diff, t_pos current, t_pos inc)
{
	int		i;
	int		cumul;
	int		order;

	cumul = diff.x / 2;
	i = 0;
	while (++i <= diff.x)
	{
		order = e->height_a < e->height_b ? i : diff.x - i;
		if (e->display >= 7 && e->display <= 10)
			get_color(e, order, diff.x);
		current.x += inc.x;
		cumul += diff.y;
		if (cumul >= diff.x)
		{
			cumul -= diff.x;
			current.y += inc.y;
		}
		if (current.x < WIN_W && current.y < WIN_H - 100
				&& current.x >= 0 && current.y > 100)
			image_put_pixel(e->image, current, e->size_line, e->color);
	}
}

/*
** Order is for any progressive color along the segment
** The color is picked for every pixel if it varies, otherwise it's defined once
**	in draw_segment
*/

static void	print_segment_on_y(t_data *e, t_pos diff, t_pos current, t_pos inc)
{
	int		i;
	int		cumul;
	int		order;

	cumul = diff.y / 2;
	i = 0;
	while (++i <= diff.y)
	{
		order = e->height_a < e->height_b ? i : diff.y - i;
		if (e->display >= 7 && e->display <= 10)
			get_color(e, order, diff.y);
		current.y += inc.y;
		cumul += diff.x;
		if (cumul >= diff.y)
		{
			cumul -= diff.y;
			current.x += inc.x;
		}
		if (current.x < WIN_W && current.y < WIN_H - 100
				&& current.x >= 0 && current.y > 100)
			image_put_pixel(e->image, current, e->size_line, e->color);
	}
}

/*
** Draws a segment using Bresenham's line algorithm
** Separated in two cases, either vertically (on_y) or horizontally (on_x)
** First if optimizes the process, not drawing anything if no pixel of the
**	segment would display on screen
*/

void		draw_segment(t_data *e, t_pos first, t_pos second)
{
	t_pos	diff;
	t_pos	current;
	t_pos	inc;

	if ((first.x < 0 && second.x < 0)
			|| (first.x > WIN_W && second.x > WIN_W)
			|| (first.y < 0 && second.y < 0)
			|| (first.y > WIN_H && second.y > WIN_H))
		return ;
	current.x = first.x;
	current.y = first.y;
	diff.x = abs(second.x - first.x);
	diff.y = abs(second.y - first.y);
	inc.x = (second.x - first.x) > 0 ? 1 : -1;
	inc.y = (second.y - first.y) > 0 ? 1 : -1;
	next_color(e, e->height_a);
	if (current.x > 0 && current.x < WIN_W
			&& current.y > 100 && current.y < WIN_H - 125)
		image_put_pixel(e->image, current, e->size_line, e->color);
	if (diff.x > diff.y)
		print_segment_on_x(e, diff, current, inc);
	else
		print_segment_on_y(e, diff, current, inc);
}
