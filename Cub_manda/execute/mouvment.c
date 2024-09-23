/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:06:17 by mkibous           #+#    #+#             */
/*   Updated: 2024/09/21 11:08:37 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_w(t_data *vars)
{
	vars->up_down_x = ((cos(vars->view)) * TILE / 25);
	vars->up_down_y = ((sin(vars->view)) * TILE / 25);
}

void	ft_s(t_data *vars)
{
	vars->up_down_x = cos((vars->view + M_PI)) * TILE / 25;
	vars->up_down_y = sin(vars->view + M_PI) * TILE / 25;
}

void	ft_d(t_data *vars)
{
	vars->lr_x = cos((vars->view + (M_PI / 2))) * TILE / 25;
	vars->lr_y = sin((vars->view + (M_PI / 2))) * TILE / 25;
}

void	ft_a(t_data *vars)
{
	vars->lr_x = cos((vars->view - (M_PI / 2))) * TILE / 25;
	vars->lr_y = sin((vars->view - (M_PI / 2))) * TILE / 25;
}

void	ft_add(t_data *vars)
{
	if (vars->w)
		ft_w(vars);
	if (vars->s)
		ft_s(vars);
	if (vars->a)
		ft_a(vars);
	if (vars->d)
		ft_d(vars);
	if ((vars->w && vars->s))
	{
		vars->up_down_x = 0;
		vars->up_down_y = 0;
	}
	if ((vars->a && vars->d))
	{
		vars->lr_x = 0;
		vars->lr_y = 0;
	}
}
