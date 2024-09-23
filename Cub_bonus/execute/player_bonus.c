/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:03:02 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 18:04:31 by mkibous          ###   ########.fr       */
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
