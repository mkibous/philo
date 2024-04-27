SRCS = main.c atoi.c
OBJS = $(SRCS:.c=.o)
CC = CC
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
NAME = philo
RM = rm -f
all: $(NAME)
$(NAME): $(OBJS) philosophers.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
push:
	@read -p "Enter commit message: " commit_message; \
	git add .; \
	git commit -m "$$commit_message"; \
	git push;

.PHONY: clean push