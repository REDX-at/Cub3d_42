/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:09:29 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/21 11:11:09 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_vertical_ray(t_data *vars)
{
	double	a;
	double	b;

	a = vars->x * RESOLVE;
	b = vars->y * RESOLVE;
	vars->vy = ((floor(b / (TILE * RESOLVE)) * (TILE * RESOLVE)));
	if (vars->ys == 1)
		vars->vy += (TILE * RESOLVE);
	vars->vx = ((vars->vy - b) / tan(vars->view)) + a;
	vars->ystep = (TILE * RESOLVE);
	vars->xstep = (TILE * RESOLVE) / tan(vars->view);
	if (vars->xstep < 0)
		vars->xstep = -vars->xstep;
	vars->ystep *= vars->ys;
	vars->xstep *= vars->xs;
	if (vars->ys == -1)
		vars->vy--;
	while (ft_check_wall(vars, vars->vx / (RESOLVE * TILE),
			vars->vy / (RESOLVE * TILE)) == 0)
		(1) && (vars->vx += vars->xstep, vars->vy += vars->ystep);
	vars->vc = sqrt(((vars->vx - a) * (vars->vx - a))
			+ ((vars->vy - b) * (vars->vy - b))) * cos(vars->al);
	if (vars->vc < 0)
		vars->vc = -vars->vc;
	vars->vc = vars->vc / RESOLVE;
}

void	ft_horisontale(t_data *vars)
{
	double	a;
	double	b;

	(1) && (a = vars->x * RESOLVE, b = vars->y * RESOLVE);
	vars->hx = ((floor(a / ((TILE * RESOLVE)))) * (TILE * RESOLVE));
	if (vars->xs == 1)
		vars->hx += (TILE * RESOLVE);
	vars->hy = (vars->hx - a) * tan(vars->view);
	vars->hy = b + (vars->hy);
	vars->xstep = (TILE * RESOLVE);
	vars->ystep = (TILE * RESOLVE) * tan(vars->view);
	if (vars->ystep < 0)
		vars->ystep = -vars->ystep;
	vars->xstep *= vars->xs;
	vars->ystep *= vars->ys;
	if (vars->xs == -1)
		vars->hx--;
	while (ft_check_wall(vars, vars->hx / (RESOLVE * TILE),
			vars->hy / (RESOLVE * TILE)) == 0)
		(1) && (vars->hx += vars->xstep, vars->hy += vars->ystep);
	vars->hc = sqrt(((vars->hx - a) * (vars->hx - a)) + ((vars->hy - b)
				* (vars->hy - b))) * cos(vars->al);
	if (vars->hc < 0)
		vars->hc = -vars->hc;
	vars->hc = vars->hc / RESOLVE;
}

void	ft_take_first_hit(t_data *vars)
{
	get_view(vars);
	if (fabs(sin(vars->view)) > 1e-6)
		ft_vertical_ray(vars);
	else
		vars->vc = -1;
	if (fabs(cos(vars->view)) > 1e-6)
		ft_horisontale(vars);
	else
		vars->hc = -1;
	if (vars->vc == -1)
		vars->c = vars->hc;
	else if (vars->hc == -1)
		vars->c = vars->vc;
	else
	{
		if (vars->vc < vars->hc)
			vars->c = vars->vc;
		else
			vars->c = vars->hc;
	}
}

void	ft_calculate(t_data *vars, t_textures **texture, int *h, int *wall_h)
{
	ft_take_first_hit(vars);
	ft_find_texture(vars, texture);
	(*wall_h) = (TILE / vars->c) * ((WINDOW_WIDTH / 2) / tan(POV / 2));
	if ((*wall_h) < 0)
		(*wall_h) = -(*wall_h);
	vars->med = (WINDOW_HEIGHT / 2);
	*h = (vars->med - ((*wall_h) / 2));
	if (vars->wallhit == 1)
		vars->hit_index = (vars->wallx - (floor(vars->wallx / TILE) * TILE));
	else
		vars->hit_index = (vars->wally - (floor(vars->wally / TILE) * TILE));
	vars->tex_x = fmod(vars->hit_index * (*texture)->width / TILE,
			(*texture)->width);
}

void	ft_draw_ray(t_data *vars)
{
	int			h;
	int			wall_height;
	int			color;
	t_textures	*texture;

	(1) && (h = 0, wall_height = 0);
	ft_calculate(vars, &texture, &h, &wall_height);
	while (h <= vars->med + (wall_height / 2) && h < WINDOW_HEIGHT)
	{
		if (h < 0)
			h = 0;
		if (h >= WINDOW_HEIGHT)
			h = WINDOW_HEIGHT - 1;
		vars->tex_y = (h - (vars->med - (wall_height / 2)))
			* texture->height / wall_height;
		if (vars->tex_y >= texture->height)
			vars->tex_y = texture->height - 1;
		color = *(unsigned int *)(texture->addr + (vars->tex_y
					* texture->line_lenght + vars->tex_x
					* (texture->bits_per_pixel / 8)));
		my_pixel_put(vars, vars->px_x, h, color);
		h++;
	}
	vars->px_x += 1;
}
