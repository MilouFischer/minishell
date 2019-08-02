# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efischer <efischer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/31 17:50:10 by efischer          #+#    #+#              #
#    Updated: 2019/07/31 17:51:51 by efischer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#=====================================HEAD======================================

IFLAGS += -I
INCLUDES += includes/
LIBINCLUDES += libft/includes/
HEAD += minishell.h

#=====================================PATH======================================

PATHO += objs/
PATHI += $(INCLUDES)
PATHLIB += libft/

#====================================COMPILE=====================================

CC = gcc
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
COMPILE += $(CC) -c

#=====================================SRCS======================================

SRCS += minishell.c
SRCS += manage_env.c
SRCS += list_functions.c
SRCS += get_command.c
SRCS += expansion.c
SRCS += exec_blt.c
SRCS += exec_bin.c

#///////////////////////////////////BUILTIN/////////////////////////////////////

SRCS += exit_blt.c
SRCS += echo_blt.c
SRCS += cd_blt.c
SRCS += printenv_blt.c
SRCS += setenv_blt.c
SRCS += pwd_blt.c
SRCS += unsetenv_blt.c
SRCS += env_blt.c
SRCS += get_path.c
SRCS += clean_path.c
SRCS += change_dir.c
SRCS += flags_env_blt.c
SRCS += flags_cd_blt.c

#=====================================OBJS======================================

OBJS += $(patsubst %.c, $(PATHO)%.o, $(SRCS))

LIBFT += $(PATHLIB)libft.a

vpath %.c srcs/
vpath %.c srcs/builtin/
vpath %.h $(PATHI)

all: $(NAME)

$(NAME): $(LIBFT) $(PATHO) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(OBJS): $(PATHO)%.o: %.c $(HEAD) Makefile
	$(COMPILE) $(CFLAGS) $< $(IFLAGS) $(INCLUDES) $(IFLAGS) $(LIBINCLUDES) -o $@

$(PATHO):
	mkdir $@

$(LIBFT): FORCE
	make -C $(PATHLIB)

clean:
	$(RM) $(OBJS)
	$(RM) -R $(PATHO)
	make clean -C $(PATHLIB)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(PATHLIB)

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
