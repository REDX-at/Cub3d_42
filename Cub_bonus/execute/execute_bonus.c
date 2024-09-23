/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:08:09 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 18:13:07 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
