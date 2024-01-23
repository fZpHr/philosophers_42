/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:28:31 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/22 20:01:24 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	routine(t_philo *p)
{
	int	i;

	i = 0;
	while (1 < 11)
	{
		if (i == 0)
		{
			pthread_mutex_lock(&p->forks[0]);
			printf("philo %d has taken a fork\n", p->id);
			pthread_mutex_lock(&p->forks[1]);
			printf("philo %d has taken a fork\n", p->id);
			printf("philo %d is eating\n", p->id);
			pthread_mutex_unlock(&p->forks[0]);
			pthread_mutex_unlock(&p->forks[1]);
			printf("philo %d is sleeping\n", p->id);
			printf("philo %d is thinking\n", p->id);
			i++;
		}
		else if (i == 1)
		{
			pthread_mutex_lock(&p->forks[1]);
			printf("philo %d has taken a fork\n", p->id);
			pthread_mutex_lock(&p->forks[0]);
			printf("philo %d has taken a fork\n", p->id);
			printf("philo %d is eating\n", p->id);
			pthread_mutex_unlock(&p->forks[1]);
			pthread_mutex_unlock(&p->forks[0]);
			printf("philo %d is sleeping\n", p->id);
			printf("philo %d is thinking\n", p->id);
			i--;
		}
	}
}

void	create_philo(t_philo *p, int nb_philo)
{
	int	i;

	*p = malloc(nb_philo * sizeof(t_philo));
	i = 0;
	while (i < p->ac - 1)
	{
		p[i].id = i;
		p[i].eat_count = 0;
		p[i].is_eating = 0;
		p[i].last_eat = 0;
		i++;
	}
	while (i < philo_nb)
	{
		pthread_create(&p[i].thread, NULL, (void *)routine, (void *)&p[i]);
		i++;
	}
}
void	philo(t_philo *p)
{
	pthread_t	t2;

	create_pholo(p);
	pthread_t t1; // faut creer des threads pour chaque philo
	if (pthread_create(&t1, NULL, (void *)routine, (void *)p))
		error_handle("pthread_create() error", 2);
	if (pthread_create(&t2, NULL, (void *)routine, (void *)p))
		error_handle("pthread_create() error", 2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

int	main(int argc, char **argv)
{
	t_philo p;

	init(&p);
	p.av = argv;
	p.ac = argc;
	if ((argc < 5 || argc > 6) || check_argv(argv, argc))
	{
		printf("\033[0;31mError: bad arguments\033[0m\n");
		return (1);
	}
	else
	{
		philo(&p);
		// free_end(&p, 0);
	}
	return (0);
}