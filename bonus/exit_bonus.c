/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 07:41:45 by vmourtia          #+#    #+#             */
/*   Updated: 2023/01/19 10:02:03 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

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
