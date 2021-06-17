#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_philosopher
{
	int				index;
	int				fork_id;
	unsigned long	last_eaten;
	int				l_fork;
	int				r_fork;
	unsigned long	start_time;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	unsigned long	time_to_sleep;
	int				should_eat;
	int				eating;
	sem_t			*forks;
	sem_t			*saying;
	sem_t			*dl_crutch;
}	t_philosopher;

typedef struct s_settings
{
	int				num_of_phil;
	unsigned long	start_time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				should_eat;
	t_philosopher	**philos;
	sem_t			*forks;
	sem_t			*saying;
	sem_t			*dl_crutch;
	pthread_t		thread;
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
int				check_philos(t_philosopher *philosoph);

#endif
