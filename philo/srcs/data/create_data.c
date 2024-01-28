/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 03:24:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/27 03:24:21 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	create_philo(t_philo *p)
{
	int	i;

	i = 0;
	p->philosopher_threads = malloc(sizeof(pthread_t) * p->nb_of_philo);
	if (!p->philosopher_threads)
	{
		printf("malloc() error");
		destroy_mutex(p);
		destroy_mutex_fork(p);
		free(p->last_meal);
		free(p->forks);
		return (1);
	}
	while (i < p->nb_of_philo)
	{
		pthread_create(&p->philosopher_threads[i], NULL, (void *)routine,
			(void *)p);
		i++;
	}
	usleep(10);
	pthread_create(&p->monitor_thread_id, NULL,
		(void *)monitor_thread_death, (void*)p);
	return (0);
}

int	create_fork(t_philo *p)
{
	int	i;

	i = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nb_of_fork);
	if (!p->forks)
	{
		printf("malloc() error");
		destroy_mutex(p);
		free(p->last_meal);
		return (1);
	}
	while (i < p->nb_of_fork)
	{
		pthread_mutex_init(&p->forks[i], NULL);
		i++;
	}
	return (0);
}

void	join_philo(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		pthread_join(p->philosopher_threads[i], NULL);
		i++;
	}
	pthread_join(p->monitor_thread_id, NULL);
}
