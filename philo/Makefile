# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 14:51:38 by egache            #+#    #+#              #
#    Updated: 2025/08/28 14:07:17 by egache           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER := include/philosophers.h

HEAD		:=	\
include	\

NAME	:=	philo

SRC_DIR	:=	src
SRC		:=	\
philosophers.c	\
tfbil.c	\
initialisation.c \
init_philo.c \
philo_routine.c \
philo_routine_forks.c \
philo_routine_eating.c \
philo_routine_utils.c \
monitoring.c \
ft_time.c \
free_return.c

SRC		:=	$(SRC:%=$(SRC_DIR)/%)

BUILD_DIR:=	.build
OBJ		:=	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP		:=	$(OBJ:%.o=.d)

CC		:=	cc
CFLAGS        :=    -Wall -Wextra -Werror
#CFLAGS        :=    -fsanitize=thread -Wall -Wextra -Werror
INCLUDE	:=	$(addprefix -I,$(HEAD)) -MMD -MP

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
