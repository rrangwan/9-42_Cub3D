/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:00:39 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init(char **data, char **map, t_program *prog)
{
	int	i;
	int	j;

	j = 0;
	while (data && !ft_map_row(data[j]))
	{
		i = 0;
		while (data && data[j] && data[j][i] && ft_isspace(data[j][i]))
			i++;
		if (data[j][i] == 'N' || data[j][i] == 'S' || data[j][i] == 'E' \
		|| data[j][i] == 'W' || data[j][i] == 'F' || data[j][i] == 'C')
			init0(&i, data[j], prog);
		j++;
	}
	prog->mlx.map = map;
	init_mlx(prog);
	init_images(prog);
	init_player(prog);
}

void	init0(int *i, char *str, t_program *prog)
{
	if (str[*i] == 'N')
		init_n(i, str, prog);
	else if (str[*i] == 'S')
		init_s(i, str, prog);
	else if (str[*i] == 'E')
		init_e(i, str, prog);
	else if (str[*i] == 'W')
		init_w(i, str, prog);
	else if (str[*i] == 'F')
		init_f(i, str, prog);
	else if (str[*i] == 'C')
		init_c(i, str, prog);
}

void	init_n(int *i, char *str, t_program *prog)
{
	*i += 2;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.north = init_path(str, i);
}

void	init_s(int *i, char *str, t_program *prog)
{
	*i += 2;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.south = init_path(str, i);
}

void	init_e(int *i, char *str, t_program *prog)
{
	*i += 2;
	while (str[*i + 1] && ft_isspace(str[*i]))
		*i += 1;
	prog->tex.east = init_path(str, i);
}
