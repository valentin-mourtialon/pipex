# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 16:16:53 by valentin          #+#    #+#              #
#    Updated: 2023/01/16 15:28:48 by vmourtia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS_LIBFT =	bonus/libft/ft_split.c \
				bonus/libft/ft_strlen.c \
				bonus/libft/ft_strjoin.c \
				bonus/libft/ft_strncmp.c

BONUS_SRCS =	bonus/main.c \
				bonus/init.c \
				bonus/free.c \
				bonus/close.c \
				bonus/wait.c \
				bonus/child.c \
				bonus/alert.c

SRCS =			mandatory/main.c \
				mandatory/init.c \
				mandatory/free.c \
				mandatory/close.c \
				mandatory/wait.c \
				mandatory/child.c \
				mandatory/alert.c

LIBFT  =		mandatory/libft/ft_split.c \
				mandatory/libft/ft_strlen.c \
				mandatory/libft/ft_strjoin.c \
				mandatory/libft/ft_strncmp.c

OBJS = 			${SRCS:c=o} ${LIBFT:c=o}

BONUS_OBJS = 	${BONUS_SRCS:c=o} ${BONUS_LIBFT:c=o}

NAME =			pipex

CC =			cc

CFLAGS =		-Wall -Werror -Wextra

INC =			-I./includes/

RM =			rm -f

all :			${NAME}

bonus :			$(BONUS_OBJS)
				$(CC) $(BONUS_OBJS) -o $(NAME)

%.o : %.c
				${CC} ${CFLAGS} ${INC} -c $< -o $@ -g


${NAME} :		${OBJS}
				${CC} ${OBJS} -o ${NAME}

clean :
				${RM} ${OBJS} $(BONUS_OBJS)

fclean :		clean
				${RM} ${NAME}

re :			fclean all

.PHONY :		all clean fclean re

