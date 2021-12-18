/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:22:42 by aelaoufi          #+#    #+#             */
/*   Updated: 2021/12/18 14:50:38 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

int	ft_checkend(char **str, char **line)
{
	if ((ft_strlen(*line) == 0 && ft_strlen(*str) == 0))
	{
		if (*str)
		{
			free(*str);
			*str = NULL;
		}
		free(*line);
		*line = NULL;
		return (0);
	}
	return (1);
}

int	ft_checknline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_assign(char **str, t_line *stru, int fd, int flag)
{
	if (flag == 0)
	{
		free(stru->buf);
		stru->buf = NULL;
		stru->reader = ft_strlen(ft_strchr(str[fd], '\n'));
		stru->line = ft_substr(str[fd], 0,
				ft_strlen(str[fd]) - stru->reader + 1);
		stru->temp = ft_substr(str[fd],
				ft_strlen(stru->line), ft_strlen(str[fd]));
		free(str[fd]);
		str[fd] = stru->temp;
	}
	if (flag == 1)
	{
		stru->buf[stru->reader] = '\0';
		str[fd] = ft_strjoin(str[fd], stru->buf);
	}
	if (flag == 2)
	{
		stru->reader = 1;
		stru->buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!(stru->buf))
			return ;
	}
}

char	*get_next_line_bonus(int fd, char **str)
{
	t_line	stru;

	ft_assign(str, &stru, fd, 2);
	if (!(str[fd]))
		str[fd] = ft_strdup ("");
	while (stru.reader > 0 && !ft_checknline(str[fd]))
	{
		stru.reader = read(fd, stru.buf, BUFFER_SIZE);
		if (stru.reader < 0)
		{
			if (str[fd])
			{
				free(str[fd]);
				str[fd] = NULL;
			}
			free(stru.buf);
			stru.buf = NULL;
			return (NULL);
		}
		ft_assign(str, &stru, fd, 1);
	}
	ft_assign(str, &stru, fd, 0);
	if (!ft_checkend(&(str[fd]), &(stru.line)))
		return (NULL);
	return (stru.line);
}

char	*get_next_line(int fd)
{
	static char	*result[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	return (get_next_line_bonus(fd, &(result[fd])));
}
