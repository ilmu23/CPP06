NAME	=	abc

CC		=	c++
CFLAGS	=	-std=c++17 -Wall -Wextra -Werror

SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc

FILES	=	main.cpp \
			Base.cpp

SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS	=	$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@printf "\e[38;2;222;89;126;1m>\e[m Compiling %s\n" $@
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\e[38;2;222;89;126;1m>\e[m \e[1mDone!\e[m\n"

$(OBJDIR):
	@printf "\e[38;2;222;89;126;1m>\e[m Creating objdir\n"
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@printf "\e[38;2;222;89;126;1m>\e[m Compiling %s\n" $@
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
