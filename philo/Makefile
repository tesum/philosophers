NAME	=	philo

SRCS	=	srcs/main.c		\
			srcs/parcer.c	\
			srcs/day.c		\

HEADER	=	srcs/philo.h

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS	=	-Wall -Wextra -Werror -I.
RM		=	rm -f
CC		=	gcc

all		:	$(NAME)

$(OBJ)	:	$(HEADER)

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean	:
			$(RM) $(OBJ)
		
fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re