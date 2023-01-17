/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:41:37 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/17 19:21:03 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*
	In this function, we prevent the program from
	throwing a "Unvalid close of file descriptor -1" 
	warning.
*/
void	close_files(t_pipex *pipex)
{
	if (pipex->input_file >= 0)
		close(pipex->input_file);
	if (pipex->output_file >= 0)
		close(pipex->output_file);
}

void	close_pipe(int	*pipefd)
{
	if (pipefd[0] >= 0)
		close(pipefd[0]);
	if (pipefd[1] >= 0)
		close(pipefd[1]);
}

void	close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr - 1 && pipex->pipefd)
	{
		if (pipex->pipefd[i])
			close_pipe(pipex->pipefd[i]);
		i++;
	}
}