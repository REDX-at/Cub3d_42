/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:44:56 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 16:52:23 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
