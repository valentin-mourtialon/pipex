/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:15:25 by valentin          #+#    #+#             */
/*   Updated: 2023/02/06 10:39:18 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	handle_sigquit(int signal)
{
	(void)signal;
	get_next_line(-1);
}

int	init_here_doc(t_heredoc *hd, char **av)
{
	hd->stdinfd = open("/dev/stdin", O_RDONLY);
	if (hd->stdinfd < 0)
		return (alert_msg("Open stdin error !\n"), 0);
	hd->tmpfd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (hd->tmpfd < 0)
		return (alert_msg("Open file here_doc error !\n"), 0);
	hd->line = get_next_line(hd->stdinfd);
	if (hd->line == NULL)
		return (alert_msg("Gnl init error !\n"), 0);
	hd->limiter = ft_strjoin(av[2], "\n");
	if (hd->limiter == NULL)
	{
		free(hd->line);
		alert_msg("Limiter join error !\n");
		return (0);
	}
	return (1);
}

/* 
	get_next_line(-1)
		Cleans static memory if it's necessary.
*/
void	exit_here_doc(t_heredoc *hd)
{
	get_next_line(-1);
	if (hd->line)
		free(hd->line);
	if (hd->limiter)
		free(hd->limiter);
	close(hd->tmpfd);
	close(hd->stdinfd);
}

int	listen_here_doc(t_heredoc *hd)
{
	while (ft_strncmp(hd->line, hd->limiter, ft_strlen(hd->limiter)) != 0)
	{
		hd->written = write(hd->tmpfd, hd->line, ft_strlen(hd->line));
		if (hd->written != ft_strlen(hd->line))
		{
			free(hd->line);
			free(hd->limiter);
			alert_msg("Write error !\n");
			return (0);
		}
		free(hd->line);
		hd->line = get_next_line(hd->stdinfd);
		if (hd->line == NULL)
		{
			alert_msg("Gnl error !\n");
			return (0);
		}
	}
	return (1);
}

/*
	Understand pipex_args vs av:

	Our multi_pipes() function has been
	designed to work without here_doc argument
	Inside of the multi_pipes() function we
	use char **av and expected it to be 
	shaped as followed: 

	Case no heredoc: we use char **av
		./pipex infile cm1 cm2 cm3 outfile
		ac = 6
		cmdnbr = 3 = ac - 3

	Note the difference when here_doc is
	mentionned:
	
	Case with heredoc: we use char **pipex_args
		./pipex here_doc LIM cm1 cm2 cm3 outfile
		ac = 7
		cmdnbr = 3 = ac - 4
*/
int	here_doc(int cmdnbr, char **av, char **envp)
{
	char		**pipex_args;
	t_heredoc	hd;
	int			hd_status;

	signal(SIGINT, handle_sigquit);
	if (init_here_doc(&hd, av) == 0)
		return (-1);
	hd_status = listen_here_doc(&hd);
	if (hd_status == 0)
	{
		exit_here_doc(&hd);
		return (-1);
	}
	else
	{
		exit_here_doc(&hd);
		pipex_args = retrieve_args(cmdnbr + 3, av);
		multi_pipes(cmdnbr, pipex_args, envp);
		if (unlink("here_doc") == -1)
			return (free_args(pipex_args), -1);
		free_args(pipex_args);
		return (0);
	}
}
