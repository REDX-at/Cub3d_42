/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:11:50 by aitaouss          #+#    #+#             */
/*   Updated: 2024/08/27 14:30:14 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_imposter(t_alloc *alloc, int i, int j, int flag)
{
	if (alloc->map[0] == NULL)
		print_err_exit("Map Invalid : Map empty", alloc);
	while (alloc->map[++i])
	{
		j = 0;
		while (alloc->map[i][j] != '\0' && alloc->map[i][j] == '\n' && flag)
		{
			i++;
			if (alloc->map[i] == NULL)
				print_err_exit("Map Invalid : Map With just new line", alloc);
		}
		flag = 0;
		if (alloc->map[i][j] == '\n')
			print_err_exit("Map Invalid : New line detected", alloc);
		while (alloc->map[i][j])
		{
			if (alloc->map[i][j] != '1' && alloc->map[i][j] != '0'
				&& alloc->map[i][j] != ' '
				&& alloc->map[i][j] != 'S' && alloc->map[i][j] != 'N'
				&& alloc->map[i][j] != 'W'
				&& alloc->map[i][j] != 'E' && alloc->map[i][j] != '\n'
				&& alloc->map[i][j] != 'D' && alloc->map[i][j] != '\t')
				print_err_exit("Map Invalid : Unknown symbol", alloc);
			j++;
		}
	}
}

char	*ft_strnew(size_t size, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	fix_map(t_alloc *alloc)
{
	size_t	longest_line;
	int	i;
	char	*tmp;

	i = 0;
	longest_line = 0;
	while (alloc->split[i])
	{
		if (ft_strlen(alloc->split[i]) > longest_line)
			longest_line = ft_strlen(alloc->split[i]);
		i++;
	}
	i = 0;
	while (alloc->split[i])
	{
		if (ft_strlen(alloc->split[i]) < longest_line)
		{
			tmp = ft_strnew(longest_line - ft_strlen(alloc->split[i]), ' ');
			free(alloc->split[i]);
			alloc->split[i] = ft_strjoin(alloc->split[i], tmp);
			free(tmp);
		}
		i++;
	}	
}

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
			if (alloc->split[i][j] != '1' && alloc->split[i][j] != ' ' && alloc->split[i][j] != '\t')
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
		if (alloc->map[len -1][i] != '1' && alloc->map[len -1][i] != ' ' && alloc->map[len -1][i] != '\t')
		{
			free(tmp);
			print_err_exit("Map Invalid : Map not closed in last line", alloc);
		}
		i++;
	}
}

void checkmap(char **map, char cara){
	int index = 0;
	int incre = 0;
	while (map[index]){
		while (map[index][incre])
			{
				if (map[index][incre] == cara)
					{
						printf("Invalid Value \n");
						exit(1);
					}
				incre++;
			}
			incre = 0;
			index++ ;
	}
}
void	check_map(t_alloc *alloc)
{
	int		i;
	char	*tmp ;
	char	*tmp_2;

	tmp_2 = ft_strdup("");
	if (!tmp_2)
		print_err_exit("Malloc failed", alloc);
	tmp = ft_strdup("");
	if (!tmp)
		print_err_exit("Malloc failed", alloc);
	i = -1;
	check_imposter(alloc, -1, 0, 1);
	join_double_pointer(alloc, &tmp, &tmp_2);
	check_valid_map(tmp, alloc);
	alloc->map = ft_strdup_2d(alloc->split);
	print_2d(alloc->map);
	check_player(tmp, alloc);
	check_last_line(tmp, alloc);
	free(tmp);
	check_arround(alloc);
}
