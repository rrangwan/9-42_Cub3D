/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:51 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

int	ft_path1(char *ret, int fd)
{
	if (fd != -1)
	{
		ft_putstr_fd("Error\ntexture path ", 2);
		ft_putstr_fd(ret, 2);
		ft_putstr_fd(" not a file\n", 2);
		ft_path2(ret, fd);
		return (1);
	}
	fd = open(ret, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\ntexture path ", 2);
		ft_putstr_fd(ret, 2);
		ft_putstr_fd(" not accessible\n", 2);
		ft_path2(ret, fd);
		return (1);
	}
	ft_path2(ret, fd);
	return (0);
}

void	ft_path2(char *ret, int fd)
{
	close (fd);
	free (ret);
	ret = NULL;
}

int	check_elems2(char *str, int *i, int *elem, int *ctn)
{
	if ((str[*i] == 'F' && str[*i + 1] && ft_isspace(str[*i + 1])) \
			|| (str[*i] == 'C' && str[*i + 1] && ft_isspace(str[*i + 1])))
	{
		if (str[*i] == 'F')
			elem[4]++;
		else if (str[*i] == 'C')
			elem[5]++;
		*i += 1;
		while (str[*i + 1] && ft_isspace(str[*i]) && str[*i] != '\n')
			*i += 1;
		if (str[*i])
			elem[7] += ft_rgb(str, *i);
		else
			elem[7] += 1;
		*ctn += 2;
		if (elem[7] > 0)
		{
			ft_putstr_fd("Error\nRGB color failure\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_rgb(char *str, int i)
{
	char	*ret;
	char	**temp2;

	ret = ft_rgb1(str, i);
	if (!ret)
		return (1);
	temp2 = ft_split(ret, ',');
	free (ret);
	if (ft_array_len(temp2) != 3)
	{
		free_2d_array(temp2);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if (!(ft_atoi2(temp2[i]) >= 0 && ft_atoi2(temp2[i]) <= 255))
		{
			free_2d_array(temp2);
			return (1);
		}
		i++;
	}
	free_2d_array(temp2);
	return (0);
}

char	*ft_rgb1(char *str, int i)
{
	char	*temp;
	char	*ret;
	int		j;

	temp = (char *)malloc(sizeof(char) * 4097);
	if (!temp)
		return (NULL);
	ft_memset(temp, '\0', 4097);
	j = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	ret = ft_strdup(temp);
	free (temp);
	return (ret);
}
