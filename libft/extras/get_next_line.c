/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:05:53 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/07 01:58:06 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	ft_free(char **sbuf, char *set)
{
	free (*sbuf);
	*sbuf = set;
}

static char	*extract_one_line(char **sbuf)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (sbuf[0][i] != 0 && sbuf[0][i] != 10)
		i++;
	if (!sbuf[0][i])
	{
		line = ft_strdup(&sbuf[0][0]);
		ft_free(sbuf, NULL);
	}
	else
	{
		line = ft_substr(&sbuf[0][0], 0, i + 1);
		temp = ft_strdup(&sbuf[0][i + 1]);
		ft_free(sbuf, temp);
		if (!sbuf[0][0])
			ft_free(sbuf, NULL);
	}
	return (line);
}

static void	process_file(int fd, char **sbuf, char *buffer, ssize_t nbytes)
{
	char	*temp;

	while (nbytes > 0)
	{
		buffer[nbytes] = 0;
		if (!sbuf[0])
			sbuf[0] = ft_strdup("");
		temp = ft_strjoin(sbuf[0], buffer);
		ft_free(&sbuf[0], temp);
		if (ft_strchr(sbuf[0], 10))
			break ;
		nbytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
}

static char	*check_sbuf(char **sbuf, ssize_t n)
{
	if (!sbuf[0] && n <= 0)
		return (NULL);
	else
		return (extract_one_line(sbuf));
}

char	*get_next_line(int fd)
{
	static char	*sbuf;
	char		*buffer;
	ssize_t		nbytes;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	nbytes = read(fd, buffer, BUFFER_SIZE);
	process_file(fd, &sbuf, buffer, nbytes);
	return (check_sbuf(&sbuf, nbytes));
}
