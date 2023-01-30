/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:09:23 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/30 15:37:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

/*
	Why i + 2 ?

	Example: memory = "get\n next line\0"

	After the first while-loop, we'll have:
	i = 3

	This number (i=3) means that we need to
	alloc 3 chars which are, in our example,
	"get".

	However, the subject mentions that our
	line should end with a "\n" (newline)
	if the end of the file isn't encountered.
	In this way, we know that we have to 
	alloc i + 1 for the moment...

	Because we still have to save a byte for
	our "end of string" character: "\0".

	Conclusion: i + 1 + 1.

	Note: it also works with the following
	example: "get next line\0" where the "\0"
	is encountered before the "\n" that is 
	never met.
*/
static char	*write_line_from_memory(char *memory)
{
	char	*line;
	int		i;

	i = 0;
	if (memory && !memory[i])
		return (free(memory), NULL);
	while (memory[i] && memory[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (memory[i] && memory[i] != '\n')
	{
		line[i] = memory[i];
		i++;
	}
	if (memory[i] == '\n')
	{
		line[i] = memory[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*clear_memory(char *memory)
{
	char	*cleared_memory;
	int		i;
	int		j;

	i = 0;
	while (memory[i] && memory[i] != '\n')
		i++;
	if (memory && !memory[i])
		return (free(memory), NULL);
	cleared_memory = malloc(sizeof(char) * (ft_strlen(memory) - i + 1));
	if (!cleared_memory)
		return (NULL);
	j = 0;
	while (memory[i])
		cleared_memory[j++] = memory[++i];
	cleared_memory[j] = '\0';
	free(memory);
	return (cleared_memory);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;
	int			nbytes;
	char		*buffer;

	if (BUFFER_SIZE < 1 || fd < 0 || fd >= FOPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	nbytes = 1;
	while (!ft_strchr(memory, '\n') && nbytes != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes < 0)
			return (free(buffer), NULL);
		buffer[nbytes] = 0;
		memory = ft_strjoin(memory, buffer);
		if (!memory)
			return (free(buffer), NULL);
	}
	line = write_line_from_memory(memory);
	memory = clear_memory(memory);
	return (line);
}
