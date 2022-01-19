# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/14 12:04:44 by mobrycki          #+#    #+#              #
#    Updated: 2021/09/23 15:34:20 by mobrycki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

SRCS	= main.c philo.c utils.c utils_supp.c

CFLAGS 	= -Wall -Wextra -Werror

CC 		= gcc

GREEN	= \x1b[32m
YELLOW 	= \033[0;33m
RESET	= \x1b[0m

OBJ		= $(SRCS:%.c=%.o)

$(NAME)	:	$(OBJ)
			@$(CC) -lpthread $(CFLAGS) $(OBJ) -o $(NAME)
			@make clean                                                    
			@echo "${GREEN}  ____  _     _ _                       _                   ${RESET}"
			@echo "${GREEN} |  _ \| |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ ___ ${RESET}"
			@echo "${GREEN} | |_) | '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __|${RESET}"
			@echo "${GREEN} |  __/| | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \${RESET}"
			@echo "${GREEN} |_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/${RESET}"
			@echo "${GREEN}                                 |_|                        ${RESET}"
			@echo "${YELLOW}                                 	         by mobrycki   ${RESET}"

all		:	$(NAME)

clean	:
			@rm -f $(OBJ)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re