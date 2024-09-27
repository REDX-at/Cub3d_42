/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:09 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/27 18:10:08 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_delay_weapon(t_data *vars)
{
	if (vars->delay_weapon < 3)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_official->img_weap, vars->weap_x,
			vars->weap_y);
	if (vars->delay_weapon >= 3 && vars->delay_weapon < 6)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_official->img_weap, vars->weap_x,
			vars->weap_y);
	if (vars->delay_weapon >= 6 && vars->delay_weapon < 12)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_offic_1->img_weap, vars->weap_x,
			vars->weap_y);
	if (vars->delay_weapon >= 12 && vars->delay_weapon < 18)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_offic_2->img_weap, vars->weap_x,
			vars->weap_y);
	if (vars->delay_weapon >= 18 && vars->delay_weapon < 24)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_offic_3->img_weap, vars->weap_x,
			vars->weap_y);
	if (vars->delay_weapon >= 24 && vars->delay_weapon < 30)
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_offic_4->img_weap, vars->weap_x,
			vars->weap_y);
}

void	ft_weapon(t_data *vars)
{
	if (vars->weapon0 == 0 && vars->mouse_on == 0)
	{
		if (vars->delay_weapon >= 36)
			vars->delay_weapon = 1;
		draw_circle(vars, 2, 0xFFFF00);
		vars->weap_x = WINDOW_WIDTH - vars->weapon_official->img_weap_width;
		vars->weap_y = WINDOW_HEIGHT
			- vars->weapon_official->img_weap_height;
		ft_delay_weapon(vars);
		if (vars->delay_weapon >= 30 && vars->delay_weapon < 36)
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->weapon_offic_5->img_weap, vars->weap_x,
				vars->weap_y);
		vars->delay_weapon++;
	}
}

void	ft_weapon_animation(t_data *vars)
{
	ft_weapon(vars);
	if (vars->mouse_on == 1)
	{
		vars->weap_x = (WINDOW_WIDTH / 2)
			- (vars->weapon_shoot->img_weap_width / 2);
		vars->weap_y = WINDOW_HEIGHT - vars->weapon_shoot->img_weap_height;
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_shoot->img_weap, vars->weap_x, vars->weap_y);
	}
	if (vars->delay == 15)
	{
		vars->mouse_on = 0;
		vars->delay = 0;
	}
	if (vars->mouse_on == 2 && vars->delay < 15)
	{
		vars->weap_x = (WINDOW_WIDTH / 2)
			- (vars->weapon_zoom->img_weap_width / 2);
		vars->weap_y = WINDOW_HEIGHT - vars->weapon_zoom->img_weap_height;
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->weapon_zoom->img_weap, vars->weap_x, vars->weap_y);
		vars->delay++;
	}
}

void	draw_circle(t_data *vars, int radius, int color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
			{
				x = (WINDOW_WIDTH / 2) + dx;
				y = (WINDOW_HEIGHT / 2) + dy;
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
					mlx_pixel_put(vars->mlx, vars->win, x, y, color);
			}
			dx++;
		}
		dy++;
	}
}
