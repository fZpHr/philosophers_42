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

	int i = 0;
	
	if ((argc < 5 || argc > 6) || check_argv(argv, argc))
	{
		printf("Error: bad arguments\n");
		return (1);
	}
	else
	{
		p.av = argv;
		p.ac = argc;
		if (init(&p) == 1)
			return (1);
		if (create_fork(&p) == 1)
			return (1);
		if (create_philo(&p) == 1)
			return (1);
		join_philo(&p);
		free_end(&p);
	}
	return (0);
}