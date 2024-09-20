/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:12:49 by aitaouss          #+#    #+#             */
/*   Updated: 2024/09/19 16:19:38 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	print_and_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

t_weapon	*init_weapon(t_data *data)
{
	t_weapon	*weapon;

	weapon = malloc(sizeof(t_weapon));
	(void)data;
	if (!weapon)
		print_and_exit("Failed to allocate memory for weapon\n");
	weapon->img_weap = NULL;
	weapon->img_weap_width = 0;
	weapon->img_weap_height = 0;
	return (weapon);
}

void	load_weapon(t_data *data, t_weapon *weapon, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_and_exit("Failed to open weapon texture file\n");
	close(fd);
	weapon->img_weap = mlx_xpm_file_to_image(data->mlx, path,
			&weapon->img_weap_width, &weapon->img_weap_height);
	if (!weapon->img_weap)
		print_and_exit("Failed to load weapon texture\n");
}

void	get_weapon(t_data *data)
{
	data->weapon_official = init_weapon(data);
	load_weapon(data, data->weapon_official,
		"textures_bonus/weapon_texture/weapon.xpm");
	data->weapon_zoom = init_weapon(data);
	load_weapon(data, data->weapon_zoom,
		"textures_bonus/weapon_texture/weapon_down.xpm");
	data->weapon_shoot = init_weapon(data);
	load_weapon(data, data->weapon_shoot,
		"textures_bonus/weapon_texture/weapon_red.xpm");
	data->weapon_offic_1 = init_weapon(data);
	load_weapon(data, data->weapon_offic_1,
		"textures_bonus/weapon_texture/weapon_frame_1.xpm");
	data->weapon_offic_2 = init_weapon(data);
	load_weapon(data, data->weapon_offic_2,
		"textures_bonus/weapon_texture/weapon_frame_2.xpm");
	data->weapon_offic_3 = init_weapon(data);
	load_weapon(data, data->weapon_offic_3,
		"textures_bonus/weapon_texture/weapon_frame_3.xpm");
	data->weapon_offic_4 = init_weapon(data);
	load_weapon(data, data->weapon_offic_4,
		"textures_bonus/weapon_texture/weapon_frame_4.xpm");
	data->weapon_offic_5 = init_weapon(data);
	load_weapon(data, data->weapon_offic_5,
		"textures_bonus/weapon_texture/weapon_frame_5.xpm");
}

t_textures	*init_textures(t_data *data)
{
	t_textures	*textures;

	data->texture_north = data->alloc->no_path;
	data->texture_south = data->alloc->so_path;
	data->texture_west = data->alloc->we_path;
	data->texture_east = data->alloc->ea_path;
	data->texture_door = ft_strdup("textures_bonus/door.xpm");
	textures = malloc(sizeof(t_textures));
	if (!textures)
		print_and_exit("Failed to allocate memory for textures\n");
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
