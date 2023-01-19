/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:12:48 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/19 10:01:51 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

/*
	The one tricky thing in this function are the "if conditions".
	These conditions are set to prevent the program from waiting 
	for a childpid that is not initialized 
	(as there is no fork if the input file is not found).
*/
void	ft_wait(t_pipex *pipex)
{
	int		status;

	if (pipex->index < pipex->cmd_nbr - 1)
		waitpid(pipex->childpid, &status, WNOHANG);
	else if (pipex->index == pipex->cmd_nbr - 1)
	{
		close_all_pipes(pipex);
		waitpid(pipex->childpid, &status, WNOHANG);
		close_files(pipex);
		free_pipex(pipex);
	}
}
