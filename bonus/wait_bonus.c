/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:12:48 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/18 11:18:57 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	wait_first_child(t_pipex *pipex, int *status)
{
	printf("\t\twait first child...\n");
	waitpid(pipex->childpid, status, 0);
	if (!WIFEXITED(*status))
	{
		close_files(pipex);
		free_pipex(pipex);
		printf("\t\tEnd wait first child...\n");
		return (alert_msg(INTERRUPT_FIRST_CHILD), -1);
	}
	printf("\t\tEnd wait first child...\n");
	return (0);
}

static int	wait_child(t_pipex *pipex, int *status)
{
	printf("\t\twait child...\n");
	waitpid(pipex->childpid, status, 0);
	if (!WIFEXITED(*status))
	{
		close_files(pipex);
		free_pipex(pipex);
		return (alert_msg(INTERRUPT_CHILD), -1);
	}
	return (0);
}

static int	wait_last_child(t_pipex *pipex, int *status)
{
	printf("\t\twait last child...\n");
	waitpid(pipex->childpid, status, 0);
	if (!WIFEXITED(*status))
	{
		close_files(pipex);
		free_pipex(pipex);
		return (alert_msg(INTERRUPT_LAST_CHILD), -1);
	}
	return (0);
}

/*
	The one tricky thing in this function are the "if conditions".
	These conditions are set to prevent the program from waiting 
	for a childpid that is not initialized 
	(as there is no fork if the input file is not found).
*/
int	ft_wait(t_pipex *pipex)
{
	int		status;
		
	if (pipex->index == 0 && pipex->exec_cmd_output == 1 && wait_first_child(pipex, &status) < 0)
		return (0);
	if (pipex->index == pipex->cmd_nbr - 1)
	{
		close_all_pipes(pipex);
		if (pipex->exec_cmd_input == 1 && wait_last_child(pipex, &status) < 0)
			return (0);
		close_files(pipex);
		free_pipex(pipex);
	}
	if (pipex->index > 0 && pipex->index < pipex->cmd_nbr - 1)
	{
		if (wait_child(pipex, &status) < 0)
			return (0);
	}
	return (0);
}