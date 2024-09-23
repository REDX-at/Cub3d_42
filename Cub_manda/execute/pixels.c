/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:23:34 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/21 11:24:43 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_pixel_put(t_data *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->size_l + x * (vars->bpp / 8));
	*(unsigned int *)dst = color;
}
