#include "philo_two.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	timestamp(t_philosopher *philo)
{
	return ((int)(get_time() - philo->start_time));
}

void	thread_sleep(unsigned long time)
{
	unsigned long	now;
	unsigned long	until;

	now = get_time();
	until = now + time;
	while (now < until)
	{
		now = get_time();
		if (now >= until)
			return ;
		usleep(100);
	}
}

void	say(char *str, t_philosopher *philo)
{
	sem_wait(philo->saying);
	printf(str, timestamp(philo), philo->index);
	sem_post(philo->saying);
}

void	destroy_philos(t_settings	*settings)
{
	int	i;

	i = 0;
	while (i < settings->num_of_phil)
	{
		free(settings->phil[i]);
		i++;
	}
	sem_unlink("/forks");
	sem_unlink("/saying");
	sem_unlink("/dl_crutch");
	free(settings->phil);
}
