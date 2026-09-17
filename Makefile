NAME		= gnl
BONUS_NAME	= gnl_bonus
CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= -I ./ -D BUFFER_SIZE=42
VALGRIND	= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
SRCS		= get_next_line.c get_next_line_utils.c main.c
BONUS_SRCS	= get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c
OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@cc $(CPPFLAGS) $(CFLAGS) -c $^ -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@cc $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

valgrind: $(NAME)
	@$(VALGRIND) ./$(NAME) get_next_line.h

valgrind_bonus: $(BONUS_NAME)
	@$(VALGRIND) ./$(BONUS_NAME) get_next_line.h get_next_line.c

%.o: %.c
	@cc $(CPPFLAGS) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus valgrind valgrind_bonus clean fclean re
