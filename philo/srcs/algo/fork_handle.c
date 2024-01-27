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

void select_fork(t_philo *p, int c_id, int cmd)
{
	int		left_fork;
	int		right_fork;

	left_fork = (c_id - 1) % p->nb_of_fork;
	right_fork = c_id  % p->nb_of_fork;
	if (left_fork > right_fork)
	{
		mutex_handle(&p->forks[right_fork], cmd);
		mutex_handle(&p->forks[left_fork], cmd);
	}
	else
	{
		mutex_handle(&p->forks[left_fork], cmd);
		mutex_handle(&p->forks[right_fork], cmd);
	}
}

void	fork_handle(t_philo *p, int c_id, int cmd)
{
	if (cmd == 3)
		select_fork(p, c_id, cmd);
	else if (cmd == 4)
		select_fork(p, c_id, cmd);
}