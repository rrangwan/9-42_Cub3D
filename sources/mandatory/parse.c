/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/08/01 19:24:04 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	check_map_extension(char *file)
{
	char	*ext;

	ext = ft_strrchr(file, '.');
	if (!ext)
	{
		ft_putstr_fd("Error\nInvalid Map, No Extension\n", 2);
		exit(1);
	}
	if (ft_strncmp(ext, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid Map Extension\n", 2);
		exit(1);
	}
	ext = ft_strchr(file, '.');
	if (ft_strlen(ext) != 4)
	{
		ft_putstr_fd("Error\nInvalid Map Extension\n", 2);
		exit(1);
	}
}

#if __APPLE__

void	check_map_validity(char *file)
{
	int		fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		ft_putstr_fd("Error\nArgument Not a file\n", 2);
		close(fd);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nMap file does not exist\n", 2);
		close(fd);
		exit (1);
	}
	close(fd);
}
#endif

void	check_elements0(char **data, int *elem, char **map_temp)
{
	if (data)
	{
		free_2d_array(data);
		data = NULL;
	}
	close(elem[6]);
	free (elem);
	elem = NULL;
	if (map_temp)
	{
		free_2d_array(map_temp);
		map_temp = NULL;
	}
}

int	check_last2(int *j, char **map)
{
	int	len;
	int	i;

	len = 0;
	while (*j > 0)
	{
		i = 0;
		if (map[*j][i] && ft_isspace(map[*j][i]) && map[*j][i] != '\n')
			i++;
		if ((!map[*j][i + 1] || map[*j][i] == '\n') || (map[*j][i] && \
		(check_elems0(map[*j], &i) || ((map[*j][i] == 'F' || map[*j][i] == 'C') \
		&& map[*j][i + 1] && ft_isspace(map[*j][i + 1])))))
			break ;
		else
		{
			*j -= 1;
			len++;
		}
	}
	if (*j <= 0)
		return (0);
	if (!ft_map_row(map[*j + 1]))
		return (0);
	return (len);
}

int	check_last(char **map)
{
	int	j;
	int	i;

	i = 0;
	j = ft_array_len(map) - 1;
	while (j > 0)
	{
		while (ft_isspace(map[j][i]) && map[j][i] != '\n')
			i++;
		if (map[j][i] == '\n')
			j--;
		else
			break ;
	}
	return (j);
}
