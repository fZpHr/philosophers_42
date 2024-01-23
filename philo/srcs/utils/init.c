/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:32:00 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/23 17:20:37 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init(t_philo *p)
{
	p->id = 0;
	p->nb_of_philo = ft_atoi(p->av[1]);
	p->nb_of_fork = p->nb_of_philo;
	p->time_to_die = ft_atoi(p->av[2]);
	p->time_to_eat = ft_atoi(p->av[3]);
	p->time_to_sleep = ft_atoi(p->av[4]);
	if (p->av[5])
		p->nb_of_meals = ft_atoi(p->av[5]);
	else
		p->nb_of_meals = -1;
}