/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:53:00 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 10:38:46 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	alloc_onearg(char **args, char **av, int i)
{
	int	arglen;

	arglen = ft_strlen(av[i]);
	args[i] = malloc(sizeof(char) * (arglen + 1));
	if (args[i] == NULL)
		return ;
	args[i][arglen] = '\0';
}

static void	alloc_args(char **args, char **av, int argsnbr)
{
	int		i;
	int		arglen;

	alloc_onearg(args, av, 0);
	alloc_onearg(args, av, 1);
	i = 2;
	while (i < argsnbr)
	{
		arglen = ft_strlen(av[i + 1]);
		args[i] = malloc(sizeof(char) * (arglen + 1));
		if (args[i] == NULL)
			return ;
		args[i][arglen] = '\0';
		i++;
	}
}

char	**retrieve_args(int argsnbr, char **av)
{
	int		i;
	int		j;
	char	**args;

	args = malloc(sizeof(char *) * (argsnbr + 1));
	if (args == NULL)
		return (NULL);
	args[argsnbr] = NULL;
	alloc_args(args, av, argsnbr);
	i = 0;
	while (i < argsnbr + 1)
	{
		j = 0;
		while (av[i][j])
		{
			if (i < 2)
				args[i][j] = av[i][j];
			else if (i > 2)
				args[i - 1][j] = av[i][j];
			j++;
		}
		i++;
	}
	return (args);
}
