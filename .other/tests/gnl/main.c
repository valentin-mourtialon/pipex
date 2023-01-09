#include "gnl.h"

int	main(int ac, char **av)
{
	int     fd = open("../cases/cas_1a.txt", O_RDONLY);
	char    *line;
	
	if (ac == 1);
	{
		while ((line = get_next_line(fd)))
		{
			printf("%s", line);
			free(line);
		}
		free(line);
		if (fd >= 0)
			close(fd);
	}
	return (0);
}