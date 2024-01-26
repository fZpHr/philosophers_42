/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:28:31 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/26 18:06:03 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	monitor_thread_death(t_philo *p) 
{
	int i;
	
	i = 1;
    while (1) 
	{
		mutex_handle(&p->meal, 3);
        if (get_current_time() - p->last_meal[i] > p->time_to_die) 
		{
			mutex_handle(&p->meal, 4);
			mutex_handle(&p->print, 3);
			printf("\033[0;31m%ld %d died\n\033[00m", (get_current_time() - p->last_meal[i]) , i);
			mutex_handle(&p->print, 4);
            exit(1);
        }
		mutex_handle(&p->meal, 4);
		if (p->ok == 1)
			break ;
		if (i == p->nb_of_philo)
			i = 1;
        usleep(10);
    }
}

void	create_fork(t_philo *p)
{
	int	i;

	i = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nb_of_fork);
	if (!p->forks)
		error_handle("malloc() error", 1);
	while (i < p->nb_of_fork)
	{
		mutex_handle(&p->forks[i], 1);
		i++;
	}
}

int	fork_handle(t_philo *p, int c_id, int cmd)
{
	int		left_fork;
	int		right_fork;

	left_fork = (c_id - 1) % p->nb_of_fork;
	right_fork = c_id  % p->nb_of_fork;
	if (cmd == 3)
	{
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
	else if (cmd == 4)
	{
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
	return (0);
}

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
			printf_handle("%ld %d has taken a fork\n", p, start, c_id);
			printf_handle("%ld %d has taken a fork\n", p, start, c_id);
			printf_handle("%ld %d is eating\n", p, start, c_id);
			ft_usleep(p->time_to_eat);
			eat_count++;
			mutex_handle(&p->meal, 3);
			p->last_meal[c_id] = get_current_time();
			mutex_handle(&p->meal, 4);
			fork_handle(p, c_id, 4);
			printf_handle("%ld %d is sleeping\n", p, start, c_id);
			ft_usleep(p->time_to_sleep);
		}
		if (think == 0)
		{
			printf_handle("%ld %d is thinking\n", p, start, c_id);
			think = 1;
		}
		if (p->nb_of_meals != -1 && eat_count == p->nb_of_meals)
		{
			p->ok = 1;
			break ;
		}
		i++;
	}
}

void	test(t_philo *p)
{
	int	i;
	int	c_id;

	mutex_handle(&p->lock, 3);
	p->id++;
	c_id = p->id;
	mutex_handle(&p->lock, 4);
	i = 0;
	while (i < 5)
	{
		printf("%d %d test%d : \n", c_id, i, c_id);
		i++;
	}
}

void	create_philo(t_philo *p)
{
	int	i;

	i = 0;
	p->philosopher_threads = malloc(sizeof(pthread_t) * p->nb_of_philo);
	if (!p->philosopher_threads)
		error_handle("malloc() error", 1);
	while (i < p->nb_of_philo)
	{
		pthread_create(&p->philosopher_threads[i], NULL, (void *)routine,
			(void *)p);
		i++;
	}
	usleep(100);
	pthread_create(&p->monitor_thread_id, NULL, (void *)monitor_thread_death, (void*)p);
}

void	join_philo(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		pthread_join(p->philosopher_threads[i], NULL);
		i++;
	}
	pthread_join(p->monitor_thread_id, NULL);
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
		//free_end(&p);
	}
	return (0);
}