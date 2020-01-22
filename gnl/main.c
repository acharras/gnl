#include "get_next_line.h"
#include <stdio.h>

int     main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 0;
	(void)ac;
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line) > 0))
	{
		printf("ret %d\t|%s|\n", ret, line);
		free(line);
	}
	printf("ret %d\t|%s|\n", ret, line);
	free(line);
	return (0);
}
