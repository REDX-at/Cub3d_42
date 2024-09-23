/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:14:31 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/20 18:15:02 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	load_textures(t_data *data, char *path, t_textures *textures)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_and_exit("Failed to open texture file\n");
	close(fd);
	textures->img = mlx_xpm_file_to_image(data->mlx, path, &textures->width,
			&textures->height);
	if (!textures->img)
		print_and_exit("Failed to load texture\n");
	textures->addr = mlx_get_data_addr(textures->img, &textures->bits_per_pixel,
			&textures->line_lenght, &textures->endian);
	if (!textures->addr)
		print_and_exit("Failed to get texture address\n");
}

void	get_texture(t_data *data)
{
	data->textures_door_struct = init_textures(data);
	load_textures(data, data->texture_door, data->textures_door_struct);
	data->textures_north_struct = init_textures(data);
	load_textures(data, data->texture_north, data->textures_north_struct);
	data->textures_south_struct = init_textures(data);
	load_textures(data, data->texture_south, data->textures_south_struct);
	data->textures_west_struct = init_textures(data);
	load_textures(data, data->texture_west, data->textures_west_struct);
	data->textures_east_struct = init_textures(data);
	load_textures(data, data->texture_east, data->textures_east_struct);
	data->textures_black_screen = init_textures(data);
	load_textures(data, "textures_bonus/black_screen.xpm",
		data->textures_black_screen);
	data->textures_start_screen = init_textures(data);
	load_textures(data, "textures_bonus/start_screen.xpm",
		data->textures_start_screen);
}

void	ft_find_texture(t_data *vars, t_textures **texture)
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
