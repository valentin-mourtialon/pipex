/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:40:00 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/16 17:25:58 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

/* F_OK 82 ? */
char	*get_exe_path(char **bin_paths, char *cmd)
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

void	run_last_child(t_pipex pipex, char *last, char **envp)
{
	pipex.child_pids[pipex.index] = fork();
	if (pipex.child_pids[pipex.index] == 0)
		last_child(pipex, last, envp);
	else if (pipex.child_pids[pipex.index] < 0)
		alert_msg(FORK_ALERT);
}

/*
	The first 'close' (l.93) is for the one side of the 
	pipe that we don't use !

	Why no free is needed when the cmd is well 
	executed with 'execve' ? (l.111)
*/
void	last_child(t_pipex pipex, char *last, char **envp)
{
	close(pipex.pipefd[pipex.index][1]);
	dup2(pipex.pipefd[pipex.index][0], 0);
	close(pipex.pipefd[pipex.index][0]);
	dup2(pipex.output_file, 1);
	close(pipex.output_file);
	pipex.cmd_args = ft_split(last, ' ');
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

void	run_first_child(t_pipex pipex, char *first, char **envp)
{
	pipex.child_pids[pipex.index] = fork();
	if (pipex.child_pids[pipex.index] == 0)
		first_child(pipex, first, envp);
	else if (pipex.child_pids[pipex.index] < 0)
		alert_msg(FORK_ALERT);
}

void	first_child(t_pipex pipex, char *first, char **envp)
{
	close(pipex.pipefd[pipex.index][0]);
	if (pipex.input_file >= 0)
	{
		dup2(pipex.input_file, 0);
		close(pipex.input_file);
	}
	dup2(pipex.pipefd[pipex.index][1], 1);
	close(pipex.pipefd[pipex.index][1]);
	pipex.cmd_args = ft_split(first, ' ');
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

void	run_child(t_pipex pipex, char *cmd, char **envp)
{
	pipex.child_pids[pipex.index] = fork();
	if (pipex.child_pids[pipex.index] == 0)
		child(pipex, cmd, envp);
	else if (pipex.child_pids[pipex.index] < 0)
		alert_msg(FORK_ALERT);
}

/*
	     pipefd[i-1]   pipefd[i]
		      1         1
	cmd (i-1) | cmd (i) |
	          0         0
		i-1        i

	dup2(pipex.pipefd[pipex.index - 1][1], 0);
	dup2(pipex.pipefd[pipex.index][0], 1);
*/
void	child(t_pipex pipex, char *cmd, char **envp)
{
	// !!! close(pipex.pipefd[pipex.index - 1][0]);
	dup2(pipex.pipefd[pipex.index - 1][1], 0);
	dup2(pipex.pipefd[pipex.index][0], 1);
	// !!! close_pipes(&pipex);
	pipex.cmd_args = ft_split(cmd, ' ');
	pipex.exe_path = get_exe_path(pipex.bin_paths, pipex.cmd_args[0]);
	if (!pipex.exe_path)
	{
		alert_msg(pipex.cmd_args[0]);
		alert_msg(CMD_ALERT);
		free_child(&pipex); // !!! Change 
		free_pipex(&pipex); // !!! Change
		exit(1);
	}
	execve(pipex.exe_path, pipex.cmd_args, envp);
}