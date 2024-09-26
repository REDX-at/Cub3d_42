/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:15:48 by aitaouss          #+#    #+#             */
/*   Updated: 2024/09/26 18:15:33 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	check_valid_map(char *tmp, t_alloc *alloc)
{
	int	i;
	int	j;
	int	store;

	j = 0;
	i = 0;
	free_2d(alloc->split);
	alloc->split = ft_split(tmp, '\n');
	fix_map(alloc);
	store = i;
	while (alloc->split[i])
	{
		j = 0;
		while (alloc->split[i][j] && store == i)
		{
			if (alloc->split[i][j] != '1' && alloc->split[i][j]
				!= ' ')
			{
				free(tmp);
				print_err_exit("Map not closed in first line", alloc);
			}
			j++;
		}
		i++;
	}
}

void	check_player(char *tmp, t_alloc *alloc)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tmp[i])
	{
		if (tmp[i] == 'W' || tmp[i] == 'E' || tmp[i] == 'S' || tmp[i] == 'N')
		{
			alloc->player = tmp[i];
			count++;
		}
		i++;
	}
	if (count == 0)
		print_err_exit("Map Invalid : Need one player", alloc);
	if (count > 1)
		print_err_exit("Map Invalid : One player only", alloc);
}

void	check_last_line(char *tmp, t_alloc *alloc)
{
	int	i;
	int	len;

	i = 0;
	free_2d(alloc->map);
	alloc->map = ft_split(tmp, '\n');
	len = ft_strlen_2d(alloc->map);
	while (alloc->map[len - 1][i])
	{
		if (alloc->map[len -1][i] != '1' && alloc->map[len -1][i]
			!= ' ')
		{
			free(tmp);
			print_err_exit("Map Invalid : Map not closed in last line", alloc);
		}
		i++;
	}
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
