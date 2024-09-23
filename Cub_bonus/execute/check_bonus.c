/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:10:20 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 18:11:36 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_close(t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
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
		if (ft_check_wall(vars, ((vars->x + x) / TILE), ((vars->y + y) / TILE)
				+ sy) && ft_check_wall(vars, ((vars->x + x) / TILE) + sx,
				((vars->y + y) / TILE)))
		{
			if ((int)(vars->y / TILE) == (int)((vars->y + y) / TILE)
				&& (int)(vars->x / TILE) == (int)((vars->x + x) / TILE))
				return (0);
			return (1);
		}
	}
	return (0);
}

int	ft_check_wall(t_data *vars, double x, double y)
{
	int	i;
	int	j;

	i = (int)x;
	j = (int)y;
	if (i < 0 || j < 0 || i >= vars->width || j >= vars->height)
		return (1);
	if (vars->map[j][i] == '1' || vars->map[j][i] == 'D')
		return (1);
	return (0);
}

int	ft_check_wall_d(t_data *vars, double x, double y, int wall)
{
	int	i;
	int	j;

	i = floor(x / TILE);
	j = floor(y / TILE);
	if (i < 0 || j < 0 || i >= vars->width || j >= vars->height)
		return (1);
	if ((wall == 1 || wall == 3) && vars->map[j][i] == '1')
		return (1);
	if ((wall == 2 || wall == 3) && vars->map[j][i] == 'D')
		return (2);
	if (wall == 'd' && vars->map[j][i] == 'd')
		return (2);
	if (wall == 'D' && vars->map[j][i] == 'D')
		return (2);
	return (0);
}

void	get_view(t_data *vars)
{
	if (cos(vars->view) > 0)
		vars->xs = 1;
	else if (cos(vars->view) < 0)
		vars->xs = -1;
	else
		vars->xs = 0;
	if (sin(vars->view) > 0)
		vars->ys = 1;
	else if (sin(vars->view) < 0)
		vars->ys = -1;
	else
		vars->ys = 0;
}
