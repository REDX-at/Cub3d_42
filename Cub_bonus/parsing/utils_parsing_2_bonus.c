/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:55:11 by aitaouss          #+#    #+#             */
/*   Updated: 2024/09/23 19:37:37 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	print_err_exit(char *str, t_alloc *alloc)
{
	(void)alloc;
	printf(RED"Error\n"W"%s\n", str);
	out_clean(alloc);
	exit(1);
}

void	print_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("|%s|\n", str[i]);
		i++;
	}
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	**convert_tabs_space(char **str)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	j = 0;
	i = ft_strlen_2d(str);
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (str[++i])
	{
		tmp[j] = malloc(sizeof(char) * ft_strlen(str[i]) + 1);
		k = -1;
		while (str[i][++k])
		{
			tmp[j][k] = str[i][k];
		}
		tmp[j][k] = '\0';
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}

void	check_space_and_open(char *str, char *element)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free(str);
		printf(RED"Error\n"W"Error in opening %s file\n", element);
		exit(1);
	}
	close(fd);
}
