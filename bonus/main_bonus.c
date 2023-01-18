/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:28 by valentin          #+#    #+#             */
/*   Updated: 2023/01/18 13:19:52 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/* 
	file1 cmd1 | cmd2 | cmd3 | cmd4 file2
	ac = 7
	cmd_nbr = 7 - 3 = 4
	pipe_nbr = cmd_nbr - 1
*/
static void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipefd[i]) < 0)
		{
			close_pipe(pipex->pipefd[i]);
			if (pipex->pipefd[i])
				free(pipex->pipefd[i]);
		}
		i++;
	}
}

static char	*get_bin_paths(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp);
}

/*
	ac >= 5: At least: "file1 cmd1 cmd2 file2"

	Note: if the input file does not exist
	or if there is an error while opening it,
	there is no fork, and, as a result,
	the command is simply not executed.
*/
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
		return (alert_msg(ARGS_INPUT_ALERT), 0);
	if (init_pipex(&pipex, ac) < 0)
		return (alert_msg(INIT_ALERT), 0);
	init_input(&pipex, av);
	create_pipes(&pipex);
	pipex.paths = get_bin_paths(envp);
	if (!pipex.paths)
		return (alert_msg(PATH_NOT_FOUND_ALERT), 0);
	pipex.bin_paths = ft_split(pipex.paths, ':');
	if (!pipex.bin_paths)
		return (alert_msg(SPLIT_BIN_PATHS_ALERT), 0);

	printf("cmd_nbr = %d\n", pipex.cmd_nbr);
	
	while (pipex.index < pipex.cmd_nbr)
	{
		printf("\tindex = %d\n", pipex.index);
		child(&pipex, av, envp);
		printf("\tchildpid = %d\n", pipex.childpid);
		printf("\texecuted\n");
		pipex.index++;
		printf("\n");
	}
	close_all_pipes(&pipex);
	close_files(&pipex);
	free_pipex(&pipex);
	return (0);
}
