/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:18:36 by valentin          #+#    #+#             */
/*   Updated: 2023/02/05 21:24:48 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <get_next_line.h>

# define MAX_ACS 1028
# define MAX_FDS_ALERT "To many pipes !\n"
# define ARGS_INPUT_ALERT "Invalid number of arguments.\n"
# define INIT_ALERT "Error occured during initialization.\n"
# define PATH_NOT_FOUND_ALERT "PATH not found.\n"
# define SPLIT_BIN_PATHS_ALERT "Error while splitting PATH.\n"
# define PIPE1_ERR "Pipe 1"
# define CMD_ALERT ": Command not found.\n"
# define FORK_ALERT "Fork error.\n"
# define INTERRUPT_FIRST_CHILD "First child interrupted.\n"
# define INTERRUPT_CHILD "Child interrupted.\n"
# define INTERRUPT_LAST_CHILD "Last child interrupted.\n"
# define EXECVE_ALERT "Execution issue in child process.\n"

/*
	Should be free in pipex:
	int		*pids;
	int		**pipefd;
	char	**bin_paths;

	Should be free in child:
	char	*exe_path;
	char	**cmd_args;

	No need to be free:
	char	*paths;
*/
typedef struct	s_pipex {
	int		index;
	int		cmd_nbr;
	int		exec_cmd_input;
	int		exec_cmd_output;
	int		input_file;
	int		output_file;
	int		*pids;
	int		**pipefd;
	char	*paths;
	char	*exe_path;
	char	**bin_paths;
	char	**cmd_args;
}	t_pipex;

typedef struct	s_heredoc {
	int		stdinfd;
	int		tmpfd;
	char 	*line;
	char	*limiter;
	int		written;
}	t_heredoc;

/* stdlib */
int		ft_strlen(const char *s);
char	*ft_strchr(char *s, int c);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2);

/* alert.c */
void	error_msg(char *msg);
void	alert_msg(char *msg);

/* init.c */
void	init_output(t_pipex *pipex, char **av);
void	init_input(t_pipex *pipex, char **av);
int		init_pipex(t_pipex *pipex, int cmdnbr);

/* free.c */
void	free_child(t_pipex *pipex);
void	free_bin_paths(t_pipex *pipex);
void	free_pipefd(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
void	free_args(char **args);

/* close.c */
void	close_files(t_pipex *pipex);
void	close_pipe(int	*pipefd);
void	close_all_pipes(t_pipex *pipex);
void	close_all(t_pipex *pipex);

/* wait.c */
/*void	ft_wait(t_pipex *pipex);*/
void	pipex_wait(t_pipex *pipex);

/* handle_heredoc.c */
int		init_here_doc(t_heredoc *hd, char **av);
void	exit_here_doc(t_heredoc *hd);
int		listen_here_doc(t_heredoc *hd);
int		here_doc(int ac, char **av, char **envp);

/* multipipes.c */
int		multi_pipes(int cmdnbr, char **av, char **envp);

/* child.c */
void	child(t_pipex *pipex, char **av, char **envp);

/* exit_bonus.c */
void	exit_child(t_pipex *pipex, char *msg1, char *msg2);

/* args.c */
char	**retrieve_args(int argsnbr, char **av);

#endif