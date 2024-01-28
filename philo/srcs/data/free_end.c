/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:44:11 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/24 15:19:31 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	free_end(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_fork)
	{
		pthread_mutex_destroy(&p->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&p->lock);
	pthread_mutex_destroy(&p->monitor);
	pthread_mutex_destroy(&p->print);
	pthread_mutex_destroy(&p->meal);
	pthread_mutex_destroy(&p->meal_finishm);
	pthread_mutex_destroy(&p->finishm);
	free(p->forks);
	free(p->last_meal);
	free(p->philosopher_threads);
}
