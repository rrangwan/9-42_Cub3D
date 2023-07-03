/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:26 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

#if __linux__
//should return 0 if all good
int	ft_path(char *str, int i)
{
	char	*ret;
	int		j;
	int		len;
	int		fd;

	j = i;
	while (!ft_isspace(str[j]))
		j++;
	len = j - i;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (1);
	while (!ft_isspace(str[i]))
	{
		ret[j] = str[i];
		j++;
		i += 1;
	}
	ret[j] = '\0';
	fd = open(ret, __O_DIRECTORY | __O_PATH);
	if (ft_path1(ret, fd))
		return (1);
	return (0);
}
#endif

#if __APPLE__
//should return 0 if all good
int	ft_path(char *str, int i)
{
	char	*ret;
	int		j;
	int		len;
	int		fd;

	j = i;
	while (!ft_isspace(str[j]))
		j++;
	len = j - i;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (1);
	while (!ft_isspace(str[i]))
	{
		ret[j] = str[i];
		j++;
		i += 1;
	}
	ret[j] = '\0';
	fd = open(ret, O_DIRECTORY);
	if (ft_path1(ret, fd))
		return (1);
	return (0);
}
#endif

int	ft_array_len(char **array)
{
	int	ret;

	ret = 0;
	if (array)
	{
		while (array[ret] != NULL)
			ret++;
	}
	return (ret);
}

//returns -1 if error
int	ft_atoi2(const char *str)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (-1);
		num = (num * 10) + (str[i++] - 48);
	}
	if (num > INT32_MAX)
		return (-1);
	else
		return (num);
}

#if __linux__

void	check_map_validity(char *file)
{
	int		fd;

	fd = open(file, __O_DIRECTORY | __O_PATH);
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
