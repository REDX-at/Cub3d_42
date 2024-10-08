/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:28:37 by aitaouss          #+#    #+#             */
/*   Updated: 2024/10/07 11:32:53 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

char	*while_skip_space(char *str, char *tmp, int i, int j)
{
	tmp = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t')
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

	j = 3;
	if (flag)
		i = 2;
	else
		i = 3;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			j++;
		i++;
	}
	if (flag)
		i = 1;
	else
		i = 2;
	tmp = NULL;
	tmp = while_skip_space(str, tmp, i, j);
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
			if (!ft_isdigit(str[i][j]) && str[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
