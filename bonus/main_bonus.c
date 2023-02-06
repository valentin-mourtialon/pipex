/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:28 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 10:25:55 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

/*
	ac >= 5: At least: "file1 cmd1 cmd2 file2"

	Warning case with ac=5 and here_doc:
		./pipex here_doc LIM cmd1 outfile
		ac = 5
*/
int	main(int ac, char **av, char **envp)
{
	int	exit_code;

	if (ac < 5)
		return (alert_msg(ARGS_INPUT_ALERT), 0);
	else if (ac > MAX_ACS)
		return (alert_msg(MAX_FDS_ALERT), 0);
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (ac == 5)
			return (alert_msg(ARGS_INPUT_ALERT), 0);
		exit_code = here_doc(ac - 4, av, envp);
	}
	else
		exit_code = multi_pipes(ac - 3, av, envp);
	return(exit_code);
}
