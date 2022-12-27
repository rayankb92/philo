SRCS = $(addprefix src/, init.c main.c utilc.c time.c is_dead.c watcher.c)

NAME = philo

INC = -Iincludes

FLAGS = -g3 #-fsanitize=thread # -Wall -Werror -Wextra

OBJS = ${SRCS:.c=.o}

${NAME} : ${OBJS}
		gcc ${FLAGS} ${INC} $(OBJS) -o $(NAME)

all : ${NAME}

%.o:%.c
		gcc ${FLAGS} ${INC} -c $< -o $@

clean :
		rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : all bonus clean fclean