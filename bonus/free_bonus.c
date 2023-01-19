/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:42:06 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/19 10:01:19 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

/*
	This function is used to free cmd_args
	which is only allocated in child process
	(hence the name of the function).
*/
void	free_child(t_pipex *pipex)
{
	int	k;

	k = 0;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[k])
			free(pipex->cmd_args[k++]);
		free(pipex->cmd_args);
	}
}

void	free_bin_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->bin_paths[i])
	{
		if (pipex->bin_paths[i])
			free(pipex->bin_paths[i++]);
	}
	free(pipex->bin_paths);
}

void	free_pipefd(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipex->pipefd[i])
			free(pipex->pipefd[i++]);
	}
	free(pipex->pipefd);
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->bin_paths)
		free_bin_paths(pipex);
	if (pipex->pipefd)
		free_pipefd(pipex);
}
