SRCS		= main.c
OBJS		= $(addprefix srcs/, $(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror 
NAME		= philo
RM			= rm -f

all:		$(NAME)

%.o: %.c
			@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): 	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "\e[96m# ************************ #"
			@echo "\e[96m#                          #"
			@echo "\e[96m#      make completed      #"
			@echo "\e[96m#                          #"
			@echo "\e[96m# ************************ #"

clean:
			@$(RM) $(OBJS)
			@echo "\e[96m# ************************ #"
			@echo "\e[96m#                          #"
			@echo "\e[96m#   make clean completed   #"
			@echo "\e[96m#                          #"
			@echo "\e[96m# ************************ #"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\e[96m# ************************ #"
			@echo "\e[96m#                          #"
			@echo "\e[96m#  make fclean completed   #"
			@echo "\e[96m#                          #"
			@echo "\e[96m# ************************ #"

re:			fclean all

.PHONY:		all clean fclean re
