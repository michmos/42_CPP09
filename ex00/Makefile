
NAME	:= exec_cpp07

SRC_DIR := src
SRCS	:= main.cpp
SRCS	:= $(addprefix $(SRC_DIR)/, $(SRCS))

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

CC		:= c++
CFLAGS	:= -Wall -Wextra -Werror -std=c++11 -MMD -fsanitize=address
LDFLAGS	:= -fsanitize=address
DEBUG	?= 0
ifeq ($(DEBUG), 1)
	CC 		:= g++
	CFLAGS	:= -g -DDEBUG
	LDFLAGS	:=
endif
RM		:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)

fclean:
	$(RM) $(BUILD_DIR)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)
	$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

-include $(OBJS:.o=.d)

.PHONY = all clean fclean re


# ----------------------------------- colors --------------------------------- #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# ----------------------------------- messages ------------------------------- #

CUR_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED	:= $(MAGENTA) $(BOLD) REMOVED %s (%s) $(RESET)\n\n
CREATED	:= $(GREEN) $(BOLD) CREATED %s (%s) $(RESET)\n\n
UPDATED	:= $(GREEN) $(BOLD) CREATED OR UPDATED %s (%s) $(RESET)\n\n
