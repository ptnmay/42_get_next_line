/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaeyang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:55:25 by psaeyang          #+#    #+#             */
/*   Updated: 2022/10/29 15:21:40 by psaeyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*keep_this_line(char *keep, int rslen)
{
	char	*tmp;

	if (!keep[rslen])
	{
		free (keep);
		return (NULL);
	}	
	tmp = malloc(1);
	if (!tmp)
	{
		free (tmp);
		return (NULL);
	}
	tmp[0] = '\0';
	if (keep[rslen - 1] == '\n')
	{
		if (keep[rslen] == '\0')
		{
			free (keep);
			return (NULL);
		}
		else
			tmp = ft_strjoin(tmp, &keep[rslen]);
	}
	free (keep);
	return (tmp);
}

char	*get_this_line(char *keep)
{
	char	*kept;
	int		i;

	i = 0;
	if (keep == NULL)
		return (NULL);
	kept = malloc(sizeof(char) + (ft_strlen_n(keep, '\n') + 1));
	if (!kept)
		return (NULL);
	while (keep[i] != '\n' && keep[i] != '\0')
	{
		kept[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		kept[i] = keep[i];
		i++;
	}
	kept[i] = '\0';
	return (kept);
}

char	*readfile(int fd, char *keep)
{
	char	*buf;
	int		nb;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	nb = 1;
	while (nb > 0)
	{

		nb = read(fd, buf, BUFFER_SIZE);
//		printf("%d hello gl\n", nb);
		if (nb < 0)
		{
			free (buf);
			return (NULL);
		}
		buf[nb] = '\0';
	//	printf("buf = %s", buf);
	//	printf("----------------------------\n");
		keep = ft_strjoin(keep, buf);
	//	printf("keep = %s", keep);
	//	printf("----------------------------\n");
		if (ft_find_n(buf))
		{
		//	printf("=======");
			break ;
		}
	}
	free (buf);
	return (keep);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	char		*rsline;
	size_t		rslen;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!keep)
	{
		keep = malloc(1);
		keep[0] = '\0';
	}
	keep = readfile(fd, keep);
//	printf("ad keep =%p %d\n", keep, *keep);
	if (!keep[0])
	{
		//printf("Mello\n");
		free (keep);
		return (NULL);
	}
	rsline = get_this_line(keep);
	rslen = ft_strlen_n(rsline, '\n') + 1;
//	printf("rslen = %zu\n", rslen);
//	printf("----------------------------\n");
	keep = keep_this_line(keep, rslen);
//	printf("keep line = %s", keep);
	return (rsline);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("/Users/psaeyang/get_next_line/1test/files/nl", O_RDONLY);
	printf("fd :%d\n", fd);
	line = get_next_line(fd);
	printf("line1 =  %s\n", line);
	free(line);
	printf("Hello\n");
	line = get_next_line(fd);
	printf("line2 =  %s\n", line);
	free(line);
	close(fd);
}*/
