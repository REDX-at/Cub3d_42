/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:12:49 by aitaouss          #+#    #+#             */
/*   Updated: 2024/09/17 16:35:45 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_and_exit(char *message)
{
	printf("%s\n", message);
	exit(1);
}

t_textures	*init_textures(t_data *data)
{
	t_textures	*textures;

	data->texture_north = data->alloc->no_path;
	data->texture_south = data->alloc->so_path;
	data->texture_west = data->alloc->we_path;
	data->texture_east = data->alloc->ea_path;
	textures = malloc(sizeof(t_textures));
	if (!textures)
		print_and_exit("Failed to allocate memory for textures");
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
		print_and_exit("Failed to open texture file");
	close(fd);
	textures->img = mlx_xpm_file_to_image(data->mlx, path,
			&textures->width, &textures->height);
	if (!textures->img)
		print_and_exit("Failed to load texture image");
	textures->addr = mlx_get_data_addr(textures->img, &textures->bits_per_pixel,
			&textures->line_lenght, &textures->endian);
	if (!textures->addr)
		print_and_exit("Failed to get texture address");
}

void	get_texture(t_data *data)
{
	data->textures_north_struct = init_textures(data);
	load_textures(data, data->texture_north, data->textures_north_struct);
	data->textures_south_struct = init_textures(data);
	load_textures(data, data->texture_south, data->textures_south_struct);
	data->textures_west_struct = init_textures(data);
	load_textures(data, data->texture_west, data->textures_west_struct);
	data->textures_east_struct = init_textures(data);
	load_textures(data, data->texture_east, data->textures_east_struct);
}
