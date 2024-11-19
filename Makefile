CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./inc/
SRCDIR = ./src/
SRCFIL = main.cpp ConfigParser.cpp
SRCS = $(addprefix $(SRCDIR),$(SRCFIL))
OBJS = $(SRCS:.cpp=.o)
NAME = webserv

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
