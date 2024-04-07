SRCS = main.c
OBJS = $(SRCS:.c=.o)
CC = CC
CFLAGS = -Wall Wextra -Werror
NAME = philo
RM = rm -f
all: $(NAME)
$(NAME): $(OBJS) philosophers.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: clean