/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:18:36 by valentin          #+#    #+#             */
/*   Updated: 2023/01/09 16:49:41 by vmourtia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define ARGS_INPUT_ALERT "Invalid number of arguments.\n"
# define OUTPUT_FILE_ALERT "Output file error.\n"
# define PATH_NOT_FOUND_ALERT "PATH not found.\n"
# define SPLIT_BIN_PATHS_ALERT "Error while splitting PATH.\n"
# define PIPE1_ERR "Pipe 1"
# define CMD_ALERT ": Command not found.\n"
# define INTERRUPT_CHILD1 "First child interrupted.\n"
# define INTERRUPT_CHILD2 "Second child interrupted.\n"

typedef struct	s_pipex {
	int		exec_cmd;
	int		input_file;
	int		output_file;
	int		child1_pid;
	int		child2_pid;
	int		pipefd[2];
	char	*paths;
	char	*exe_path;
	char	**bin_paths;
	char	**cmd_args;
}	t_pipex;

/* stdlib */
size_t	ft_strlen(const char *s);
char    **ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

/* alert.c */
void	error_msg(char *msg);
void	alert_msg(char *msg);

/* init.c */
int		init_io(t_pipex *pipex, char **av);
int		init_pipex(t_pipex *pipex, char **av);

/* free.c */
void	free_child(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);

/* close.c */
void	close_files(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);

/* child.c */
char	*get_exe_path(char **bin_paths, char *cmd);
void	second_child(t_pipex pipex, char **av, char **envp);
void	first_child(t_pipex pipex, char **av, char **envp);

#endif