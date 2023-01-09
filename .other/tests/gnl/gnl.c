#include "gnl.h"

char	*get_next_line(int fd)
{
	static char	*memory[FOPEN_MAX];
	char		*line;
	int			nbytes;
	char		*buffer;

	if (BUFFER_SIZE < 1 || fd < 0 || fd >= FOPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	nbytes = 1;
	while (!ft_strchr(memory[fd], '\n') && nbytes != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (free(buffer), NULL);
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes < 0)
			return (NULL);
		buffer[nbytes] = 0;
		memory[fd] = ft_strjoin(memory[fd], buffer);
		if (!(memory[fd]))
			return (NULL);
	}
	line = write_line_from_memory(memory[fd]);
	memory[fd] = clear_memory(memory[fd]);
	return (line);
}
