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
SRCS += ft_exit.c
SRCS += ft_echo.c
SRCS += cd_blt.c
SRCS += env.c
SRCS += printenv_blt.c

#=====================================OBJS======================================

OBJS += $(patsubst %.c, $(PATHO)%.o, $(SRCS))

LIBFT += $(PATHLIB)libft.a

vpath %.c srcs/
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
