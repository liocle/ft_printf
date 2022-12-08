
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lclerc <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 12:40:47 by lclerc            #+#    #+#              #
#    Updated: 2022/12/08 11:41:10 by lclerc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= 		CC
NAME= 		libftprintf.a
LFLAGS=		-Wall -Wextra -Werror
HEADER=		-I libft.h
CFILES=		ft_printf.c 
OBJECTS=	$(CFILES:%.c=%.o)
MAIN=		ft_print_main.c

all: $(NAME)

# Running 'ar s' corresponds to running 'ranlib' on it.
# $@ stands for whatever is on the left side of the ":"
# $^ stands for whatever is on the right side of the ":" 
# regular expression where % is a wildcard, using @echo should run the command without printing the output

$(NAME): $(OBJECTS)
	@echo "\nCreating :$(NAME):\n"
	@ar rucs $(NAME) $(OBJECTS) 
	@echo "\n$(NAME) created and indexed\n"

%.o:%.c 
	$(CC) -c $(CFILES) $(LFLAGS) $(HEADER) 


test:
	@echo "\nCompiling executable with static libft.a library:"
	$(CC) $(MAIN) $(CFLAGS) -g -fsanitize=address 

full: $(NAME)
	$(CC) $(MAIN) $(CFLAGS) -g -fsanitize=address 
	@./a.out

clean:
	/bin/rm -f $(OBJECTS) $(BOBJECTS)
	@echo "\n$(OBJECTS) deleted\n"


fclean: clean
	/bin/rm -f $(NAME)
	@echo "\n$(NAME) deleted\n"

re: fclean all

.PHONY: clean  all fclean re
