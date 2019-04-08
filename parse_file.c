/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <acostaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:39:41 by acostaz           #+#    #+#             */
/*   Updated: 2019/04/08 14:36:39 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Reading and stocking one line, checking if the line is empty or not
*/

static int	get_map_data(t_data *e)
{
	char	*line;
	int		ret;

	ret = 0;
	if (get_next_line(e->fd, &line) == 1)
	{
		e->line = ft_strsplit(line, ' ');
		free(line);
		if (!e->line)
			ft_error("Invalid map");
		++ret;
	}
	else
		free(line);
	return (ret);
}

/*
** Going through the file once, checking if no lines are empty
** Then calculating the input's size
** Last, allocating the (int**) map with the input's size
*/

static void	read_file(t_data *e, char *filename)
{
	char	*line;
	int		len;

	e->col_nbr = 0;
	e->line_nbr = 0;
	while (get_next_line(e->fd, &line) == 1)
	{
		++e->line_nbr;
		len = ft_strlen(line);
		free(line);
		if (!len)
			ft_error("Invalid file");
	}
	free(line);
	if (e->line_nbr == 0)
		ft_error("Empty file");
	close(e->fd);
	e->fd = open(filename, O_RDONLY);
	get_map_data(e);
	while (e->line[e->col_nbr])
		++e->col_nbr;
	e->max_h = ft_atoi(e->line[0]);
	e->min_h = e->max_h;
	alloc_map(e);
}

static void	free_data_line(t_data *e)
{
	int		i;

	i = 0;
	while (e->line[i])
	{
		free(e->line[i]);
		++i;
	}
	free(e->line);
}

/*
** Find the min and max height in file
*/

static void	find_min_max(t_data *e, int i, int j)
{
	if (e->map[i][j] > e->max_h)
		e->max_h = e->map[i][j];
	if (e->map[i][j] < e->min_h)
		e->min_h = e->map[i][j];
}

/*
** First checks with above functions
** Then filling the (int**) map with the input's data
*/

void		parse_file(t_data *e, char *filename)
{
	int	nbr_col;

	nbr_col = -1;
	if ((e->fd = open(filename, O_RDONLY)) <= 0)
		ft_error("Invalid file");
	read_file(e, filename);
	while (++nbr_col < e->col_nbr)
	{
		e->map[0][nbr_col] = ft_atoi(e->line[nbr_col]);
		find_min_max(e, 0, nbr_col);
	}
	free_data_line(e);
	while ((++e->line_nbr) && get_map_data(e) == 1)
	{
		nbr_col = -1;
		while (e->line[++nbr_col])
		{
			e->map[e->line_nbr][nbr_col] = ft_atoi(e->line[nbr_col]);
			find_min_max(e, e->line_nbr, nbr_col);
		}
		if (nbr_col != e->col_nbr)
			free_map(e, 1, "Invalid map");
		free_data_line(e);
	}
}
