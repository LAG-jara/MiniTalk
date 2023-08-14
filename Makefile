# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 18:26:19 by alajara-          #+#    #+#              #
#    Updated: 2023/07/25 17:43:57 by alajara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		#===========#
# 		||VARIABLES||
#		#===========#

# -=-=-=-=- NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

NAME		:= minitalk
SERVER      := server
CLIENT		:= client
MKFL        := Makefile

# -=-=-=-=- CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

DEF_CLR     := \033[0;39m
GRAY        := \033[0;90m
RED         := \033[0;91m
GREEN       := \033[0;92m
YELLOW      := \033[0;93m
BLUE        := \033[0;94m
MAGENTA     := \033[0;95m
CYAN        := \033[0;96m
WHITE       := \033[0;97m

# -=-=-=-=- PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

INC_DIR := inc/
SRC_DIR := source/
UTL_DIR := utils/

LIB_DIR	:= $(INC_DIR)libft/

OBJ_DIR := .objs/
DEP_DIR := .deps/

# -=-=-=-=- CMND -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

CFLAGS	= -Wall -Wextra -Werror -W
#XFLAGS	= -fsanitize=address -g
DFLAGS	= -MT $@ -MMD -MP

AR	= ar -rcs
RM	= rm -f
MK	= mkdir -p
CP	= cp -f
I	= -I./$(LIB_DIR)

# -=-=-=-=- FILE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

LIBFT	= $(LIB_DIR)libft.a

SRCS_S	= server.c
SRCS_C	= client.c
SRCS	= valid_args.c

OBJS_S	= $(addprefix $(OBJ_DIR), $(SRCS_S:.c=.o) $(SRCS:.c=.o))
DEPS_S	= $(addprefix $(DEP_DIR), $(addsuffix .d, $(basename $(SRCS_S))))

OBJS_C	= $(addprefix $(OBJ_DIR), $(SRCS_C:.c=.o) $(SRCS:.c=.o))
DEPS_C	= $(addprefix $(DEP_DIR), $(addsuffix .d, $(basename $(SRCS_C))))
OBJS	= $(OBJS_S) $(OBJS_C) 

# -=-=-=-=- RULE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all : makelib $(NAME)

makelib:
	@$(MAKE) -C $(LIB_DIR)

$(NAME):: $(SERVER) $(CLIENT)
	@printf "\n\t$(WHITE)Program \033[1;31mMINITALK $(WHITE)has been done!$(DEF_COLOR)\n"
	
$(NAME)::
	@printf "\t$(WHITE)Nothing more to be done for program \033[1;31mMINITALK$(DEF_COLOR)\n"

$(SERVER): $(OBJS_S) minitalk.h
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJS_S) -L $(LIB_DIR) -lft -o $(SERVER)

$(CLIENT): $(OBJS_C) minitalk.h
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJS_C) -L $(LIB_DIR) -lft -o $(CLIENT)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@$(RM) -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "$(BLUE)  Test object and dependencies files cleaned.$(DEF_COLOR)"
	
fclean:
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(RM) -rf $(OBJ_DIR) $(DEP_DIR)
	@$(RM) $(SERVER) $(CLIENT)
	@echo "$(WHITE) All objects, dependencies and executables removed.$(DEF_COLOR)"
	
re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(GREEN) Cleaned and rebuilt everything for Test project.$(DEF_COLOR)"
	
$(OBJ_DIR)%.o: %.c $(MKFL)
	@$(MK) $(dir $@) $(dir $(subst $(OBJ_DIR),$(DEP_DIR), $@))
	@printf "\r$(GREEN)\tCompiling: $(YELLOW)$< $(DEF_CLR)                   \r"
	@$(CC) $(CFLAGS) $(DFLAGS) $I -c $< -o $@
	@mv $(patsubst %.o, %.d, $@) $(dir $(subst $(OBJ_DIR), $(DEP_DIR), $@))
	
-include $(DEPS_S) $(DEPS_C)

.PHONY: all clean fclean re norm
