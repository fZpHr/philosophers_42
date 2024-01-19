/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:28:31 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/19 18:48:48 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	philo(t_philo *p)
{
	while (1)
	{
		if (p->is_eating)
		{
			printf("philo %d is eating\n", p->id);
			p->is_eating = 0;
			p->eat_count++;
		}
		else
		{
			printf("philo %d is thinking\n", p->id);
			p->is_eating = 1;
		}
		if (p->is_eating == 0)
			usleep(p->sleep * 1000);
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo p;
	_uint64_t start;
	__uint64_t end;

	init(&p);
	p.av = argv;
	p.ac = argc;
	start = printf("time : %zu\n", get_current_time());
	usleep(100000);
	end = printf("time : %zu\n", get_current_time());
	printf("time : %d\n", end - start);
	if ((argc < 5 || argc > 6) || check_argv(argv, argc))
	{
		printf("\033[0;31mError: bad arguments\033[0m\n");
		return (1);
	}
	else
	{
		// free_end(&p, 0);
	}
	return (0);
}