/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:08:09 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/19 16:35:13 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	ft_get_angle(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'S')
		return ((3 * M_PI) / 2);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (M_PI);
	return (0);
}

void	ft_get_player(t_data *vars, int i, int j)
{
	if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S'
		|| vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
	{
		vars->view = ft_get_angle(vars->map[i][j]);
		(1) && (vars->x = j, vars->y = i);
		vars->map[i][j] = '0';
	}
}

void	ft_get_size(t_data *vars)
{
	int	i;
	int	j;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (vars->map[i])
	{
		j = 0;
		len = 0;
		while (vars->map[i][j])
		{
			ft_get_player(vars, i, j);
			len++;
			j++;
		}
		if (len > max)
			max = len;
		i++;
	}
	vars->width = max;
	vars->height = i;
}

int	ft_close(t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void	ft_get_sign(int *sx, int *sy, double x, double y)
{
	if (x < (double)0)
		*sx = 1;
	else
		*sx = -1;
	if (y < (double)0)
		*sy = 1;
	else
		*sy = -1;
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

void	ft_w(t_data *vars)
{
	vars->up_down_x = ((cos(vars->view)) * TILE / 25);
	vars->up_down_y = ((sin(vars->view)) * TILE / 25);
}

void	ft_s(t_data *vars)
{
	vars->up_down_x = cos((vars->view + M_PI)) * TILE / 25;
	vars->up_down_y = sin(vars->view + M_PI) * TILE / 25;
}

void	ft_d(t_data *vars)
{
	vars->lr_x = cos((vars->view + (M_PI / 2))) * TILE / 25;
	vars->lr_y = sin((vars->view + (M_PI / 2))) * TILE / 25;
}

void	ft_a(t_data *vars)
{
	vars->lr_x = cos((vars->view - (M_PI / 2))) * TILE / 25;
	vars->lr_y = sin((vars->view - (M_PI / 2))) * TILE / 25;
}

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

void	my_pixel_put(t_data *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->size_l + x * (vars->bpp / 8));
	*(unsigned int *)dst = color;
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

int	ft_check_wall(t_data *vars, double x, double y)
{
	int	i;
	int	j;

	i = (int)x;
	j = (int)y;
	if (i < 0 || j < 0 || i >= vars->width || j >= vars->height)
		return (1);
	if (vars->map[j][i] == '1')
		return (1);
	return (0);
}

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

void	ft_get_texture(t_data *vars, t_textures **texture)
{
	if (vars->c == vars->vc)
	{
		vars->wallx = vars->vx / RESOLVE;
		vars->wally = vars->vy / RESOLVE;
		vars->wallhit = 1;
		if (sin(vars->view) > 0)
			*texture = vars->textures_north_struct;
		else
			*texture = vars->textures_south_struct;
	}
	else
	{
		vars->wallx = vars->hx / RESOLVE;
		vars->wally = vars->hy / RESOLVE;
		vars->wallhit = 2;
		if (cos(vars->view) > 0)
			*texture = vars->textures_east_struct;
		else
			*texture = vars->textures_west_struct;
	}
}

void	ft_calculate(t_data *vars, t_textures **texture, int *h, int *wall_h)
{
	ft_take_first_hit(vars);
	ft_get_texture(vars, texture);
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

void	ft_add(t_data *vars)
{
	if (vars->w)
		ft_w(vars);
	if (vars->s)
		ft_s(vars);
	if (vars->a)
		ft_a(vars);
	if (vars->d)
		ft_d(vars);
	if ((vars->w && vars->s))
	{
		vars->up_down_x = 0;
		vars->up_down_y = 0;
	}
	if ((vars->a && vars->d))
	{
		vars->lr_x = 0;
		vars->lr_y = 0;
	}
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

void	ft_imgs(t_data *vars)
{
	if (ft_check(vars, vars->up_down_x + vars->lr_x,
			vars->up_down_y + vars->lr_y) == 0)
	{
		vars->x += vars->up_down_x + vars->lr_x;
		vars->y += vars->up_down_y + vars->lr_y;
	}
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp,
			&vars->size_l, &vars->endian);
}

int	ft_player(t_data *vars)
{
	double	v;
	double	tmp;
	int		n;

	n = 0;
	vars->view += vars->view_speed;
	ft_add(vars);
	ft_imgs(vars);
	(1) && (tmp = vars->view + (POV / 2), v = vars->view);
	vars->view = v - (POV / 2);
	ft_color(vars);
	vars->px_x = 0;
	while (n < WINDOW_WIDTH)
	{
		vars->al = v - vars->view;
		ft_draw_ray(vars);
		(1) && (vars->view += POV / WINDOW_WIDTH, n++);
	}
	vars->view = v;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

void	ft_mlx(t_data *vars)
{
	mlx_hook(vars->win, 17, 1, ft_close, vars);
	mlx_hook(vars->win, 2, 1L << 0, ft_key, vars);
	mlx_hook(vars->win, 3, 1L << 1, ft_rel, vars);
	mlx_loop_hook(vars->mlx, ft_player, vars);
	mlx_loop(vars->mlx);
}

void	ft_execute(t_alloc *alloc)
{
	t_data	vars;

	ft_memset(&vars, 0, sizeof(t_data));
	vars.map = alloc->map;
	vars.alloc = alloc;
	ft_get_size(&vars);
	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		printf("Failed to init mlx\n");
		exit(1);
	}
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!vars.win)
	{
		printf("Failed to create window\n");
		exit(1);
	}
	vars.y = floor(vars.y * TILE) + (TILE / 2);
	vars.x = floor(vars.x * TILE) + (TILE / 2);
	get_texture(&vars);
	ft_mlx(&vars);
}
