SRCS = utils_bonus.c main_bonus.c philo_bonus.c atoi_bonus.c
OBJS = $(SRCS:.c=.o)
CC = CC
CFLAGS = -Wall -Wextra  -g -fsanitize=address
NAME = philo_bonus
RM = rm -f
all: $(NAME)
$(NAME): $(OBJS) philosophers_bonus.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
%.o: %.c philosophers_bonus.h
	$(CC) $(CFLAGS) -c $<
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: clean