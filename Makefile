# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 16:16:53 by valentin          #+#    #+#              #
#    Updated: 2023/01/17 18:01:26 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS_SRCS =	bonus/main_bonus.c \
				bonus/init_bonus.c \
				bonus/free_bonus.c \
				bonus/close_bonus.c \
				bonus/wait_bonus.c \
				bonus/child_bonus.c \
				bonus/alert_bonus.c

SRCS =			mandatory/main.c \
				mandatory/init.c \
				mandatory/free.c \
				mandatory/close.c \
				mandatory/wait.c \
				mandatory/child.c \
				mandatory/alert.c

LIBFT  =		libft/ft_split.c \
				libft/ft_strlen.c \
				libft/ft_strjoin.c \
				libft/ft_strncmp.c

OBJS = 			${SRCS:c=o} ${LIBFT:c=o}

BONUS_OBJS = 	${BONUS_SRCS:c=o} ${LIBFT:c=o}

NAME =			pipex

CC =			cc

CFLAGS =		-Wall -Werror -Wextra

INC =			-I./includes/

RM =			rm -f

all :			mandatory

bonus :			$(BONUS_OBJS)
				$(CC) $(BONUS_OBJS) -o $(NAME)

%.o : %.c
				${CC} ${CFLAGS} ${INC} -c $< -o $@ -g

mandatory :		${OBJS}
				${CC} ${OBJS} -o ${NAME}

clean :
				${RM} ${OBJS} $(BONUS_OBJS)

fclean :		clean
				${RM} ${NAME}

re :			fclean all

rebonus :		fclean bonus

.PHONY :		all clean fclean bonus re

