/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:28 by valentin          #+#    #+#             */
/*   Updated: 2023/01/16 16:47:16 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

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
	Note: if the input file does not exist
	or if there is an error while opening it,
	there is no fork, and, as a result,
	the command is simply not executed.
*/
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	(void)av;
	(void)envp;
	if (ac < 5) /* At least: file1 cmd1 cmd2 file2 */
		return (alert_msg(ARGS_INPUT_ALERT), 0);
	if (init_pipex(&pipex, ac) < 0)
		return (alert_msg(INIT_ALERT), 0);
	init_input(&pipex, av);
	create_pipes(pipex);
	pipex.paths = get_bin_paths(envp);
	if (!pipex.paths)
		return (alert_msg(PATH_NOT_FOUND_ALERT), 0);
	pipex.bin_paths = ft_split(pipex.paths, ':');
	if (!pipex.bin_paths)
		return (alert_msg(SPLIT_BIN_PATHS_ALERT), 0);
	
	if (pipex.exec_cmd_input == 1)
		run_first_child(pipex, av[2], envp);
		
	pipex.index++;
	while (pipex.index++ < pipex.cmd_nbr - 2)
		pipex.index++;

	init_output(&pipex, av);
	if (pipex.exec_cmd_output == 1)
		run_last_child(pipex, av[ac - 2], envp);

	return (ft_wait(pipex));
}
