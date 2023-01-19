/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:42:06 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/19 09:59:20 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

void	free_pipex(t_pipex *pipex)
{
	int	k;

	k = 0;
	while (pipex->bin_paths[k])
		free(pipex->bin_paths[k++]);
	free(pipex->bin_paths);
}
