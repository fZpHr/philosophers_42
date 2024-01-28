/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:32:00 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/26 18:11:26 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init_mutex(t_philo *p)
{
	pthread_mutex_init(&p->lock, NULL);
	pthread_mutex_init(&p->monitor, NULL);
	pthread_mutex_init(&p->print, NULL);
	pthread_mutex_init(&p->meal, NULL);
	pthread_mutex_init(&p->meal_finishm, NULL);
	pthread_mutex_init(&p->finishm, NULL);
}

void	destroy_mutex(t_philo *p)
{
	pthread_mutex_destroy(&p->lock);
	pthread_mutex_destroy(&p->monitor);
	pthread_mutex_destroy(&p->print);
	pthread_mutex_destroy(&p->meal);
	pthread_mutex_destroy(&p->meal_finishm);
	pthread_mutex_destroy(&p->finishm);
}

void	destroy_mutex_fork(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_fork)
	{
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
}

int	init(t_philo *p)
{
	p->id = 0;
	init_mutex(p);
	p->finish = 0;
	p->meal_finish = 0;
	p->nb_of_philo = ft_atoi(p->av[1]);
	p->nb_of_fork = p->nb_of_philo;
	p->time_to_die = ft_atoi(p->av[2]);
	p->time_to_eat = ft_atoi(p->av[3]);
	p->time_to_sleep = ft_atoi(p->av[4]);
	p->last_meal = malloc(sizeof(uint64_t) * (p->nb_of_philo + 1));
	if (!p->last_meal)
	{
		destroy_mutex(p);
		printf("malloc() error");
		return (1);
	}
	if (p->av[5])
		p->nb_of_meals = ft_atoi(p->av[5]);
	else
		p->nb_of_meals = -1;
	return (0);
}
