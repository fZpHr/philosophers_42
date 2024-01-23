/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:44:11 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/23 15:49:35 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	free_end(t_philo *p)
{
	int i;

	i = 0;
	/*while (i < p->nb_of_philo)
	{
		pthread_mutex_destroy(&p->l_forks[i]);
		pthread_mutex_destroy(&p->r_forks[i]);
		i++;
	}*/
	// pthread_mutex_destroy(&p->lock);
	free(p->philosopher_threads);
	/*free(p->l_forks);
	free(p->r_forks);*/
	exit(0);
}