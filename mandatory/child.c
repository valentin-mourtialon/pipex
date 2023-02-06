/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:40:00 by vmourtia          #+#    #+#             */
/*   Updated: 2023/02/06 10:31:02 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/* 
	F_OK 82 ?
*/
static char	*get_exe_path(char **bin_paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (bin_paths == NULL)
		return (NULL);
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

/*
	The first 'close' (l.93) is for the one side of the 
	pipe that we don't use !

	Why no free is needed when the cmd is well 
	executed with 'execve' ? (l.111)
*/
void	second_child(t_pipex pipex, char **av, char **envp)
{
	close(pipex.pipefd[1]);
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[0]);
	dup2(pipex.output_file, 1);
	close(pipex.output_file);
	pipex.cmd_args = ft_split(av[3], ' ');
	pipex.exe_path = get_exe_path(pipex.bin_paths, pipex.cmd_args[0]);
	if (!pipex.exe_path)
	{
		alert_msg(pipex.cmd_args[0]);
		alert_msg(CMD_ALERT);
		free_child(&pipex);
		free_pipex(&pipex);
		exit(1);
	}
	execve(pipex.exe_path, pipex.cmd_args, envp);
}

void	run_second_child(t_pipex pipex, char **av, char **envp)
{
	pipex.child2_pid = fork();
	if (pipex.child2_pid == 0)
		second_child(pipex, av, envp);
	else if (pipex.child2_pid < 0)
		alert_msg(FORK_ALERT);
}

void	first_child(t_pipex pipex, char **av, char **envp)
{
	close(pipex.pipefd[0]);
	if (pipex.input_file >= 0)
	{
		dup2(pipex.input_file, 0);
		close(pipex.input_file);
	}
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[1]);
	pipex.cmd_args = ft_split(av[2], ' ');
	if (!pipex.cmd_args)
		exit_child(&pipex, NULL, NULL);
	pipex.exe_path = get_exe_path(pipex.bin_paths, pipex.cmd_args[0]);
	if (!pipex.exe_path)
		exit_child(&pipex, pipex.cmd_args[0], CMD_ALERT);
	execve(pipex.exe_path, pipex.cmd_args, envp);
}

void	run_first_child(t_pipex pipex, char **av, char **envp)
{
	pipex.child1_pid = fork();
	if (pipex.child1_pid == 0)
		first_child(pipex, av, envp);
	else if (pipex.child1_pid < 0)
		alert_msg(FORK_ALERT);
}
