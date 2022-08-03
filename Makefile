NAME = philo_bonus

CFLAGS =  -Wall -Wextra -Werror 

RM = rm -f

CC = cc 

AR = ar -rcs

OBJECT = *.o

FILES =	main.c\
		philo_bonus_utils.c\
		#philo_utils_2.c\

OBJS = $(subst .c,.o,$(FILES)) 
all : $(NAME)
$(NAME) : $(OBJS)
	$(CC)  -o $(NAME) $(OBJECT)

clean :
	$(RM) $(OBJECT)
	
fclean : clean
	$(RM) $(NAME)
	
re : clean all
