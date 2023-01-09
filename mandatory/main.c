/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:28 by valentin          #+#    #+#             */
/*   Updated: 2023/01/09 10:55:14 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	*get_bin_paths(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp);
}

/*
	The one tricky thing in this function is the first if-condition.
	This condition is set to prevent the program from waiting for a pid
	that is not initialized (as there is no fork if the input file is
	not found).
*/
static int	ft_wait(t_pipex pipex)
{
	int		status;

	close_pipes(&pipex);
	if (pipex.exec_cmd == 1)
	{
		waitpid(pipex.child1_pid, &status, 0);
		if (!WIFEXITED(status))
		{
			close_files(&pipex);
			free_pipex(&pipex);
			return (alert_msg(INTERRUPT_CHILD1), 0);
		}
	}
	waitpid(pipex.child2_pid, &status, 0);
	if (!WIFEXITED(status))
	{
		close_files(&pipex);
		free_pipex(&pipex);
		return (alert_msg(INTERRUPT_CHILD2), 0);
	}
	close_files(&pipex);
	free_pipex(&pipex);
	return (0);
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

	if (ac != 5)
		return (alert_msg(ARGS_INPUT_ALERT), 0);
	if (init_pipex(&pipex, av) == 0)
		return (0);
	if (pipe(pipex.pipefd) < 0)
		return (error_msg(PIPE1_ERR), 0);
	pipex.paths = get_bin_paths(envp);
	if (!pipex.paths)
		return (alert_msg(PATH_NOT_FOUND_ALERT), 0);
	pipex.bin_paths = ft_split(pipex.paths, ':');
	if (!pipex.bin_paths)
		return (alert_msg(SPLIT_BIN_PATHS_ALERT), 0);
	if (pipex.exec_cmd == 1)
	{
		pipex.child1_pid = fork();
		if (pipex.child1_pid == 0)
			first_child(pipex, av, envp);
	}
	pipex.child2_pid = fork();
	if (pipex.child2_pid == 0)
		second_child(pipex, av, envp);
	return (ft_wait(pipex));
}
