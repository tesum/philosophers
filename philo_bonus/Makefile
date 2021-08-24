NAME	=	philo

SRCS	=	srcs/main.c		\
			srcs/parcer.c	\
			srcs/day.c		\

HEADER	=	srcs/philo_bonus.h

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS	=	 -I. -Wall -Wextra -Werror
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