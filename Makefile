# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lclerc <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 12:40:47 by lclerc            #+#    #+#              #
#    Updated: 2022/12/09 17:24:46 by lclerc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= 		CC
NAME= 		libftprintf.a
LFLAGS=		-Wall -Wextra -Werror
HEADER=		-I ft_printf.h
CFILES=		ft_printf.c \
			ft_utils.c \
			ft_putnbr_dec_hex_ptr.c
OBJECTS=	$(CFILES:%.c=%.o)
MAIN=		ft_print_main.c

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "\nCreating $(NAME)\n"
	@ar rucs $(NAME) $(OBJECTS) 
	@echo "\n$(NAME) created and indexed\n"

%.o:%.c 
	$(CC) -c $(CFILES) $(LFLAGS) $(HEADER) 

clean:
	/bin/rm -f $(OBJECTS) $(BOBJECTS)
	@echo "\n$(OBJECTS) deleted\n"

fclean: clean
	/bin/rm -f $(NAME)
	@echo "\n$(NAME) deleted\n"

re: fclean all

.PHONY: clean all fclean re
