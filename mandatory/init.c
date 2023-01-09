/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:42:45 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/09 10:54:06 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*
	This function only exists to reproduce the true bash behavior:
	if the input file does not exist, the pipe does not actually
	exit the process. That is why my error_msg function does not exit.

	This behavior requires us to consider the proper execution of the
	rest of the program, even if the input file does not exist.
	
	O_TRUNC ? (l.174)
*/
int	init_io(t_pipex *pipex, char **av)
{
	pipex->input_file = open(av[1], O_RDONLY);
	if (pipex->input_file < 0)
	{
		error_msg(av[1]);
		pipex->exec_cmd = 0;
	}
	pipex->output_file = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->output_file < 0)
		return (alert_msg(OUTPUT_FILE_ALERT), 0);
	return (1);
}

/*
	The cmd is executed by default exec_cmd is set to True.
	exec_cmd is set to False if input_file is not found.

	paths = all bin paths in PATH separeted with ':' 
	as one string.

	bin_paths = all binary paths as a tab of char*.
	
	exe_path = the cmd executable file path. 
	Set in childs.

	cmd_args = It's a tab of char*.
	The first char * is the cmd.
	All other char* are either an option or an arg of the cmd.
*/
int	init_pipex(t_pipex *pipex, char **av)
{
	pipex->exec_cmd = 1;
	if (init_io(pipex, av) == 0)
		return (0);
	pipex->child1_pid = 0;
	pipex->child2_pid = 0;
	pipex->pipefd[0] = 0;
	pipex->pipefd[1] = 0;
	pipex->paths = NULL;
	pipex->exe_path = NULL;
	pipex->bin_paths = NULL;
	pipex->cmd_args = NULL;
	return (1);
}
