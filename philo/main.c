/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:28:31 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/24 17:41:14 by hbelle           ###   ########.fr       */
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
void	fork_handle(t_philo *p, int c_id, int cmd)
{
	int	cur;

	if (c_id == p->nb_of_philo)
	{
		cur = c_id + 1;
		mutex_handle(&p->forks[cur], cmd);
		mutex_handle(&p->forks[0], cmd);
	}
	else
	{
		cur = c_id + 1;
		mutex_handle(&p->forks[cur], cmd);
		mutex_handle(&p->forks[cur + 1], cmd);
	}
}

void	routine(t_philo *p)
{
	int	i;
	int	eat_count;
	int	c_id;

	mutex_handle(&p->lock, 3);
	p->id++;
	c_id = p->id;
	mutex_handle(&p->lock, 4);
	i = 0;
	eat_count = 0;
	p->start = get_current_time();
	while (1)
	{
		if (i % 2 == 0)
			printf("%ld %d is thinking\n", get_current_time() - p->start, c_id);
		else if (eat_count != p->nb_of_meals && p->nb_of_fork > 1)
		{
			mutex_handle(&p->lock, 3);
			fork_handle(p, c_id, 3);
			printf("%ld %d has taken a fork\n", get_current_time() - p->start,
				c_id);
			printf("%ld %d has taken a fork\n", get_current_time() - p->start,
				c_id);
			printf("%ld %d is eating\n", get_current_time() - p->start, c_id);
			eat_count++;
			ft_usleep(p->time_to_eat);
			p->nb_of_fork += 2;
			fork_handle(p, c_id, 4);
			mutex_handle(&p->lock, 4);
			printf("%ld %d is sleeping\n", get_current_time() - p->start, c_id);
			ft_usleep(p->time_to_sleep);
		}
		if (get_current_time() - p->start > p->time_to_die)
		{
			printf("%ld %d died\n", get_current_time() - p->start, c_id);
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
		free_end(&p);
	}
	return (0);
}