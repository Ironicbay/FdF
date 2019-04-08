/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:35:48 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:34:58 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_shown(t_data *e)
{
	t_pos	pos;

	pos.y = 109;
	while (++pos.y < 423)
	{
		pos.x = 9;
		while (++pos.x < 405)
		{
			if (pos.y < 115 || pos.y > 417 || pos.x < 15 || pos.x > 399
					|| (pos.x > 204 && pos.x < 210 && pos.y > 143)
					|| (pos.y > 143 && pos.y < 149))
				image_put_pixel(e->image, pos, e->size_line, 0x777777);
			else
				image_put_pixel(e->image, pos, e->size_line, 0x00030);
		}
	}
}

static void	print_hidden(t_data *e)
{
	t_pos	pos;

	pos.y = 109;
	while (++pos.y < 145)
	{
		pos.x = 9;
		while (++pos.x < 280)
		{
			if (pos.y < 115 || pos.y > 139 || pos.x < 15 || pos.x > 274)
				image_put_pixel(e->image, pos, e->size_line, 0x777777);
			else
				image_put_pixel(e->image, pos, e->size_line, 0x00030);
		}
	}
}

/*
** Prints menu's frame
*/

void		print_menu_win(t_data *e)
{
	if (e->menu == 1)
		print_shown(e);
	else
		print_hidden(e);
}

/*
** Prints menu's text
*/

void		print_menu(t_data *e)
{
	if (e->menu == 0)
		mlx_string_put(e->mlx, e->win, 10, 115, 0xDDDDDD, M_PROMPT);
	else
	{
		mlx_string_put(e->mlx, e->win, 10, 105 + 13, 0xDDDDDD, CONTROLS);
		mlx_string_put(e->mlx, e->win, 10, 120 + 34, 0xDDDDDD, M_UP_DOWN);
		mlx_string_put(e->mlx, e->win, 10, 120 + 52, 0xDDDDDD, M_LEFT_RIGHT);
		mlx_string_put(e->mlx, e->win, 10, 120 + 70, 0xDDDDDD, M_MOVE_SPEED);
		mlx_string_put(e->mlx, e->win, 10, 120 + 88, 0xDDDDDD, M_ZOOM);
		mlx_string_put(e->mlx, e->win, 10, 120 + 106, 0xDDDDDD, M_ROTATE);
		mlx_string_put(e->mlx, e->win, 10, 120 + 124, 0xDDDDDD, M_HEIGHT);
		mlx_string_put(e->mlx, e->win, 10, 120 + 142, 0xDDDDDD, M_COLOR);
		mlx_string_put(e->mlx, e->win, 10, 120 + 178, 0xDDDDDD, M_DISPLAY_ISO);
		mlx_string_put(e->mlx, e->win, 10, 120 + 196, 0xDDDDDD, M_DISPLAY_PAR);
		mlx_string_put(e->mlx, e->win, 10, 120 + 232, 0xDDDDDD, M_CLOSE_MENU);
		mlx_string_put(e->mlx, e->win, 10, 120 + 250, 0xDDDDDD, M_RESET);
		mlx_string_put(e->mlx, e->win, 10, 120 + 268, 0xDDDDDD, M_EXIT);
	}
}

/*
** Basic border printing with given heights
*/

void		print_borders(t_data *e)
{
	t_pos	position;

	position.x = -1;
	while (++position.x < WIN_W)
	{
		position.y = -1;
		while (++position.y < 100)
		{
			if (position.y < 75)
				image_put_pixel(e->image, position, e->size_line, 0x1F7070);
			else
				image_put_pixel(e->image, position, e->size_line, 0x134340);
		}
	}
	position.x = -1;
	while (++position.x < WIN_W)
	{
		position.y = WIN_H - 1;
		while (--position.y >= WIN_H - 100)
			if (position.y > WIN_H - 75)
				image_put_pixel(e->image, position, e->size_line, 0x1F7070);
			else
				image_put_pixel(e->image, position, e->size_line, 0x134340);
	}
	mlx_string_put(e->mlx, e->win, WIN_W / 2 - 75, 25, 0xDDDDDD, BORDER_NAME);
}
