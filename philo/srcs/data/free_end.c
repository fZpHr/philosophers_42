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
		mutex_handle(&p->forks[i], 2);
		i++;
	}
	mutex_handle(&p->lock, 2);
	mutex_handle(&p->monitor, 2);
	mutex_handle(&p->print, 2);
	mutex_handle(&p->meal, 2);
	mutex_handle(&p->meal_finishm, 2);
	mutex_handle(&p->finishm, 2);
	free(p->forks);
	free(p->last_meal);
	free(p->philosopher_threads);
}