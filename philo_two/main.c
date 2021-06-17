#include "philo_two.h"

void	*behavior(void *philosoph)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosoph;
	while (philo->should_eat != 0)
	{
		sem_wait(philo->dl_crutch);
		sem_wait(philo->forks);
		say("%d %d has taken a fork\n", philo);
		sem_wait(philo->forks);
		say("%d %d has taken a fork\n", philo);
		sem_post(philo->dl_crutch);
		philo->eating = 1;
		say("%d %d is eating\n", philo);
		philo->last_eaten = get_time();
		thread_sleep(philo->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
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
	sem_wait(philo->saying);
	printf("%d %d died\n", timestamp(philo), philo->index);
	return (1);
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
			if (settings->phil[i]->should_eat == 0)
				continue ;
			checked_all = 1;
			if (settings->phil[i]->eating == 1)
				continue ;
			if (settings->time_to_die < get_time()
				- settings->phil[i]->last_eaten)
				return (say_philo_dead(settings->phil[i]));
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
	sem_unlink("/forks");
	sem_unlink("/saying");
	sem_unlink("/dl_crutch");
	settings->forks = sem_open("/forks", O_CREAT, S_IRUSR
			| S_IWUSR, settings->num_of_phil);
	settings->saying = sem_open("/saying", O_CREAT, S_IRUSR | S_IWUSR, 1);
	settings->dl_crutch = sem_open("/dl_crutch", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (!settings || !generate_philos(settings) || !create_threads(settings))
		return (0);
	check_philos(settings);
	destroy_philos(settings);
	free(settings);
	return (1);
}
