# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 14:51:38 by egache            #+#    #+#              #
#    Updated: 2025/08/08 20:33:15 by egache           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# LIBS		:=	m
# LIBS_TARGET	:=			\
# 	libft/libft.a			\
# 	mlx_linux/libmlx.a		\
# 	ft_printf/libprintf.a	\
# 	get_next_line/libgnl.a	\

HEADER := include/philosophers.h

HEAD		:=	\
include	\

NAME	:=	philo

SRC_DIR	:=	src
SRC		:=	\
philosophers.c	\
tfbil.c	\
initialisation.c \
debug.c	\
init_philo.c \
philo_routine.c \
monitoring.c \
free_exit.c

SRC		:=	$(SRC:%=$(SRC_DIR)/%)

BUILD_DIR:=	.build
OBJ		:=	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP		:=	$(OBJ:%.o=.d)

#AR	:=	ar -rcs

CC		:=	cc
CFLAGS        :=    -Wall -Wextra -Werror -g3
#CFLAGS        :=    -fsanitize=thread -Wall -Wextra -Werror -g3
INCLUDE	:=	$(addprefix -I,$(HEAD)) -MMD -MP
# LIBDIR	:=	$(addprefix -L,$(dir $(LIBS_TARGET)))
# LIBNAME	:=	$(addprefix -l,$(LIBS))

DIR_DUP	=	mkdir -p $(@D)

MAKEFLAGS	+=	--no-print-directory

RM	:=	rm -f
RMF	:=	rm -rf

all	:	$(NAME)

$(NAME)	:	$(OBJ) $(LIBS_TARGET) $(HEADER)
			$(CC) $(CFLAGS) $(LIBDIR) $(OBJ) $(LIBNAME) -o $(NAME)

$(LIBS_TARGET)	: FORCE
			@$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.c
			$(DIR_DUP)
			$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

-include $(DEP)

clean:
			$(RM) $(OBJ) $(DEP)
			$(RMF) $(BUILD_DIR)

fclean:	clean
			$(RM) $(NAME)

re:
			$(MAKE) fclean
			$(MAKE) all


FORCE :

.PHONY:	all clean fclean FORCE re
