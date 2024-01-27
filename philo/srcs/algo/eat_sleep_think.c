/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:24:49 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/27 16:24:49 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int handle_eating_and_sleeping(t_philo *p, int *eat_count, int c_id, uint64_t start)
{
    if (*eat_count != p->nb_of_meals && p->nb_of_fork > 1)
    {
        fork_handle(p, c_id, 3);
        if (printf_handle("%ld %d has taken a fork\n", p, start, c_id) == 1 ||
            printf_handle("%ld %d has taken a fork\n", p, start, c_id) == 1 ||
            printf_handle("%ld %d is eating\n", p, start, c_id) == 1)
        {
            fork_handle(p, c_id, 4);
            return 1;
        }
        ft_usleep(p->time_to_eat);
        (*eat_count)++;
        mutex_handle(&p->meal, 3);
        p->last_meal[c_id] = get_current_time();
        mutex_handle(&p->meal, 4);
        fork_handle(p, c_id, 4);
        if (printf_handle("%ld %d is sleeping\n", p, start, c_id) == 1)
            return 1;
        ft_usleep(p->time_to_sleep);
    }
    return 0;
}

int handle_thinking(t_philo *p, int *think, uint64_t start, int c_id)
{
    if (*think == 0)
    {
        if (printf_handle("%ld %d is thinking\n", p, start, c_id) == 1)
            return 1;
        *think = 1;
    }
    return 0;
}

int handle_meal_finish(t_philo *p, int eat_count)
{
    if (p->nb_of_meals != -1 && eat_count == p->nb_of_meals)
    {
        mutex_handle(&p->meal_finishm, 3);
        p->meal_finish = 1;
        mutex_handle(&p->meal_finishm, 4);
        return 1;
    }
    return 0;
}