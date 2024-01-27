/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:28:31 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/26 19:05:37 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	routine(t_philo *p)
{
	int	i;
	int	eat_count;
	int	c_id;
	int think;
	uint64_t start;

	usleep(50);
	mutex_handle(&p->lock, 3);
	p->id++;
	c_id = p->id;
	mutex_handle(&p->lock, 4);
	i = 0;
	think = 0;
	eat_count = 0;
	start = get_current_time();
	mutex_handle(&p->meal, 3);
	p->last_meal[c_id] = get_current_time();
	mutex_handle(&p->meal, 4);
	while (1)
	{
		if (i % 2 == 0)
			usleep(10);
		if (eat_count != p->nb_of_meals && p->nb_of_fork > 1)
		{
			think = 0;
			fork_handle(p, c_id, 3);
			if (printf_handle("%ld %d has taken a fork\n", p, start, c_id) == 1)
			{
				fork_handle(p, c_id, 4);
				break ;
			}
			if (printf_handle("%ld %d has taken a fork\n", p, start, c_id) == 1)
			{
				fork_handle(p, c_id, 4);
				break ;
			}
			if (printf_handle("%ld %d is eating\n", p, start, c_id) == 1)
			{
				fork_handle(p, c_id, 4);
				break ;
			}
			ft_usleep(p->time_to_eat);
			eat_count++;
			mutex_handle(&p->meal, 3);
			p->last_meal[c_id] = get_current_time();
			mutex_handle(&p->meal, 4);
			fork_handle(p, c_id, 4);
			if (printf_handle("%ld %d is sleeping\n", p, start, c_id) == 1)
				break ;
			ft_usleep(p->time_to_sleep);
		}
		if (think == 0)
		{
			if (printf_handle("%ld %d is thinking\n", p, start, c_id) == 1)
				break ;
			think = 1;
		}
		if (p->nb_of_meals != -1 && eat_count == p->nb_of_meals)
		{
			mutex_handle(&p->meal_finishm, 3);
			p->meal_finish = 1;
			mutex_handle(&p->meal_finishm, 4);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo p;

	if ((argc < 5 || argc > 6) || check_argv(argv, argc))
	{
		error_handle("Error: bad arguments,Usage [INT > 0] [0 > INT =< 200] [INT > 0] [INT >= 0] [OPTIONAL INT >= 0]",
			1);
		return (1);
	}
	else
	{
		p.av = argv;
		p.ac = argc;
		init(&p);
		create_fork(&p);
		create_philo(&p);
		join_philo(&p);
		free_end(&p);
	}
	return (0);
}