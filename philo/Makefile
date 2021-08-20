NAME	=	philo

SRCS	=	main.c		\
			parcer.c	\

HEADER	=	philo.h

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(HEADER)
			gcc $(OBJ) -o $(NAME)

clean	:
			$(RM) $(OBJ)
		
fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re