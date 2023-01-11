/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:28 by valentin          #+#    #+#             */
/*   Updated: 2023/01/11 11:14:23 by vmourtia         ###   ########.fr       */
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
	init_pipex(&pipex);
	init_input(&pipex, av);
	if (pipe(pipex.pipefd) < 0)
		return (error_msg(PIPE1_ERR), 0);
	pipex.paths = get_bin_paths(envp);
	if (!pipex.paths)
		return (alert_msg(PATH_NOT_FOUND_ALERT), 0);
	pipex.bin_paths = ft_split(pipex.paths, ':');
	if (!pipex.bin_paths)
		return (alert_msg(SPLIT_BIN_PATHS_ALERT), 0);
	if (pipex.exec_cmd_input == 1)
		run_first_child(pipex, av, envp);
	init_output(&pipex, av);
	if (pipex.exec_cmd_output == 1)
		run_second_child(pipex, av, envp);
	return (ft_wait(pipex));
}
