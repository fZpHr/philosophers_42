/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:54:17 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/25 13:47:19 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_if_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_argv(char **argv, int argc)
{
	if (check_if_digit(argv))
		return (1);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[2]) < 1)
		return (1);
	if (ft_atoi(argv[3]) < 1)
		return (1);
	if (ft_atoi(argv[4]) < 1)
		return (1);
	if (argc > 5)
		if (ft_atoi(argv[5]) < 0)
			return (1);
	return (0);
}