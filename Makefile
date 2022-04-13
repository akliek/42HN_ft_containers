NAME = my_containers
ORIG_NAME = original_containers

RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98
ORIGINAL_FLAGS = -Wall -Wextra -Werror -std=c++98 -D STDSTL

SRC = main.cpp

OBJ = main.o
ORIG_OBJ = original_main.o

BINARIES = $(NAME) $(ORIG_NAME)

project: $(BINARIES)

$(NAME): $(OBJ)
	@stty -echoctl
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@$(CC) -o $@ $^
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"
$(OBJ): $(SRC)
	@$(CC) $(FLAGS) -c $< -o $(OBJ)

$(ORIG_NAME): $(ORIG_OBJ)
	@stty -echoctl
	@echo "$(YELLOW)\n      -> Building $(ORIG_NAME) ...$(RESET)"
	@$(CC) -o $@ $^
	@echo "$(GREEN)***   Project $(ORIG_NAME) successfully compiled   ***\n$(RESET)"
$(ORIG_OBJ): $(SRC)
	@$(CC) $(ORIGINAL_FLAGS) -c $< -o $(ORIG_OBJ)

.PHONY: clean fclean re all

all:
	make

clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -f $(OBJ) $(ORIG_OBJ)

fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f my_containers
	@rm -f original_containers

re:
	@make fclean
	@make project
