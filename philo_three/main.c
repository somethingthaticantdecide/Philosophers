#include "philo_three.h"

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

int	check_philos(t_philosopher *philosoph)
{
	while (1)
	{
		if (philosoph->eating == 1)
			continue ;
		if (get_time() - philosoph->last_eaten > philosoph->time_to_die)
		{
			sem_wait(philosoph->saying);
			printf("%d %d died\n", timestamp(philosoph), philosoph->index);
			exit(1);
		}
		if (philosoph->should_eat == 0)
			exit(0);
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
	settings->forks = sem_open("/forks",
			O_CREAT, S_IRUSR | S_IWUSR, settings->num_of_phil);
	settings->saying = sem_open("/saying", O_CREAT, S_IRUSR | S_IWUSR, 1);
	settings->saying = sem_open("/dl_crutch", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (!settings || !generate_philos(settings) || !create_threads(settings))
		return (0);
	destroy_philos(settings);
	return (1);
}
