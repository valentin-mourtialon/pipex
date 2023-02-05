/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:18:54 by valentin          #+#    #+#             */
/*   Updated: 2023/02/05 15:50:10 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <pipex_bonus.h>
# include <signal.h>

# ifndef BUFFER_SIZE
# 	define BUFFER_SIZE 10
# endif

/*
	The char *str is malloc.
	So, it needs to be freed.
*/
typedef struct s_list {
	char			*str;
	struct s_list	*next;
} t_list;

typedef struct s_gnl {
	char	*line;
	char	*buffer;
	size_t	nbytes;
	int		fd;
} t_gnl;

/* get_next_line.c */
char	*get_next_line(int fd);

/* memory.c */
t_list	*get_last_memory_element(t_list *memory);
t_list	*memory_new_element(char *buffer, size_t nbytes);
void	add_back_to_memory(t_list **memory, t_gnl *gnl);

/* extract.c */
void	extract_line(t_list *memory, t_gnl *gnl);

/* clear.c */
void	free_memory(t_list **memory);
void	clear_memory(t_list **memory);

#endif