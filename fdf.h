/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:57:51 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:33:41 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "key_mapping.h"
# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIN_W 2560
# define WIN_H 1400

# define KEYPRESS 2
# define KEYRELEASE 3

# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)

# define REDCROSS 17
# define REDCROSSMASK (1L<<17)

# define C_WHITE 0xFFFFFF
# define C_BLACK 0x000000
# define C_RED 0xFF0000
# define C_ORANGE 0xFF4500
# define C_YELLOW 0xFFFF00
# define C_GREEN 0x00FF00
# define C_TURQUOISE 0x00FFE6
# define C_BLUE 0x0000FF
# define C_PURPLE 0x8A2BE2

# define BORDER_NAME	"FdF by acostaz"

# define M_PROMPT		"  Press M to display menu"
# define CONTROLS		"                CONTROLS               "
# define M_UP_DOWN		"    move up/down            W/S        "
# define M_LEFT_RIGHT	"  move left/right           A/D        "
# define M_MOVE_SPEED	" change move speed          +/-        "
# define M_ZOOM			"        zoom          up/down arrows   "
# define M_HEIGHT		"   change height       page up/down    "
# define M_ROTATE		" rotate left/right   left/right arrows "
# define M_COLOR		"       colors         num pad numbers  "
# define M_DISPLAY_ISO	"     isometric               1         "
# define M_DISPLAY_PAR	"   3D perspective            2         "
# define M_CLOSE_MENU	"     close menu              M         "
# define M_RESET		"    undo changes           clear       "
# define M_EXIT			"    exit program            esc        "

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_xyz
{
	int				x;
	int				y;
	int				z;
}					t_xyz;

typedef struct		s_data
{
	int				fd;

	t_xyz			*trigrid;
	int				**map;
	int				line_nbr;
	int				col_nbr;
	char			**line;

	int				max_h;
	int				min_h;
	double			height_a;
	double			height_b;

	t_pos			top;
	int				scale;
	int				zoom;
	double			angle;
	int				color;
	int				display;
	int				menu;
	int				mode;
	int				speed;

	void			*mlx;
	void			*win;
	int				keyboard[280];
	void			*img_addr;
	char			*image;
	int				bpp;
	int				size_line;
	int				endian;
}					t_data;

int					process_win(void *param);
void				clear_setup(t_data *e);
void				image_put_pixel(char *img_data, t_pos pos,
									int width, int color);
void				draw_segment(t_data *e, t_pos first, t_pos second);
void				parse_file(t_data *e, char *input);
void				make_grid(t_data *e);
void				print_grid(t_data *e, int size);
void				get_color(t_data *e, int index, int diff);
void				next_color(t_data *e, double height);
void				print_borders(t_data *e);
void				print_menu(t_data *e);
void				print_menu_win(t_data *e);
void				alloc_map(t_data *e);
void				free_map(t_data *e, int error, char *message);
void				free_and_exit(t_data *e);

#endif
