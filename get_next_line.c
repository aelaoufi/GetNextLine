/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:44:39 by aelaoufi          #+#    #+#             */
/*   Updated: 2021/12/18 14:50:53 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

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

void	ft_assign(char **str, t_line *line)
{
	free(line->buf);
	line->buf = NULL;
	line->reader = ft_strlen(ft_strchr(*str, '\n'));
	line->line = ft_substr(*str, 0, ft_strlen(*str) - line->reader + 1);
	line->temp = ft_substr(*str, ft_strlen(line->line), ft_strlen(*str));
	free(*str);
	*str = line->temp;
}

void	ft_assign2(char **str, t_line *line)
{
	line->reader = 1;
	line->buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!(line->buf))
		return ;
	if (!(*str))
		*str = ft_strdup ("");
}

char	*get_next_line(int fd)
{
	static char	*str;
	t_line		line;

	ft_assign2(&str, &line);
	while (line.reader > 0 && !ft_checknline(str))
	{
		line.reader = read(fd, line.buf, BUFFER_SIZE);
		if (line.reader < 0)
		{
			if (str)
			{
				free(str);
				str = NULL;
			}
			free(line.buf);
			line.buf = NULL;
			return (NULL);
		}
		line.buf[line.reader] = '\0';
		str = ft_strjoin(str, line.buf);
	}
	ft_assign(&str, &line);
	if (!ft_checkend(&str, &line.line))
		return (NULL);
	return (line.line);
}
