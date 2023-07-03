/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:02:00 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

//returns 1 if invalid
int	check_top(char **map)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	if (ft_map_row(map[0]) == 0)
		return (1);
	i = 0;
	j = 0;
	while (ft_isspace(map[j][i]) && map[j][i + 1] != '\n')
		i++;
	if (map[j][i] != '1')
		return (1);
	while (map[j][i + 1] != '\n' && flag < (int)ft_strlen(map[0]))
	{
		check_top1(map, &i, &j, &flag);
	}
	if (map[j][i + 1] != '\n')
		return (1);
	return (0);
}

void	check_top1(char **map, int *i, int *j, int *flag)
{
	while (map[*j][*i] == '1' && map[*j][*i + 1] && map[*j][*i + 1] == '1' \
	&& (*j == 0 || (*j > 0 && map[*j - 1][*i] != '1')))
		*i += 1;
	*flag += 1;
	while (map[*j][*i] && map[*j][*i] == '1'
	&& (*i < (int)ft_strlen(map[*j + 1])) && map[*j + 1][*i]
	&& map[*j + 1][*i] == '1' && map[*j][*i + 1] && map[*j][*i + 1] == ' ')
		*j += 1;
	*flag += 1;
	while (map[*j][*i] && map[*j][*i] == '1' && map[*j][*i + 1] && \
	map[*j][*i + 1] == '1' && (*j == 0 || (*j > 0 && map[*j - 1][*i + 1] \
	&& map[*j - 1][*i + 1] != '0')))
		*i += 1;
	*flag += 1;
	while (map[*j][*i] && map[*j][*i] == '1' && *j > 0 && *i > 0 && \
	map[*j - 1][*i - 1] && map[*j - 1][*i - 1] == ' ' && \
	map[*j - 1][*i] && map[*j - 1][*i] == '1')
		*j -= 1;
	*flag += 1;
}

int	check_bottom(char **map)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	j = check_last(map);
	i = 0;
	while (ft_isspace(map[j][i]) && map[j][i + 1] != '\n')
		i++;
	if (map[j][i] != '1')
		return (1);
	while (map[j][i + 1] != '\n' && flag < (int)ft_strlen(map[j]))
	{
		check_bottom1(map, &i, &j, &flag);
	}
	if (map[j][i + 1] == '\n' || (map[j][i + 1] == '\0'))
		return (0);
	return (1);
}

//return 1 if not valid bottom row
void	check_bottom1(char **map, int *i, int *j, int *flag)
{	
	while (map[*j][*i] && map[*j][*i] == '1' && map[*j][*i + 1] && \
	map[*j][*i + 1] == '1' && ((*j == check_last(map)) \
	|| ((*j < check_last(map)) && map[*j + 1][*i] && map[*j + 1][*i] != '1')))
		*i += 1;
	*flag += 1;
	while (map[*j][*i] && map[*j][*i] == '1'
	&& (*i < (int)ft_strlen(map[*j - 1])) && map[*j - 1][*i]
	&& map[*j - 1][*i] == '1' && map[*j][*i + 1] && map[*j][*i + 1] == ' ')
		*j -= 1;
	*flag += 1;
	while (map[*j][*i] && map[*j][*i] == '1' && map[*j][*i + 1] && \
	map[*j][*i + 1] == '1' && ((*j == check_last(map)) || ((*j < \
	check_last(map)) && map[*j + 1][*i + 1] && map[*j + 1][*i + 1] != '0')))
		*i += 1;
	*flag += 1;
	while (map[*j][*i] && map[*j][*i] == '1' && (*j < check_last(map)) \
	&& *i > 0 && map[*j + 1][*i] && map[*j + 1][*i] == '1' && \
	map[*j + 1][*i - 1] && map[*j + 1][*i - 1] == ' ')
		*j += 1;
}
