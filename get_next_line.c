/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manorteg <manorteg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:26:28 by manorteg          #+#    #+#             */
/*   Updated: 2024/10/06 12:45:50 by manorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_line_from_fd(int fd, t_buffer *buffers, char *line)
{
	int				line_pos;
	char			c;

	while (line_pos < MAX_LINE_LENGTH - 1) //hasta que no acabe el archivo
	{
		if (buffers[fd].position >= buffers[fd].bytes_read) //si ya se leyó todo el buffer
		{
			buffers[fd].position = 0;
			buffers[fd].bytes_read = read(fd, buffers[fd].content, BUFFER_SIZE);
			if (buffers[fd].bytes_read == 0) // fin de archivo
				break ;
			else if (buffers[fd].bytes_read < 0) // lectura fallida
				return (-1);
		}
		c = buffers[fd].content[buffers[fd].position++];
		line[line_pos++] = c;
		if (c == '\n')
			break ;
	}
	return (line_pos);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffers[MAX_FD];
	char			*line;
	char			*next_line;
	int				line_pos;

	line_pos = 0;
	line = ft_calloc(MAX_LINE_LENGTH, sizeof(char));
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || !line)
		return (free(line), NULL);
	line_pos = read_line_from_fd(fd, buffers, line);
	if (line_pos <= 0)
		return (free(line), NULL);
	next_line = ft_strdup(line);
	free(line);
	return (next_line);
}

// int main (void)
// {
// 	int fd = open("/home/manorteg/francinette/tests/get_next_line/fsoares/giant_line.txt", O_RDONLY);
// 	char *line;

// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }