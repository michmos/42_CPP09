# ------------------------------------------------------------------#
# Program variables													#
# ------------------------------------------------------------------#
NAME	:= RPN

SRC_DIR := src
SRCS	:= main.cpp RPN.cpp
SRCS	:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

CC		:= c++
CFLAGS	:= -Wall -Wextra -Werror -std=c++17 -MMD -fsanitize=address
LDFLAGS	:= -fsanitize=address
DEBUG	?= 0
ifeq ($(DEBUG), 1)
	CC 		:= g++
	CFLAGS	:= -g -DDEBUG
	LDFLAGS	:=
endif
RM		:= rm -rf

# ------------------------------------------------------------------#
# Gtest variables													#
# ------------------------------------------------------------------#
# set gtest dir
GTEST_DIR		:= ../googletest/googletest
GTEST_HEADERS 	= $(GTEST_DIR)/include/gtest/*.h \
                  $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ 	= $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

OBJS_WO_MAIN	:= $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
CPPFLAGS		+= -isystem $(GTEST_DIR)/include
CFLAGS			+= -g

# set test src dir
TEST_SRC_DIR	:= $(SRC_DIR)/tests
# set test build dir
TEST_BUILD_DIR	:= $(BUILD_DIR)/tests
# put your test source file names here
TEST_SRCS		:= RPN_test.cpp
# construct full paths
TEST_SRCS		:= $(TEST_SRCS:%.cpp=$(TEST_SRC_DIR)/%.cpp)
TEST_OBJS		:= $(TEST_SRCS:$(TEST_SRC_DIR)/%.cpp=$(TEST_BUILD_DIR)/%.o)
TESTS			=  $(basename $(TEST_OBJS))



# ------------------------------------------------------------------#
# Program build rules												#
# ------------------------------------------------------------------#
all: $(NAME)

$(NAME): $(OBJS) build_tests
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

# ------------------------------------------------------------------#
# GTest build rules													#
# ------------------------------------------------------------------#
build_tests: $(GTEST_DIR) $(TESTS)

## General setup
$(GTEST_DIR):
	@if [ ! -d $@ ]; then \
		git submodule init; \
		git submodule update;\
	fi

# used to build gtest_main.o and gtest-all.o
$(TEST_BUILD_DIR)/gtest%.o : $(GTEST_SRCS_) $(GTEST_DIR)
	$(CC) $(CPPFLAGS) -I$(GTEST_DIR) $(CFLAGS) -c \
            $(GTEST_DIR)/src/gtest$*.cc -o $@
# create static library
$(TEST_BUILD_DIR)/gtest.a : $(TEST_BUILD_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
# create static library
$(TEST_BUILD_DIR)/gtest_main.a : $(TEST_BUILD_DIR)/gtest-all.o $(TEST_BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# link test object and toTest object against static library with main
$(TESTS) : $(TEST_BUILD_DIR)/%_test : $(TEST_BUILD_DIR)/%_test.o $(TEST_BUILD_DIR)/gtest_main.a $(OBJS_WO_MAIN)
	$(CC) $(CFLAGS) $^ -o $@
	@printf "$(CREATED)" $@ $(CUR_DIR)

# create test object
$(TEST_BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -c $^ -o $@

print-%:
	$(info $($*))


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
