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