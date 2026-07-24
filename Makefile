NAME		= DigMaster

OBJ_DIR		= obj
RAYLIB_DIR	= libs/raylib/src

SRCS		= srcs/test.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBS		= -L./includes/raylib/src \
			-lraylib \
			-lopengl32 \
			-lgdi32 \
			-lwinmm \
			-lm \
			-lpthread

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I. -I$(RAYLIB_DIR)

all: $(NAME)

run: all
	./$(NAME)

$(RAYLIB):
	make -C $(RAYLIB_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(RAYLIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(RAYLIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(RAYLIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
