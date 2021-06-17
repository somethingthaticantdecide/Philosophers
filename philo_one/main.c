#include "philo_one.h"

void	pickup_forks(t_philosopher *phil)
{
	if (phil->index % 2 == 1)
	{
		pthread_mutex_lock(&(phil->forks[phil->r_fork]));
		say("%d %d has taken a fork\n", phil);
		pthread_mutex_lock(&(phil->forks[phil->l_fork]));
		say("%d %d has taken a fork\n", phil);
	}
	else
	{
		pthread_mutex_lock(&(phil->forks[phil->l_fork]));
		say("%d %d has taken a fork\n", phil);
		pthread_mutex_lock(&(phil->forks[phil->r_fork]));
		say("%d %d has taken a fork\n", phil);
	}
}

void	*behavior(void *philosoph)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosoph;
	while (philo->should_eat != 0)
	{
		pickup_forks(philo);
		philo->eating = 1;
		say("%d %d is eating\n", philo);
		philo->last_eaten = get_time();
		thread_sleep(philo->time_to_eat);
		pthread_mutex_unlock(&(philo->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->forks[philo->r_fork]));
		philo->eating = 0;
		say("%d %d is sleeping\n", philo);
		thread_sleep(philo->time_to_sleep);
		say("%d %d is thinking\n", philo);
		philo->should_eat--;
	}
	return (0);
}

int	say_philo_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->saying);
	printf("%d %d died\n", timestamp(philo), philo->index);
	return (0);
}

int	check_philos(t_settings *settings)
{
	int	i;
	int	checked_all;

	while (1)
	{
		i = -1;
		checked_all = 0;
		while (++i < settings->num_of_phil)
		{
			if (settings->philos[i]->should_eat == 0)
				continue ;
			checked_all = 1;
			if (settings->philos[i]->eating == 1)
				continue ;
			if (settings->time_to_die < get_time()
				- settings->philos[i]->last_eaten)
				return (say_philo_dead(settings->philos[i]));
		}
		if (checked_all == 0)
			return (1);
		usleep(1000);
	}
}

int	main(int argc, char const *argv[])
{
	t_settings	*settings;

	if (argc < 5 || argc > 6)
		return (0);
	settings = init_settings(argc, argv);
	if (!settings || !generate_philos(settings) || !create_threads(settings))
		return (0);
	if (check_philos(settings))
		destroy_philos(settings);
	else
		destroy_philos_without_free(settings);
	free(settings);
	return (1);
}
