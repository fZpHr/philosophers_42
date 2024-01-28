/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:18:47 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/26 16:29:38 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	printf_handle(char *str, t_philo *p, uint64_t a, uint64_t b)
{
	pthread_mutex_lock(&p->finishm);
	if (p->finish == 1)
	{
		pthread_mutex_unlock(&p->finishm);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&p->finishm);
		pthread_mutex_lock(&p->print);
		printf(str, get_current_time() - a, b);
		pthread_mutex_unlock(&p->print);
		return (0);
	}
}
