CFLAGS = -Werror -Wextra -Wall -MMD -g3
LDFLAGS = -lreadline
INCLUDES = -Iincludes -I./lib/libft/includes
SRC_DIR = src
OBJ_DIR = objs
LIBFT = lib/libft/lib/libft.a

SRCS = $(shell find $(SRC_DIR) $(SRC_DIR) -name '*.c')

OBJS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(notdir $(basename $(SRCS)))))

DEPENDS = $(OBJS:.o=.d)

NAME = minishell
-include $(DEPEND)

.PHONY: all
all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LDFLAGS) 
			$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC)  $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C lib/libft

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C lib/libft clean

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C lib/libft fclean

.PHONY:
re: fclean all
