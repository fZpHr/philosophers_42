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
	long int i;

	i = 0;
	while (i < p->nb_of_philo)
		mutex_handle(&p->forks[i++], 2);
	mutex_handle(&p->lock, 2);
	free(p->philosopher_threads);
	free(p->forks);
	exit(0);
}