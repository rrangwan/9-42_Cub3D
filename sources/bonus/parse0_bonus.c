/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:41 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

char	**check_elements007(char **temp)
{
	int		i;
	int		j;
	int		len;
	char	**ret;

	i = 0;
	j = check_last(temp);
	len = check_last2(&j, temp);
	if (len == 0)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (NULL);
	j++;
	while (i < len)
	{
		ret[i] = NULL;
		ret[i] = ft_strdup(temp[j]);
		i++;
		j++;
	}
	ret[i] = ft_strdup("\n");
	ret[i + 1] = NULL;
	return (ret);
}

char	**check_elements000(char **temp)
{
	int		i;
	int		len;
	char	**ret;

	len = 0;
	i = 0;
	while (temp[len])
		len++;
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = NULL;
		ret[i] = ft_strdup(temp[i]);
		i++;
	}
	ret[i] = NULL;
	free_2d_array(temp);
	return (ret);
}

char	**check_elements00(char *file, int *elem)
{
	char	*str;
	char	**temp;
	int		i;

	elem[6] = open(file, O_RDONLY);
	temp = (char **)malloc(sizeof(char *) * (4096));
	str = get_next_line(elem[6]);
	i = 0;
	while (str)
	{
		temp[i] = ft_strdup(str);
		free (str);
		str = get_next_line(elem[6]);
		i++;
	}
	free (str);
	str = NULL;
	temp[i] = NULL;
	return (check_elements000(temp));
}

int	check_elements(char *file, t_program *prog)
{
	int		*elem;
	char	**data;
	char	**map_temp;

	elem = (int *)ft_calloc(9, sizeof(int));
	data = check_elements00(file, elem);
	map_temp = check_elements007(data);
	if (!data || !map_temp)
	{
		check_elements0(data, elem, map_temp);
		return (1);
	}
	if (check_elements1(data, elem, map_temp))
	{
		check_elements0(data, elem, map_temp);
		return (1);
	}
	if (ft_elem(elem, 6))
	{
		check_elements0(data, elem, map_temp);
		return (1);
	}
	return (check_elements0b(map_temp, prog, data, elem));
}

int	ft_elem(int *elem, int len)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < len)
	{
		if (elem[i] != 1)
			flag = 1;
		i++;
	}
	return (flag);
}
