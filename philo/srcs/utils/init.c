/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:32:00 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/26 18:06:04 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init(t_philo *p)
{
	p->id = 0;
	mutex_handle(&p->lock, 1);
	mutex_handle(&p->monitor, 1);
	mutex_handle(&p->print, 1);
	mutex_handle(&p->meal, 1);
	p->ok = 0;
	p->nb_of_philo = ft_atoi(p->av[1]);
	p->nb_of_fork = p->nb_of_philo;
	p->time_to_die = ft_atoi(p->av[2]);
	p->time_to_eat = ft_atoi(p->av[3]);
	p->time_to_sleep = ft_atoi(p->av[4]);
	p->last_meal = malloc(sizeof(uint64_t) * (p->nb_of_philo + 1));
	if (!p->last_meal)
		error_handle("malloc() error", 1);
	if (p->av[5])
		p->nb_of_meals = ft_atoi(p->av[5]);
	else
		p->nb_of_meals = -1;
}