SRCS = utils.c main.c philo.c atoi.c
OBJS = $(SRCS:.c=.o)
CC = CC
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
NAME = philo
RM = rm -f
all: $(NAME)
$(NAME): $(OBJS) philosophers.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $<
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: clean