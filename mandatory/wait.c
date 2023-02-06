/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:12:48 by vmourtia          #+#    #+#             */
/*   Updated: 2023/02/06 10:47:34 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	if (pipex->exec_cmd_input == 1)
		waitpid(pipex->child1_pid, &status, 0);
	if (pipex->exec_cmd_output == 1)
		waitpid(pipex->child2_pid, &status, 0);
	close_files(pipex);
	free_pipex(pipex);
	return (0);
}
