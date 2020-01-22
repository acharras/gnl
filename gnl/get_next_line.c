/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: acharras <acharras@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 16:31:51 by acharras     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 15:42:27 by acharras    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int			i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_read(char *str, char *tmp, int fd, int ret)
{
	char		*buff;

	if ((ret = read(fd, NULL, 0)) < 0)
	{
		free(str);
		return (NULL);
	}
	if (!(buff = malloc(sizeof(buff) * (BUFFER_SIZE + 1))))
		return (NULL);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (ft_strchr(buff, '\n'))
		{
			if (!(tmp = ft_strjoin(str, buff)))
				return (NULL);
			str = tmp;
			free(buff);
			return (str);
		}
		if (!(str = ft_strjoin(str, buff)))
			return (NULL);
	}
	free(buff);
	return (str);
}

int			ft_fill_line(char *str, int i, char **line, char *tmp)
{
	if (i != 0)
	{
		if (!((*line) = ft_substr(str, 0, i)))
			return (-1);
		if (!(tmp = ft_strdup(str + i + 1)))
		{
			free(tmp);
			return (-1);
		}
		str = ft_strcpy(str, tmp);
		free(tmp);
	}
	else
	{
		if (!((*line) = ft_strdup("")))
			return (-1);
		if (!(tmp = ft_strdup(str + 1)))
		{
			free(tmp);
			return (-1);
		}
		str = ft_strcpy(str, tmp);
		free(tmp);
	}
	return (0);
}

int			ft_fill(char *str, int i, char **line, char *tmp)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	if (str[i] != '\0')
	{
		i = 0;
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		ft_fill_line(str, i, line, tmp);
		return (1);
	}
	else
	{
		if (!((*line) = ft_substr(str, 0, i)))
			return (-1);
		free(str);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char *str = NULL;
	char		*tmp;
	int			i;
	int			res;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
	{
		if (str)
			free(str);
		return (-1);
	}
	if (str == NULL)
		if (!((str) = ft_strdup("")))
			return (-1);
	tmp = NULL;
	str = ft_read(str, tmp, fd, 0);
	if (str == NULL)
		return (-1);
	i = 0;
	tmp = NULL;
	res = ft_fill(str, i, line, tmp);
	return (res);
}
