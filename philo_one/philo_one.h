#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				index;
	unsigned long	last_eaten;
	int				l_fork;
	int				r_fork;
	unsigned long	start_time;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	long			should_eat;
	int				eating;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*saying;
}	t_philosopher;

typedef struct s_settings
{
	int				num_of_phil;
	unsigned long	start_time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	long			should_eat;
	t_philosopher	**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	saying;
	pthread_t		*threads;
}	t_settings;

void			*behavior(void *philo);
int				ft_atoi(const char *str);
t_settings		*init_settings(int argc, const char **argv);
int				create_threads(t_settings *t);
t_philosopher	*create_phil(t_settings *settings, int i);
int				generate_philos(t_settings *settings);
unsigned long	get_time(void);
int				timestamp(t_philosopher *p);
void			thread_sleep(unsigned long time);
void			say(char *str, t_philosopher *philo);
void			destroy_philos(t_settings	*settings);
void			destroy_philos_without_free(t_settings	*settings);

#endif
