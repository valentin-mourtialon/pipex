/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:40:00 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/17 19:31:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*get_exe_path(char **bin_paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	while (*bin_paths)
	{
		tmp = ft_strjoin(*bin_paths, "/");
		if (tmp == NULL)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (cmd_path == NULL)
			return (free(tmp), NULL);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		bin_paths++;
	}
	return (NULL);
}

static void	first_child_io(t_pipex pipex)
{
	if (pipex.exec_cmd_input == 1)
	{
		if (pipex.input_file >= 0)
		{
			dup2(pipex.input_file, STDIN_FILENO);
			close(pipex.input_file);
		}
		dup2(pipex.pipefd[pipex.index][1], STDOUT_FILENO);
	}
}

static void	last_child_io(t_pipex pipex, char **av)
{
	init_output(&pipex, av);
	if (pipex.exec_cmd_output == 1)
	{
		dup2(pipex.pipefd[pipex.index][0], STDIN_FILENO);
		dup2(pipex.output_file, STDOUT_FILENO);
		close(pipex.output_file);
	}
}

static void	child_io(t_pipex pipex)
{
	dup2(pipex.pipefd[pipex.index - 1][0], STDIN_FILENO);
	dup2(pipex.pipefd[pipex.index][1], STDOUT_FILENO);
}

void	child(t_pipex pipex, char **av, char **envp)
{
	pipex.childpid = fork();
	//printf("\tchildpid = %d\n", pipex.childpid);
	if (pipex.childpid == 0)
	{
		printf("\t\tchildpid = %d\n", pipex.childpid);
		if (pipex.index == 0)
			first_child_io(pipex);
		else if (pipex.index == pipex.cmd_nbr - 1)
			last_child_io(pipex, av);
		else
			child_io(pipex);
		close_all_pipes(&pipex);
		pipex.cmd_args = ft_split(av[pipex.index + 2], ' ');
		if (!pipex.cmd_args)
			exit_child(&pipex, NULL);
		pipex.exe_path = get_exe_path(pipex.bin_paths, pipex.cmd_args[0]);
		if (!pipex.exe_path)
		{
			alert_msg(pipex.cmd_args[0]);
			exit_child(&pipex, CMD_ALERT);
		}
		execve(pipex.exe_path, pipex.cmd_args, envp);
	}
	else if (pipex.childpid < 0)
		alert_msg(FORK_ALERT);
}

/*
	Reminder:

	int	pipefd[2];

	pipefd[0] -> Read
	pipefd[1] -> Write

*/

 /* 
	Description of our t_pipex structure :

	argv index :			 0     1    2    3    4    5     6
					argv = pipex file1 cmd1 cmd2 cmd3 cmd4 file2
	pipex.index :						0    1    2    3

	ac = 7
	pipex.cmd_nbr = 7 - 3 = 4
	pipex.index = [0, 1, 2, 3]
	cmd = argv[pipex.index + 2]

*/

/*
	Description of the 3 conditions in child function

	1. if (pipex.index == 0)

							pipefd[0]
							write
							  1
		input_file    cmd1    |    cmd2
							  0
							read
						0			1

	1. if (pipex.index == pipex.cmd_nbr - 1)

					pipefd[p - 1]
					write
					 1
		cmd p - 1    |    cmd p    output_file
			         0
				    read
		   p - 1			p

	3. else

			pipefd[i-1]   pipefd[i]
				  1         1
		 cmd i-1  |  cmd i  |
				  0         0
			i-1        i

		dup2(pipex.pipefd[pipex.index - 1][1], 0);
		dup2(pipex.pipefd[pipex.index][0], 1);
*/

/*
	After the ones we used are duplicated,
	all fds should be closed!

	Example:
		Let's say we want to execute command number i.

		We have to dup2 pipefd[i][1] to write inside
		and we also have to dup2 pipefd[i - 1][0] to
		read from.

		After doing it, we should close all fds, the
		duplicated ones included.

		            pipefd[0]               pipefd[i-1]  pipefd[i]    pipefd[p -1]
		        		 1                       1         1             1
		input_file cmd 0 |... ... ... | cmd i-1  |  cmd i  | ... ... ... |  cmd p  output_file
				         0                       0         0             0
			                               i-1        i					    p - 1
	
*/