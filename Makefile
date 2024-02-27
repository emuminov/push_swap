#comilation vars-----------------------------------
CC=cc
CFLAGS=-Wall -Wextra -Werror -g

#subject declarations------------------------------
NAME=push_swap
BONUS_NAME=checker

FILES=arr.c \
list1.c \
list2.c \
list3.c \
main.c \
move.c \
parse.c \
push_swap.c \
px.c \
rrx.c \
rx.c \
sort_utils.c \
sx.c

HEAD_FILE=push_swap.h

HEAD_DIR=include
HEADER=$(HEAD_FILE:%.h=$(HEAD_DIR)/%.h)

SRCS_DIR=srcs
SRCS=$(FILES:%.c=$(SRCS_DIR)/%.c)
BONUS_SRCS=$(subst main.c,main_bonus.c,$(SRCS))

OBJS_DIR=objs
OBJS=$(FILES:%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS=$(subst main.o,main_bonus.o,$(OBJS))

#libft declarations--------------------------------
LIB_DIR=libft
LIB=$(LIB_DIR)/libft.a

#rules---------------------------------------------
$(NAME): $(LIB) $(HEADER) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $@

$(BONUS_NAME): $(LIB) $(HEADER) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIB) -o $(BONUS_NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/main_bonus.o: $(SRCS_DIR)/main_bonus.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB)::
	$(MAKE) -C $(LIB_DIR)

all: $(NAME) $(BONUS_NAME)

bonus: $(BONUS_NAME)

clean:
	$(MAKE) -C $(LIB_DIR) $@
	rm $(OBJS_DIR) -rf

fclean: clean
	$(MAKE) -C $(LIB_DIR) $@
	rm $(NAME) $(LIB) -f
	rm $(BONUS_NAME) $(LIB) -f

re: fclean
	$(MAKE) -C $(LIB_DIR) $@
	$(MAKE) all --no-print-directory

.PHONY: all clean fclean re test bonus
