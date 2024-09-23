/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:08:09 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/21 11:24:52 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
