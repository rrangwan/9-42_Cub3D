/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/08/01 19:24:51 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

int	check_elements2(char **data, int *elem, char **map_temp)
{
	if (ft_map_row(data[elem[8]]) == 0)
		return (1);
	else
	{
		elem[7] = 0;
		return (check_map(map_temp));
	}
}

//returns 1 if valid
int	ft_map_row(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str && str[i] && str[i] != '\n')
	{
		if ((str[i] != ' ' && str[i] != '1'))
			return (0);
		if (str[i] == '1')
			flag++;
		i++;
	}
	if (flag == 0)
		return (0);
	return (1);
}

//can delete i think
char	**ft_temp_map(char ***map_temp, char *str)
{
	char	**new_temp;
	int		rows;
	int		i;

	rows = ft_array_len(*map_temp);
	new_temp = (char **)malloc(sizeof(char *) * (rows + 2));
	new_temp[rows + 1] = 0;
	new_temp[rows + 2] = NULL;
	i = 0;
	while (*map_temp[i])
	{
		new_temp[i] = ft_strdup(*map_temp[i]);
		i++;
	}
	new_temp[i] = ft_strdup(str);
	new_temp[i + 1] = NULL;
	free_2d_array(*map_temp);
	map_temp = NULL;
	return (new_temp);
}

int	check_map(char **map)
{
	if (check_chars(map) || check_top(map) || check_bottom(map) \
	|| check_left(map) || check_right(map))
	{
		ft_putstr_fd("Error\nInvalid Map\n", 2);
		return (1);
	}		
	return (0);
}

int	check_chars(char **map)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	j = 0;
	while (j < ft_array_len(map))
	{
		i = 0;
		while (i < (int)ft_strlen(map[j]))
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' \
			|| map[j][i] == 'E')
				flag++;
			else if (map[j][i] != ' ' && map[j][i] != '1' && map[j][i] != '0' \
			&& map[j][i] != '\n')
				return (1);
			i++;
		}
		j++;
	}
	if (flag != 1)
		return (1);
	return (0);
}
