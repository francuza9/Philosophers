NAME	=	philo

CC	=	cc
CFLAGS	=	-g -Wall -Werror -Wextra
FLAG	=	-pthread

SR	=	src/

SRCS	=	$(SR)main.c \
		$(SR)utils.c \
		$(SR)execution.c \
		$(SR)init.c \
		$(SR)force_stop.c \
		$(SR)parsing.c \
		$(SR)exit.c

OBJS	=	$(SRCS:.c=.o)


all	: $(NAME)

$(NAME) : ft_philosophers

ft_philosophers: $(OBJS)
	$(CC) $(CFLAGS) $(FLAGS) $(FLAG) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

re:	fclean all

.PHONY : all clean fclean re ft_philosophers
