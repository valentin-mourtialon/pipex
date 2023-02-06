/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:28 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 10:55:20 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	*get_bin_paths(char **envp)
{
	if (envp == NULL)
		return (NULL);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp);
}

/*
	Note: if the input file does not exist
	or if there is an error while opening it,
	there is no fork, and, as a result,
	the command is simply not executed.

	If paths is NULL, the program does not
	exit because the full bin path could be
	given by the user !
*/
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		return (alert_msg(ARGS_INPUT_ALERT), 0);
	init_pipex(&pipex);
	init_input(&pipex, av);
	if (pipe(pipex.pipefd) < 0)
		return (error_msg(PIPE1_ERR), 0);
	pipex.paths = get_bin_paths(envp);
	if (pipex.paths == NULL)
		alert_msg(PATH_NOT_FOUND_ALERT);
	pipex.bin_paths = ft_split(pipex.paths, ':');
	if (pipex.bin_paths == NULL)
		alert_msg(SPLIT_BIN_PATHS_ALERT);
	if (pipex.exec_cmd_input == 1)
		run_first_child(pipex, av, envp);
	init_output(&pipex, av);
	if (pipex.exec_cmd_output == 1)
		run_second_child(pipex, av, envp);
	return (ft_wait(&pipex));
}
