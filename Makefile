NAME		= DigMaster

OBJ_DIR		= obj
RAYLIB_DIR	= libs/raylib/src

SRCS		= srcs/main.c
MAP_SRCS	= srcs/map/ores.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
RAYLIB		= libs/raylib/src/libraylib.a
LIBS		= -L./libs/raylib/src \
			-L./includes/funcs \
			-L./includes/structs \
			-lraylib \
			-lGL \
			-lm \
			-lpthread \
			-ldl \
			-lrt \
			-lX11

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I./includes -I$(RAYLIB_DIR)

all: $(RAYLIB) $(NAME)

run: all
	./$(NAME)

$(RAYLIB):
	make -C $(RAYLIB_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	make -C $(RAYLIB_DIR) clean

re: fclean all

.PHONY: all clean fclean re
