/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:28:31 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/25 19:57:41 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	create_fork(t_philo *p)
{
	int	i;

	i = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nb_of_fork);
	if (!p->forks)
		error_handle("malloc() error", 1);
	while (i < p->nb_of_fork)
	{
		pthread_mutex_init(&p->forks[i], NULL);
		i++;
	}
}

int	fork_handle(t_philo *p, int c_id, int cmd, uint64_t last_meal)
{
	int		left_fork;
	int		right_fork;
	//uint64_t	waiting;
	//uint64_t	time_last_meal;
	
	
	left_fork = (c_id - 1) % p->nb_of_fork;
	right_fork = c_id  % p->nb_of_fork;
	if (cmd == 3)
	{
		//waiting = get_current_time() - last_meal;   1000 1100     10
		//time_last_meal = waiting + last_meal;
		if (left_fork > right_fork)
		{
			mutex_handle(&p->forks[right_fork], cmd);
			mutex_handle(&p->forks[left_fork], cmd);
			if (get_current_time() - last_meal > p->time_to_die)
				return (1);
		}
		else
		{
			mutex_handle(&p->forks[left_fork], cmd);
			mutex_handle(&p->forks[right_fork], cmd);
			if ((get_current_time() - last_meal > p->time_to_die))
				return (1);
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
	uint64_t start;
	uint64_t last_meal;

	usleep(10);
	mutex_handle(&p->lock, 3);
	p->id++;
	c_id = p->id;
	mutex_handle(&p->lock, 4);
	i = 0;
	eat_count = 0;
	start = get_current_time();
	last_meal = get_current_time();
	while (1)
	{
		if (i % 2 == 0)
			usleep(10);
		if (eat_count != p->nb_of_meals && p->nb_of_fork > 1)
		{
			if ((fork_handle(p, c_id, 3, last_meal) == 1))
			{
				fork_handle(p, c_id, 4, last_meal);
				printf("\033[0;31m%ld %d died\n\033[00m", get_current_time() - start, c_id);
				break;
			}
			if (get_current_time() - last_meal > p->time_to_die)
			{
				fork_handle(p, c_id, 4, last_meal);
				printf("\033[0;31m%ld %d died\n\033[00m", get_current_time() - start, c_id);
				break ;
			}
			else
			{
				printf("%ld %d has taken a fork\n", get_current_time() - start,
				c_id);
				printf("%ld %d has taken a fork\n", get_current_time() - start,
				c_id);
				printf("%ld %d is eating\n", get_current_time() - start, c_id);
				ft_usleep(p->time_to_eat);
				eat_count++;
				last_meal = get_current_time();
			}
			fork_handle(p, c_id, 4, last_meal);
			if (get_current_time() - last_meal > p->time_to_die)
			{
				printf("\033[0;31m%ld %d died\n\033[00m", get_current_time() - start, c_id);
				break ;
			}
		}
		printf("%ld %d is sleeping\n", get_current_time() - start, c_id);
		ft_usleep(p->time_to_sleep);
		printf("%ld %d is thinking\n", get_current_time() - start, c_id);
		if (get_current_time() - last_meal > p->time_to_die)
		{
			printf("\033[0;31m%ld %d died\n\033[00m", get_current_time() - start, c_id);
			break ;
		}
		if (p->nb_of_meals != -1 && eat_count == p->nb_of_meals)
			break ;
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
}

int	main(int argc, char **argv)
{
	t_philo p;

	if ((argc < 5 || argc > 6) || check_argv(argv, argc))
	{
		error_handle("Error: bad arguments,Usage [INT > 1] [0 > INT =< 200] [INT > 0] [INT >= 0] [OPTIONAL INT >= 0]",
			1);
		return (1);
	}
	else
	{
		p.av = argv;
		p.ac = argc;
		init(&p);
		mutex_handle(&p.lock, 1);
		create_fork(&p);
		create_philo(&p);
		join_philo(&p);
		//free_end(&p);
	}
	return (0);
}