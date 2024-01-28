/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:15:45 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/27 14:15:45 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	increment_id(t_philo *p, int *c_id) 
{
    usleep(50);
    pthread_mutex_lock(&p->lock);
    p->id++;
    *c_id = p->id;
    pthread_mutex_unlock(&p->lock);
}

void	initialize_variables(int *i, int *think, int *eat_count, uint64_t *start) 
{
    *i = 0;
    *think = 0;
    *eat_count = 0;
    *start = get_current_time();
}

void	update_last_meal(t_philo *p, int c_id) 
{
    pthread_mutex_lock(&p->meal);
    p->last_meal[c_id] = get_current_time();
    pthread_mutex_unlock(&p->meal);
}

void	routine(t_philo *p)
{
	int			i;
	int			eat_count;
	int			c_id;
	int			think;
	uint64_t	start;

	increment_id(p, &c_id);
	initialize_variables(&i, &think, &eat_count, &start);
	update_last_meal(p, c_id);
	while (1)
	{
		if (i % 2 == 0)
			usleep(10);
		if (handle_eating_and_sleeping(p, &eat_count, c_id, start) == 1)
			break ;
		if (handle_thinking(p, &think, start, c_id) == 1)
			break ;
		if (handle_meal_finish(p, eat_count) == 1)
			break ;
		i++;
	}
}
