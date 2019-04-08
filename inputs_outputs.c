/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:16:57 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:35:46 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Used at beginning of program or to reset most changes to initial values
*/

void		clear_setup(t_data *e)
{
	e->speed = 5;
	e->angle = 0;
	e->scale = e->mode ? 150 : 500;
	e->zoom = 10 * (WIN_W + WIN_H) / (e->line_nbr + e->col_nbr);
	(e->top).x = WIN_W / 2;
	(e->top).y = WIN_H / 2;
}

/*
** Ugly necessary function
*/

static void	process_colors(t_data *e, int *key)
{
	if (key[KEY_PAD_0])
		e->display = 0;
	if (key[KEY_PAD_1])
		e->display = 1;
	if (key[KEY_PAD_2])
		e->display = 2;
	if (key[KEY_PAD_3])
		e->display = 3;
	if (key[KEY_PAD_4])
		e->display = 4;
	if (key[KEY_PAD_5])
		e->display = 5;
	if (key[KEY_PAD_6])
		e->display = 6;
	if (key[KEY_PAD_7])
		e->display = 7;
	if (key[KEY_PAD_8])
		e->display = 8;
	if (key[KEY_PAD_9])
		e->display = 9;
	if (key[KEY_PAD_MULTIPLY])
		e->display = 10;
}

/*
** Deals with every movement-related events
*/

static void	process_movement(t_data *e, int *key)
{
	if (key[KEY_LEFT] || key[KEY_RIGHT])
		e->angle += ((key[KEY_RIGHT] - key[KEY_LEFT]) * 0.1);
	if (key[KEY_UP] && e->zoom < 1000000)
	{
		e->zoom *= 1.1;
		if (e->mode == 0)
			e->scale *= 1.1;
	}
	if (key[KEY_DOWN] && e->zoom > 10 * (WIN_W + WIN_H) /
			(e->line_nbr + e->col_nbr))
	{
		e->zoom /= 1.1;
		if (e->mode == 0)
			e->scale /= 1.1;
	}
	if (key[KEY_PG_UP] && !(e->mode == 1 && e->scale > 950))
		e->scale += 50;
	if (key[KEY_PG_DOWN] && !(e->mode == 1 && e->scale < -950))
		e->scale -= 50;
	if (key[KEY_W] || key[KEY_S])
		(e->top).y += (key[KEY_S] - key[KEY_W]) * e->speed;
	if (key[KEY_A] || key[KEY_D])
		(e->top).x += (key[KEY_D] - key[KEY_A]) * e->speed;
	if (key[KEY_PAD_ADD] || (key[KEY_PAD_SUB] && e->speed > 0))
		e->speed += (key[KEY_PAD_ADD] - key[KEY_PAD_SUB]);
}

/*
** Main function for events' management
*/

int			process_win(void *param)
{
	int		*key;
	t_data	*e;

	e = (t_data*)param;
	key = e->keyboard;
	if (key[KEY_ESC])
		free_and_exit(e);
	if (key[KEY_CLEAR] || (key[KEY_1] && e->mode == 1) ||
			(key[KEY_2] && e->mode == 0))
	{
		if (key[KEY_1] || key[KEY_2])
			e->mode = key[KEY_1] ? 0 : 1;
		clear_setup(e);
	}
	e->menu = key[KEY_M];
	process_movement(e, key);
	process_colors(e, key);
	ft_bzero(&(e->image[WIN_W * 400]), WIN_W * (WIN_H - 200) * 4);
	print_grid(e, e->col_nbr * e->line_nbr);
	print_menu_win(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_addr, 0, 0);
	print_borders(e);
	print_menu(e);
	return (0);
}
