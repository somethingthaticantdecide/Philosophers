#include "philo_three.h"

t_settings	*init_settings(int argc, const char **argv)
{
	t_settings	*settings;

	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (0);
	settings->start_time = get_time();
	settings->num_of_phil = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		settings->should_eat = ft_atoi(argv[5]);
	else
		settings->should_eat = -2;
	if (settings->num_of_phil <= 0 || settings->time_to_die <= 0
		|| settings->time_to_eat <= 0 || settings->time_to_sleep <= 0
		|| settings->should_eat == -1 || settings->should_eat == 0)
	{
		free(settings);
		return (0);
	}
	return (settings);
}

int	create_threads(t_settings *settings)
{
	int			i;

	i = 0;
	while (i < settings->num_of_phil)
	{
		settings->philos[i]->fork_id = fork();
		if (settings->philos[i]->fork_id == 0)
		{
			pthread_create(&settings->thread, NULL, behavior,
				(void *)settings->philos[i]);
			pthread_detach(settings->thread);
			check_philos(settings->philos[i]);
			exit(1);
		}
		i++;
	}
	return (1);
}

t_philosopher	*create_phil(t_settings *settings, int i)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!phil)
		return (NULL);
	phil->start_time = settings->start_time;
	phil->index = i + 1;
	phil->l_fork = i;
	phil->r_fork = i + 1;
	if (i == settings->num_of_phil - 1)
		phil->r_fork = 0;
	phil->last_eaten = settings->start_time;
	phil->time_to_eat = settings->time_to_eat;
	phil->time_to_sleep = settings->time_to_sleep;
	phil->should_eat = settings->should_eat;
	phil->forks = settings->forks;
	phil->saying = settings->saying;
	phil->dl_crutch = settings->dl_crutch;
	phil->eating = 0;
	phil->time_to_die = settings->time_to_die;
	return (phil);
}

int	generate_philos(t_settings *settings)
{
	int	i;

	settings->philos = malloc(sizeof(t_philosopher *) * settings->num_of_phil);
	if (!settings->philos || !settings->forks)
		return (0);
	i = 0;
	while (i < settings->num_of_phil)
	{
		settings->philos[i] = create_phil(settings, i);
		if (!settings->philos[i])
			return (0);
		i++;
	}
	return (1);
}
