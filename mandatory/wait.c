/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:12:48 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/30 12:46:15 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*
static int	wait_first_child(t_pipex *pipex, int *status)
{
	waitpid(pipex->child1_pid, status, 0);
	if (!WIFEXITED(*status))
	{
		close_files(pipex);
		free_pipex(pipex);
		return (alert_msg(INTERRUPT_CHILD1), -1);
	}
	return (0);
}

static int	wait_second_child(t_pipex *pipex, int *status)
{
	waitpid(pipex->child2_pid, status, 0);
	if (!WIFEXITED(*status))
	{
		close_files(pipex);
		free_pipex(pipex);
		return (alert_msg(INTERRUPT_CHILD2), -1);
	}
	return (0);
}
*/

/*
	The one tricky thing in this function are the if-conditions.
	These conditions are set to prevent the program from waiting for a pid
	that is not initialized (as there is no fork if the input file is
	not found).
*/
int	ft_wait(t_pipex *pipex)
{
	int		status;

	close_pipes(pipex);
	if (pipex->exec_cmd_input == 1)/* && wait_first_child(pipex, &status) < 0)*/
		waitpid(pipex->child1_pid, status, 0);
	if (pipex->exec_cmd_output == 1)/* && wait_second_child(pipex, &status) < 0)*/
		waitpid(pipex->child2_pid, status, 0);
	close_files(pipex);
	free_pipex(pipex);
	return (0);
}
