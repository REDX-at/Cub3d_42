/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:28:37 by aitaouss          #+#    #+#             */
/*   Updated: 2024/09/23 20:29:57 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*fill_skip(char *str, char *tmp, int i, int j)
{
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			tmp[j] = str[i];
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*skip_space(char *str, int flag)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	if (flag)
		i = 2;
	else
		i = 3;
	while (str[i])
	{
		if (str[i] != ' ')
			j++;
		i++;
	}
	if (flag)
		i = 1;
	else
		i = 2;
	tmp = malloc(sizeof(char) * j + 1);
	j = 0;
	tmp = fill_skip(str, tmp, i, j);
	return (tmp);
}

int	count_virgule(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	check_digit(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]) && str[i][j]
				!= '\n' && str[i][j] != '\t')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
