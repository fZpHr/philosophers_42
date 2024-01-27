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
	mutex_handle(&p->meal, 4);
	mutex_handle(&p->meal, 3);
	mutex_handle(&p->print, 3);
	printf("\033[0;31m%ld %d died\n\033[00m", (get_current_time() - p->last_meal[i]) , i);
	mutex_handle(&p->print, 4);
	mutex_handle(&p->meal, 4);
	mutex_handle(&p->finishm, 3);
	p->finish = 1;
	mutex_handle(&p->finishm, 4);
}

void	monitor_thread_death(t_philo *p) 
{
	int i;
	
	i = 1;
    while (1) 
	{
		mutex_handle(&p->meal, 3);
        if (get_current_time() - p->last_meal[i] > p->time_to_die) 
        {
            to_late(p, i);
            break ;
        }
		mutex_handle(&p->meal, 4);
		mutex_handle(&p->meal_finishm, 3);
		if (p->meal_finish == 1)
		{
			mutex_handle(&p->meal_finishm, 4);
			break ;
		}
		mutex_handle(&p->meal_finishm, 4);
		if (i == p->nb_of_philo)
			i = 1;
		else
			i++;
        ft_usleep(5);
    }
}

