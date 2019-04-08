/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 13:57:25 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:36:19 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Custom function to print a pixel on the image, and not directly on the window
*/

void		image_put_pixel(char *img_data, t_pos pos, int width, int color)
{
	if (pos.x >= 0 && pos.x < WIN_W && pos.y >= 0 && pos.y < WIN_H)
		*(int *)&img_data[(pos.y * width) + (pos.x * 4)] = color;
}

static int	release_key(int key, void *param)
{
	if (key != KEY_M)
		((t_data*)param)->keyboard[key] = 0;
	return (0);
}

/*
** press_key and release_key work with an (int*) to have responsive inputs and
**	to make holding down a key have the expected effect
** A special case is made for M, to have a toggle on / toggle off effect
*/

static int	press_key(int key, void *param)
{
	if (key == KEY_M)
		((t_data*)param)->keyboard[KEY_M] =
			((t_data*)param)->keyboard[KEY_M] == 1 ? 0 : 1;
	else
		((t_data*)param)->keyboard[key] = 1;
	return (0);
}

int			main(int ac, char **av)
{
	t_data	e;

	if (ac != 2)
		ft_error("Several or zero arguments given");
	parse_file(&e, av[1]);
	if (!((e.mlx = mlx_init())
				&& (e.win = mlx_new_window(e.mlx, WIN_W, WIN_H, "FdF"))))
		free_map(&e, 1, "mlx function crashed");
	if (!(e.trigrid = (t_xyz*)malloc(sizeof(t_xyz) * e.col_nbr * e.line_nbr)))
		free_map(&e, 1, "Malloc error");
	e.mode = 0;
	e.menu = 0;
	e.display = 0;
	make_grid(&e);
	clear_setup(&e);
	e.img_addr = mlx_new_image(e.mlx, WIN_W, WIN_H);
	e.image = mlx_get_data_addr(e.img_addr, &e.bpp, &e.size_line, &e.endian);
	print_borders(&e);
	mlx_hook(e.win, KEYPRESS, KEYPRESSMASK, press_key, &e);
	mlx_hook(e.win, KEYRELEASE, KEYRELEASEMASK, release_key, &e);
	mlx_loop_hook(e.mlx, process_win, &e);
	mlx_loop(e.mlx);
	return (0);
}
