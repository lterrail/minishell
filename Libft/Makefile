# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/05 16:05:37 by lterrail          #+#    #+#              #
#    Updated: 2018/11/24 16:49:49 by lterrail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM		=	rm -rf

NAME	=	libft.a

CFLAGS	+=	-Wall -Wextra -Werror

CFLAGS	+=	-Iincludes

FT_PRINTF_SRCS	=	utils.c							\
					utils_printf.c					\
					utils_llitoa.c					\
					ft_printf.c						\
					ft_conversions.c				\
					ft_specifiers.c					\
					ft_modificateurs.c				\
					ft_print_resultat.c				\
					ft_print_color.c				\
					specifiers/ft_printf_s.c		\
					specifiers/ft_printf_smaj.c		\
					specifiers/ft_printf_d.c		\
					specifiers/ft_printf_c.c		\
					specifiers/ft_printf_x_p.c		\
					specifiers/ft_printf_o.c		\
					specifiers/ft_printf_u.c		\
					specifiers/ft_printf_pourcent.c

SRCS = 		ft_atoi.c			\
			ft_bzero.c			\
			ft_isalnum.c		\
			ft_isalpha.c		\
			ft_isascii.c		\
			ft_isdigit.c		\
			ft_iscmd.c			\
			ft_itoa.c			\
			ft_memalloc.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_memcpy.c			\
			ft_memdel.c			\
			ft_memmove.c		\
			ft_memset.c			\
			ft_putchar.c		\
			ft_putchar_fd.c		\
			ft_putendl.c		\
			ft_putnbr.c			\
			ft_putstr.c			\
			ft_putstr_fd.c		\
			ft_strcat.c			\
			ft_strchr.c			\
			ft_strcmp.c			\
			ft_strcpy.c			\
			ft_strdel.c			\
			ft_strdup.c			\
			ft_strequ.c			\
			ft_strjoin.c		\
			ft_strlen.c			\
			ft_strncat.c		\
			ft_strncmp.c		\
			ft_strncpy.c		\
			ft_strnequ.c		\
			ft_strnew.c			\
			ft_strnstr.c		\
			ft_strrchr.c		\
			ft_strsplit.c		\
			ft_strstr.c			\
			ft_strsub.c			\
			ft_strtrim.c		\
			ft_nbrlen.c			\
			get_next_line.c		\
			ft_bigger_than_integer.c \
			ft_strlen_char.c	\

SRCS	+=	$(addprefix ft_printf/, $(FT_PRINTF_SRCS))

OBJS	=	$(addprefix srcs/, $(SRCS:.c=.o))

$(NAME):	 $(OBJS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)
		@printf "\n"

all:	$(NAME)

%.o : %.c
	@gcc -o $@ -c $< $(CFLAGS)
	@printf "."

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
