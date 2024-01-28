/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 03:29:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/27 03:29:42 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void select_fork(t_philo *p, int c_id)
{
	int		left_fork;
	int		right_fork;

	left_fork = (c_id - 1) % p->nb_of_fork;
	right_fork = c_id  % p->nb_of_fork;
	if (left_fork > right_fork)
	{
		pthread_mutex_lock(&p->forks[right_fork]);
		pthread_mutex_lock(&p->forks[left_fork]);
	}
	else
	{
		pthread_mutex_lock(&p->forks[left_fork]);
		pthread_mutex_lock(&p->forks[right_fork]);
	}
}

void	unlock_fork(t_philo *p, int c_id)
{
	int		left_fork;
	int		right_fork;

	left_fork = (c_id - 1) % p->nb_of_fork;
	right_fork = c_id  % p->nb_of_fork;
	if (left_fork > right_fork)
	{
		pthread_mutex_unlock(&p->forks[right_fork]);
		pthread_mutex_unlock(&p->forks[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&p->forks[left_fork]);
		pthread_mutex_unlock(&p->forks[right_fork]);
	}
}

void	fork_handle(t_philo *p, int c_id, int cmd)
{
	if (cmd == 3)
		select_fork(p, c_id);
	else if (cmd == 4)
		unlock_fork(p, c_id);
}