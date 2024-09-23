/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressing_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:20:58 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 18:06:51 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_key(int key, t_data *vars)
{
	ft_key_weapon(vars, key);
	if (key == 0)
		vars->a = 1;
	if (key == 2)
		vars->d = 1;
	if (key == 124)
		vars->view_speed = 2 * (M_PI / 180);
	if (key == 123)
		vars->view_speed = -(2 * (M_PI / 180));
	if (key == 53)
		ft_close(vars);
	if (key == 49)
	{
		if (ft_open_door(vars) == 1)
			return (0);
		else if (ft_close_door(vars) == 1)
			return (0);
	}
	if (key == 36)
		vars->start_screen = 1;
	return (0);
}

void	ft_key_weapon(t_data *vars, int key)
{
	if (key == 13)
		(1) && (vars->w = 1, vars->weapon_index = 1);
	if (key == 1)
		(1) && (vars->s = 1, vars->weapon_index = 1);
	if (key == 18)
		(1) && (vars->weapon0 = 1, vars->weapon2 = 1);
	if (key == 19)
		vars->weapon0 = 0;
}

int	ft_open_door(t_data *vars)
{
	int	i;

	i = 0;
	if (ft_check_wall_d(vars, vars->x + (TILE * vars->xs), vars->y, 'D') == 2)
	{
		vars->map[(int)(vars->y / TILE)][(int)(vars->x / TILE) + vars->xs]
			= 'd';
		i = 1;
	}
	if (ft_check_wall_d(vars, vars->x, vars->y + (TILE * vars->ys), 'D') == 2)
	{
		vars->map[(int)(vars->y / TILE) + vars->ys][(int)(vars->x / TILE)]
			= 'd';
		i = 1;
	}
	return (i);
}

int	ft_close_door(t_data *vars)
{
	int	i;

	i = 0;
	if (ft_check_wall_d(vars, vars->x + (TILE * vars->xs), vars->y, 'd') == 2)
	{
		vars->map[(int)(vars->y / TILE)][(int)(vars->x / TILE) + vars->xs]
			= 'D';
		i = 1;
	}
	if (ft_check_wall_d(vars, vars->x, vars->y + (TILE * vars->ys), 'd') == 2)
	{
		vars->map[(int)(vars->y / TILE) + vars->ys][(int)(vars->x / TILE)]
			= 'D';
		i = 1;
	}
	return (i);
}

int	ft_rel(int key, t_data *vars)
{
	if (key == 13 || key == 1)
	{
		vars->weapon_index = 0;
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
