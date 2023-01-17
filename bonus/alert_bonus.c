/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:39:06 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/17 17:36:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*
	There is no exit() in order to reproduce the true pipe
	behavior, which runs all following commands even if
	the input file is not found.
*/
void	error_msg(char *msg)
{
	perror(msg);
}

void	alert_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	exit_child(t_pipex *pipex, char *msg)
{
	if (msg != NULL)
		alert_msg(msg);
	free_child(pipex);
	free_pipex(pipex);
	exit(1);
}