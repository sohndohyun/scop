NAME=lib/libft.a
SRCS = 
		source/ft_bzero.c \
		source/ft_calloc.c \
		source/ft_memccpy.c \
		source/ft_memchr.c \
		source/ft_memcmp.c \
		source/ft_memcpy.c \
		source/ft_memmove.c \
		source/ft_memset.c \
		source/ft_split.c \
		source/ft_strchr.c \
		source/ft_strdup.c \
		source/ft_strjoin.c \
		source/ft_strlcat.c \
		source/ft_strlcpy.c \
		source/ft_strlen.c \
		source/ft_strmapi.c \
		source/ft_strncmp.c \
		source/ft_strrchr.c \
		source/ft_strtrim.c \
		source/ft_substr.c \
		source/ft_atoi.c \
		source/ft_atod.c \
		source/ft_isalnum.c \
		source/ft_isalpha.c \
		source/ft_isascii.c \
		source/ft_isdigit.c \
		source/ft_isprint.c \
		source/ft_itoa.c \
		source/ft_putchar_fd.c \
		source/ft_putendl_fd.c \
		source/ft_putnbr_fd.c \
		source/ft_putstr_fd.c \
		source/ft_tolower.c \
		source/ft_toupper.c \
		source/ft_strnstr.c \
		source/ft_lstadd_back.c \
		source/ft_lstadd_front.c \
		source/ft_lstclear.c \
		source/ft_lstdelone.c \
		source/ft_lstiter.c \
		source/ft_lstlast.c \
		source/ft_lstmap.c \
		source/ft_lstnew.c \
		source/ft_lstsize.c \
		source/ft_lstat.c \
		source/ft_gnl.c
OBJS = ${SRCS:.c=.o}

all: $(NAME)

.c.o: $(SRCS)
	gcc -Wall -Werror -Wextra -I./include -c -o $@ $<

$(NAME): $(OBJS)
	ar rc $@ $^

clean:	
	rm -f $(OBJS)
fclean: clean
		rm -f $(NAME)
re: fclean all