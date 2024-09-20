/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:08:09 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 16:12:49 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

void	my_pixel_put(t_data *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->size_l + x * (vars->bpp / 8));
	*(unsigned int *)dst = color;
}

void	my_pixel_put2(t_data *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr_map + (y * vars->size_lmap + x * (vars->bpp_map / 8));
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
	if (vars->map[j][i] == '1' || vars->map[j][i] == 'D')
		return (1);
	return (0);
}

void	ft_vertical_ray(t_data *vars)
{
	double	a;
	double	b;

	(1) && (a = vars->x * RESOLVE, b = vars->y * RESOLVE);
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
	vars->vc = sqrt(((vars->vx - a) * (vars->vx - a)) + ((vars->vy - b)
				* (vars->vy - b))) * cos(vars->al);
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

void	ft_take_first_hit(t_data *vars)
{
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
		(1) && (vars->wally = vars->vy / RESOLVE, vars->wallhit = 1);
		if (sin(vars->view) > 0)
			*texture = vars->textures_north_struct;
		else
			*texture = vars->textures_south_struct;
	}
	else
	{
		vars->wallx = vars->hx / RESOLVE;
		(1) && (vars->wally = vars->hy / RESOLVE, vars->wallhit = 2);
		if (cos(vars->view) > 0)
			*texture = vars->textures_east_struct;
		else
			*texture = vars->textures_west_struct;
	}
}

void	ft_calculate(t_data *vars, t_textures **texture, int *h, int *wall_h)
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
	ft_take_first_hit(vars);
	ft_get_texture(vars, texture);
	*wall_h = (TILE / vars->c) * ((WINDOW_WIDTH / 2) / tan(POV / 2));
	if (wall_h < 0)
		*wall_h = -(*wall_h);
	vars->med = (WINDOW_HEIGHT / 2);
	*h = (vars->med - (*wall_h / 2));
	if (ft_check_wall_d(vars, vars->wallx, vars->wally, 2) == 2)
		(*texture) = vars->textures_door_struct;
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

void	ft_wall(t_data *vars, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i <= vars->map_tsize - 1)
	{
		j = 0;
		while (j <= vars->map_tsize - 1)
		{
			my_pixel_put2(vars, (x * vars->map_tsize) + i,
				(y * vars->map_tsize) + j, color);
			j++;
		}
		i++;
	}
}

void	ft_draw(t_data *vars, int i, int j)
{
	if (i >= 0 && j >= 0 && j < vars->height
		&& i < (int)ft_strlen(vars->map[j]) && vars->map[j][i] == '1')
		ft_wall(vars, i - (floor(vars->x / TILE) - (MINIMAP_WIDTH / 2)),
			j - (floor(vars->y / TILE) - (MINIMAP_WIDTH / 2)),
			0xFFFFFFF);
	if (i >= 0 && j >= 0 && j < vars->height
		&& i < (int)ft_strlen(vars->map[j]) && (vars->map[j][i] == 'D'
		|| vars->map[j][i] == 'd'))
	{
		if (vars->map[j][i] == 'D')
			ft_wall(vars, i - (floor(vars->x / TILE)
					- (MINIMAP_WIDTH / 2)), j - (floor(vars->y / TILE)
					- (MINIMAP_WIDTH / 2)), 0xFF0000);
		else
			ft_wall(vars, i - (floor(vars->x / TILE)
					- (MINIMAP_WIDTH / 2)), j - (floor(vars->y / TILE)
					- (MINIMAP_WIDTH / 2)), 0x00FF00);
	}
}

void	ft_map(t_data *vars)
{
	int	i;
	int	j;

	i = vars->x / TILE - (int)(MINIMAP_WIDTH / 2);
	j = vars->y / TILE - (int)(MINIMAP_WIDTH / 2);
	while (j < vars->height && j < (vars->y / TILE) + (MINIMAP_WIDTH / 2))
	{
		i = vars->x / TILE - (MINIMAP_WIDTH / 2);
		while (i < (vars->x / TILE) + (MINIMAP_WIDTH / 2) - 1)
		{
			ft_draw(vars, i, j);
			i++;
		}
		j++;
	}
	ft_wall(vars, MINIMAP_WIDTH / 2, MINIMAP_WIDTH / 2, 0xFFFF00);
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

void	ft_imgs(t_data *vars)
{
	vars->view += vars->view_speed;
	ft_add(vars);
	if (ft_check(vars, vars->up_down_x + vars->lr_x,
			vars->up_down_y + vars->lr_y) == 0)
	{
		vars->x += vars->up_down_x + vars->lr_x;
		vars->y += vars->up_down_y + vars->lr_y;
	}
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->img_map)
		mlx_destroy_image(vars->mlx, vars->img_map);
	vars->img_map = mlx_new_image(vars->mlx, MINIMAP_WIDTH
			* vars->map_tsize, MINIMAP_WIDTH * vars->map_tsize);
	vars->addr_map = mlx_get_data_addr(vars->img_map, &vars->bpp_map,
			&vars->size_lmap, &vars->endian_map);
	vars->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp, &vars->size_l,
			&vars->endian);
	ft_map(vars);
}

void	ft_3d_draw(t_data *vars)
{
	double	v;
	double	tmp;
	int		n;

	ft_imgs(vars);
	n = 0;
	tmp = vars->view + (POV / 2);
	v = vars->view;
	vars->view = v - (POV / 2);
	ft_color(vars);
	vars->px_x = 0;
	while (n < WINDOW_WIDTH)
	{
		vars->al = v - vars->view;
		ft_draw_ray(vars);
		vars->view += POV / WINDOW_WIDTH;
		n++;
	}
	vars->view = v;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

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
		if (vars->weapon_index == 1)
		{
			ft_delay_weapon(vars);
			if (vars->delay_weapon >= 30 && vars->delay_weapon < 36)
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->weapon_offic_5->img_weap, vars->weap_x,
					vars->weap_y);
			vars->delay_weapon++;
		}
		else
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->weapon_official->img_weap, vars->weap_x,
				vars->weap_y);
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

int	ft_player(t_data *vars)
{
	int		x;
	int		y;

	x = (WINDOW_WIDTH - vars->textures_start_screen->width) / 2;
	y = (WINDOW_HEIGHT - vars->textures_start_screen->width) / 2 + 280;
	if (!vars->start_screen)
	{
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->textures_start_screen->img, x, y);
		return (0);
	}
	ft_3d_draw(vars);
	ft_weapon_animation(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_map, 0, 0);
	return (0);
}

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

void	ft_mlx(t_data *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, ft_key, vars);
	mlx_hook(vars->win, 3, 1L << 1, ft_rel, vars);
	mlx_hook(vars->win, 17, 1L << 17, ft_close, vars);
	mlx_hook(vars->win, 4, 1L << 2, ft_mouse, vars);
	mlx_hook(vars->win, 5, 1L << 3, mouse_up, vars);
	mlx_hook(vars->win, 6, 1L << 6, ft_mouse_move, vars);
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
	vars.map_tsize = 10;
	if (!vars.mlx)
	{
		printf("Failed to init mlx\n");
		exit(1);
	}
	get_weapon(&vars);
	get_texture(&vars);
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!vars.win)
	{
		printf("Failed to create window\n");
		exit(1);
	}
	vars.y = floor(vars.y * TILE) + (TILE / 2);
	vars.x = floor(vars.x * TILE) + (TILE / 2);
	ft_mlx(&vars);
}
