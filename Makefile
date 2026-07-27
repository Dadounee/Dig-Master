NAME		= DigMaster

OBJ_DIR		= obj
RAYLIB_DIR	= libs/raylib/src

SRCS		= srcs/main.c
MAP_SRCS	= srcs/map/ores.c \
			srcs/map/zones.c \
			srcs/map/map.c \
			srcs/map/display_map.c

WEAPNS_SRCS = srcs/weapons/pickaxe_radius.c \
			srcs/weapons/pickaxes.c \
			srcs/weapons/helmets.c \
			srcs/weapons/chestplates.c \
			srcs/weapons/leggings.c \
			srcs/weapons/boots.c

PLAYER_SRCS = srcs/player/player.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o) $(MAP_SRCS:%.c=$(OBJ_DIR)/%.o) $(WEAPNS_SRCS:%.c=$(OBJ_DIR)/%.o) $(PLAYER_SRCS:%.c=$(OBJ_DIR)/%.o)
RAYLIB		= libs/raylib/src/libraylib.a
LIBS		= -L./libs/raylib/src \
			-I./includes/funcs \
			-I./includes/structs \
			-lraylib \
			-lGL \
			-lm \
			-lpthread \
			-ldl \
			-lrt \
			-lX11

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I./includes -I$(RAYLIB_DIR) -o3

all: $(RAYLIB) $(NAME)

run: all
	./$(NAME)

$(RAYLIB):
	make -C $(RAYLIB_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)/*

fclean: clean
	rm -f $(NAME)
	make -C $(RAYLIB_DIR) clean

re: fclean all

.PHONY: all clean fclean re
