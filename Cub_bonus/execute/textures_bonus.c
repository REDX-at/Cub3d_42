/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:12:49 by aitaouss          #+#    #+#             */
/*   Updated: 2024/09/20 18:14:57 by mkibous          ###   ########.fr       */
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
	free(data->texture_door);
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
