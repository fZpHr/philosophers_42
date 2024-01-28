/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 03:15:39 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/27 03:15:39 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void    to_late(t_philo *p, int i)
{
	pthread_mutex_unlock(&p->meal);
	pthread_mutex_lock(&p->meal);
	pthread_mutex_lock(&p->print);
	printf("\033[0;31m%ld %d died\n\033[00m", (get_current_time() - p->last_meal[i]) , i);
	pthread_mutex_unlock(&p->print);
	pthread_mutex_unlock(&p->meal);
	pthread_mutex_lock(&p->finishm);
	p->finish = 1;
	pthread_mutex_unlock(&p->finishm);
}

void	monitor_thread_death(t_philo *p) 
{
	int i;
	
	i = 1;
    while (1) 
	{
		pthread_mutex_lock(&p->meal);
        if (get_current_time() - p->last_meal[i] > p->time_to_die) 
        {
            to_late(p, i);
            break ;
        }
		pthread_mutex_unlock(&p->meal);
		pthread_mutex_lock(&p->meal_finishm);
		if (p->meal_finish == 1)
		{
			pthread_mutex_unlock(&p->meal_finishm);
			break ;
		}
		pthread_mutex_unlock(&p->meal_finishm);
		if (i == p->nb_of_philo)
			i = 1;
		else
			i++;
        ft_usleep(5);
    }
}

