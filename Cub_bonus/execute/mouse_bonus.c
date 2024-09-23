/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:59:21 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 18:12:49 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_mouse(int key, int x, int y, t_data *vars)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (0);
	if (key == 1)
	{
		if (vars->mouse_on == 1)
			vars->mouse_on = 2;
	}
	if (key == 2)
	{
		if (vars->mouse_on == 1)
			vars->mouse_on = 0;
		else
			vars->mouse_on = 1;
	}
	if (key == 3)
	{
		if (vars->move_mouse == 0)
			vars->move_mouse = 1;
		else
			vars->move_mouse = 0;
	}
	return (0);
}

int	mouse_up(int key, int x, int y, t_data *vars)
{
	if ((key == 1 || key == 2) && x >= 0 && x <= WINDOW_WIDTH
		&& y >= 0 && y <= WINDOW_HEIGHT)
		vars->view_speed = 0;
	return (0);
}

int	ft_mouse_move(int x, int y, t_data *vars)
{
	static int	prev_x = WINDOW_WIDTH / 2;
	int			dx;

	if (x < 0)
		x = 0;
	(void)y;
	if (x > WINDOW_WIDTH)
		x = WINDOW_WIDTH;
	dx = x - prev_x;
	if (vars->move_mouse == 1)
		vars->view_speed = dx * (M_PI / 180) * 0.3;
	else
		vars->view_speed = 0;
	prev_x = x;
	return (0);
}
