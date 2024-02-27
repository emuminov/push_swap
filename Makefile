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
HEAD=$(HEAD_FILE:%.h=$(HEAD_DIR)/%.h)

SRCS_DIR=srcs
SRCS=$(FILES:%.c=$(SRCS_DIR)/%.c)
BONUS_SRCS=$(subst main.c,bonus_main.c,$(SRCS))

OBJS_DIR=objs
OBJS=$(FILES:%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS=$(subst main.o,bonus_main.o,$(OBJS))

#libft declarations--------------------------------
LIB=libft.a
LIB_DIR=libft
LIB_PATH=$(LIB_DIR)/$(LIB)

#rules---------------------------------------------
$(NAME): $(LIB) $(HEAD) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $@

$(BONUS_NAME): $(LIB) $(HEAD) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIB) -o $(BONUS_NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(SRCS) $(HEAD)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/bonus_main.o: $(SRCS_DIR)/bonus_main.c $(BONUS_SRCS) $(HEAD)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(LIB_PATH)
	cp $(LIB_PATH) .

$(LIB_PATH):
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
