SRCS		= main.c philo_utils.c
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
			@echo "\033[1;92m# ************************ #\033[0m"
			@echo "\033[1;92m#                          #\033[0m"
			@echo "\033[1;92m#      make completed      #\033[0m"
			@echo "\033[1;92m#                          #\033[0m"
			@echo "\033[1;92m# ************************ #\033[0m"

clean:
			@$(RM) $(OBJS)
			@echo "\033[1;93m# ************************ #\033[0m"
			@echo "\033[1;93m#                          #\033[0m"
			@echo "\033[1;93m#   make clean completed   #\033[0m"
			@echo "\033[1;93m#                          #\033[0m"
			@echo "\033[1;93m# ************************ #\033[0m"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\033[1;91m# ************************ #\033[0m"
			@echo "\033[1;91m#                          #\033[0m"
			@echo "\033[1;91m#  make fclean completed   #\033[0m"
			@echo "\033[1;91m#                          #\033[0m"
			@echo "\033[1;91m# ************************ #\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
