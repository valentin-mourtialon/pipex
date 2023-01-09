#include "gnl.h"

char	*write_line_from_memory(char *memory)
{
	char	*line;
	int		i;

	i = 0;
	if (!memory[i])
		return (NULL);
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

char	*clear_memory(char *memory)
{
	char	*cleared_memory;
	int		i;
	int		j;

	i = 0;
	while (memory[i] && memory[i] != '\n')
		i++;
	if (!memory[i])
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

size_t	ft_strlen(char *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	if (c > 256)
		c %= 256;
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

char	*ft_strjoin(char *memory, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!memory)
	{
		memory = malloc(sizeof(char));
		memory[0] = '\0';
	}
	if (!memory || !buffer)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(memory) + ft_strlen(buffer) + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (memory[++i] != '\0')
		join[i] = memory[i];
	j = 0;
	while (buffer[j] != '\0')
		join[i++] = buffer[j++];
	join[ft_strlen(memory) + ft_strlen(buffer)] = '\0';
	free(memory);
	free(buffer);
	return (join);
}
