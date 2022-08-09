NAME = philo_bonus

CFLAGS =  -Wall -Wextra -Werror 

RM = rm -f

CC = cc #-fsanitize=thread -g

AR = ar -rcs

OBJECT = *.o

FILES =	philo_bonus.c\
		philo_bonus_utils.c\
		philo_bonus_utils2.c\

OBJS = $(subst .c,.o,$(FILES)) 
all : $(NAME)
$(NAME) : $(OBJS)
	$(CC)  -o $(NAME) $(OBJECT)

clean :
	$(RM) $(OBJECT)
	
fclean : clean
	$(RM) $(NAME)
	
re : clean all
