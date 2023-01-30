/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 07:26:47 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/30 11:47:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exit_child(t_pipex *pipex, char *msg1, char *msg2)
{
	if (msg1 != NULL)
		alert_msg(msg1);
	if (msg2 != NULL)
		alert_msg(msg2);
	free_child(pipex);
	free_pipex(pipex);
	exit(1);
}
