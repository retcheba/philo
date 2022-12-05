SRCS		= main.c philo.c philo_utils.c
SRC			= $(addprefix src/, $(SRCS))
OBJS		= $(SRC:src/%.c=obj/%.o)
D_OBJS		= mkdir -p $(@D)
CC			= gcc
CFLAGS		= -g -pthread -Wall -Wextra -Werror
NAME		= philo
RM			= rm -rf

all:		$(NAME)

obj/%.o: src/%.c	
			@$(D_OBJS)
			@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): 	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "\033[1;92m# ************************ #\033[0m"
			@echo "\033[1;92m#                          #\033[0m"
			@echo "\033[1;92m#      make completed      #\033[0m"
			@echo "\033[1;92m#                          #\033[0m"
			@echo "\033[1;92m# ************************ #\033[0m"

clean:
			@$(RM) $(OBJ_DIR)
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
