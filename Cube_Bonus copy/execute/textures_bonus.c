/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:12:49 by aitaouss          #+#    #+#             */
/*   Updated: 2024/08/24 17:37:59 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_textures	*init_textures(t_data *data)
{
	data->texture_north = data->alloc->no_path;
	data->texture_south = data->alloc->so_path;
	data->texture_west = data->alloc->we_path;
	data->texture_east = data->alloc->ea_path;
	t_textures *textures;
	
	textures = malloc(sizeof(t_textures));
	if (!textures)
	{
		printf("Failed to allocate memory for textures\n");
		exit(1);
	}
	textures->img = NULL;
	textures->addr = NULL;
	textures->width = 0;
	textures->height = 0;
	textures->bits_per_pixel = 0;
	textures->line_lenght = 0;
	textures->endian = 0;
	return (textures);
}

void	load_textures(t_data *data, char *path, t_textures *textures)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open texture file\n");
		exit(1);
	}
	close(fd);
	textures->img = mlx_xpm_file_to_image(data->mlx, path, &textures->width, &textures->height);
	if (!textures->img)
	{
		printf("Failed to load texture\n");
		exit(1);
	}
	textures->addr = mlx_get_data_addr(textures->img, &textures->bits_per_pixel, &textures->line_lenght, &textures->endian);
	if (!textures->addr)
	{
		printf("Failed to get texture address\n");
		exit(1);
	}
}

void    get_texture(t_data *data)
{
    printf("alloc no path %s\n", data->alloc->no_path);
    exit(1);
	data->textures_north_struct = init_textures(data);
	load_textures(data, data->texture_north, data->textures_north_struct);
	data->textures_south_struct = init_textures(data);
	load_textures(data, data->texture_south, data->textures_south_struct);
	data->textures_west_struct = init_textures(data);
	load_textures(data, data->texture_west, data->textures_west_struct);
	data->textures_east_struct = init_textures(data);
	load_textures(data, data->texture_east, data->textures_east_struct);
}
