NAME	= cub3D

SRCS	=	main.c					\
			exec/cub_utils.c		\
			exec/free_functions.c	\
			exec/init.c				\
			exec/init_dir.c			\
			exec/movement.c			\
			exec/rotation_camera.c	\
			exec/raycast_lines.c	\
			exec/floor_cast.c		\
			exec/load_textures.c	\
			exec/draw.c				\
			exec/hooks.c			\
			exec/get_rayprog.c		\
									\
			parsing/fail.c			\
			parsing/parsing.c		\
			parsing/get_east.c		\
			parsing/get_west.c		\
			parsing/get_floor.c		\
			parsing/get_north.c		\
			parsing/check_map.c		\
			parsing/get_south.c		\
			parsing/get_colors.c	\
			parsing/ft_splitv2.c	\
			parsing/check_color.c	\
			parsing/get_ceiling.c	\
			parsing/parsing_next.c	\

HEADER_FILES = cub3d.h

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address

LFLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all:		${NAME}

%.o : %.c 	${HEADER_FILES}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			mkdir -p ./obj/
			@$(MAKE) -C ./mlx_linux
			@$(MAKE) -C ./libft
			@${CC} ${CFLAGS} ${OBJS} ${LFLAGS} ./libft/libft.a -o cub3D
			mv ./main.o ./*/*.o ./obj/

clean:
			${RM} ${OBJS} ./obj/

fclean:		clean
			${RM} cub3D
			${MAKE} -C ./mlx_linux clean
			${MAKE} -C ./libft fclean

re:			fclean all

.PHONY:		all clean fclean re cub3D
