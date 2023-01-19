/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:42:45 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/19 10:00:47 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static int	init_pipefd(t_pipex *pipex)
{
	int	i;

	pipex->pipefd = malloc(sizeof(int *) * (pipex->cmd_nbr - 1));
	if (!pipex->pipefd)
		return (-1);
	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		pipex->pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipefd[i])
			return (-1);
		pipex->pipefd[i][0] = 0;
		pipex->pipefd[i][1] = 0;
		i++;
	}
	return (0);
}

/*
	The cmd is executed by default exec_cmd is set to True.
	exec_cmd is set to False if input_file is not found.

	cmd_nbr = number of command
	Example:
	file1 cmd1 cmd2 cmd3 file2 ac = 6 cmd_nbr = 6 - 3

	paths = all bin paths in PATH separeted with ':' 
	as one string.

	bin_paths = all binary paths as a tab of char*.
	
	exe_path = the cmd executable file path. 
	Set in childs.

	cmd_args = It's a tab of char*.
	The first char * is the cmd.
	All other char* are either an option or an arg of the cmd.
*/
int	init_pipex(t_pipex *pipex, int ac)
{
	pipex->index = 0;
	pipex->cmd_nbr = ac - 3;
	pipex->exec_cmd_input = 1;
	pipex->exec_cmd_output = 1;
	pipex->input_file = -1;
	pipex->output_file = -1;
	pipex->childpid = -1;
	if (init_pipefd(pipex) < 0)
		return (-1);
	pipex->paths = NULL;
	pipex->exe_path = NULL;
	pipex->bin_paths = NULL;
	pipex->cmd_args = NULL;
	return (0);
}

/*
	This function only exists to reproduce the true bash behavior:
	if the input file does not exist, the pipe does not actually
	exit the process. That is why my error_msg function does not exit.

	This behavior requires us to consider the proper execution of the
	rest of the program, even if the input file does not exist.
	
	exec_cmd is initialized as 1 before t_pipex is passed to the
	following function.
*/
void	init_input(t_pipex *pipex, char **av)
{
	pipex->input_file = open(av[1], O_RDONLY);
	if (pipex->input_file < 0)
	{
		error_msg(av[1]);
		pipex->exec_cmd_input = 0;
	}
}

/*
	We initiate exec_cmd as 1 to erase the 
	previous value which could be either
	1 if the input file were valid or 0 if
	it were not.
*/
void	init_output(t_pipex *pipex, char **av)
{
	pipex->output_file = open(av[pipex->index + 3], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->output_file < 0)
	{
		error_msg(av[pipex->index + 3]);
		pipex->exec_cmd_output = 0;
	}
}
