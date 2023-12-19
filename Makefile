#comilation vars-----------------------------------
CC=cc
CFLAGS=-Wall -Wextra -Werror -g

#subject declarations------------------------------
NAME=push_swap

FILES=main.c push_swap.c
HEAD_FILE=push_swap.h

HEAD_DIR=include
HEAD=$(HEAD_FILE:%.h=$(HEAD_DIR)/%.h)

SRCS_DIR=srcs
SRCS=$(FILES:%.c=$(SRCS_DIR)/%.c)

OBJS_DIR=objs
OBJS=$(FILES:%.c=$(OBJS_DIR)/%.o)

#libft declarations--------------------------------
LIB=libft.a
LIB_DIR=libft
LIB_PATH=$(LIB_DIR)/$(LIB)

#rules---------------------------------------------
$(NAME): $(LIB) $(HEAD) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(SRCS) $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(LIB_PATH)
	cp $(LIB_PATH) .

$(LIB_PATH):
	$(MAKE) -C $(LIB_DIR)

all: $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR) $@
	rm $(OBJS) -f

fclean: clean
	$(MAKE) -C $(LIB_DIR) $@
	rm $(NAME) $(LIB) -f

re: fclean
	$(MAKE) -C $(LIB_DIR) $@
	$(MAKE) all --no-print-directory

test: $(NAME)
	$(CC) tests/ft_printf.c $(NAME) -o test.out
	./test.out
	valgrind ./test.out --check-leaks=full -s
	
.PHONY: all clean fclean re test
