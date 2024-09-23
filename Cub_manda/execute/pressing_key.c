/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressing_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:13:07 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/21 11:16:30 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_key(int key, t_data *vars)
{
	if (key == 13)
		vars->w = 1;
	if (key == 1)
		vars->s = 1;
	if (key == 2)
		vars->d = 1;
	if (key == 0)
		vars->a = 1;
	if (key == 124)
	{
		vars->view_speed = 2 * (M_PI / 180);
	}
	if (key == 123)
	{
		vars->view_speed = -(2 * (M_PI / 180));
	}
	if (key == 53)
		ft_close(vars);
	return (0);
}

int	ft_rel(int key, t_data *vars)
{
	if (key == 13 || key == 1)
	{
		vars->up_down_x = 0;
		vars->up_down_y = 0;
	}
	if (key == 0 || key == 2)
	{
		vars->lr_x = 0;
		vars->lr_y = 0;
	}
	if (key == 13)
		vars->w = 0;
	if (key == 1)
		vars->s = 0;
	if (key == 0)
		vars->a = 0;
	if (key == 2)
		vars->d = 0;
	if (key == 123 || key == 124)
		vars->view_speed = 0;
	return (0);
}

void	ft_color(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			if (j < WINDOW_HEIGHT / 2)
				my_pixel_put(vars, i, j, vars->alloc->color_c);
			else
				my_pixel_put(vars, i, j, vars->alloc->color_f);
			j++;
		}
		i++;
	}
}

int	ft_check(t_data *vars, double x, double y)
{
	int	sx;
	int	sy;

	ft_get_sign(&sx, &sy, x, y);
	if (ft_check_wall(vars, ((vars->x + x) / TILE), ((vars->y + y) / TILE)))
		return (1);
	if (ft_check_wall(vars, ((vars->x + x) / TILE),
			((vars->y + y) / TILE)) == 0)
	{
		if (ft_check_wall(vars, ((vars->x + x) / TILE),
				((vars->y + y) / TILE) + sy) && ft_check_wall(vars,
				((vars->x + x) / TILE) + sx, ((vars->y + y) / TILE)))
		{
			if ((int)(vars->y / TILE) == (int)((vars->y + y) / TILE)
				&& (int)(vars->x / TILE) == (int)((vars->x + x) / TILE))
				return (0);
			return (1);
		}
	}
	return (0);
}

int	ft_close(t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}
