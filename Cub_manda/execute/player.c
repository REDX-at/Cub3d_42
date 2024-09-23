/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:17:38 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/21 11:20:40 by mkibous          ###   ########.fr       */
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
