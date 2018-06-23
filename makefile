NAME			=	libftprintf.a

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -I$(INC_DIR)

SRC_DIR			=	./src/
SRCS			=	$(addprefix $(SRC_DIR), $(SRC))
SRC				=	ft_printf.c			\
					converter_char.c	\
					converter_float.c	\
					converter_int.c		\
					handler_binflag.c	\
					handler_char.c		\
					handler_error.c		\
					handler_float.c		\
					handler_int.c		\
					handler_litteral.c	\
					handler_ptr.c		\
					handler_str.c		\
					minilib_str.c		\
					minilib_tstr.c		\
					minilibft.c			\
					parser.c			\
					parser_flags.c

OBJ_DIR			=	./obj/
OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ))
OBJ				=	$(SRC:.c=.o)

INC_DIR			=	./include/
INCS			=	$(addprefix $(INC_DIR), $(INC))
INC				=	ft_printf.h

.PHONY: all clean fclean re

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean:				clean
	@rm -f $(NAME)

re:					fclean all