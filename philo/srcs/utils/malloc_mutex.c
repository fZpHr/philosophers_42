/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:06:11 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/22 18:28:29 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*malloc_handle(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_handle("malloc() error", 1);
	return (ptr);
}

void	*mutex_handle(pthread_mutex_t *mutex, int function_nb)
{
	int status;

	if (function_nb == 1)
	{
		status = pthread_mutex_init(mutex, NULL);
		if (status != 0)
			mutex_error(status);
	}
	else if (function_nb == 2)
	{
		status = pthread_mutex_destroy(mutex);
		if (status != 0)
			mutex_error(status);
	}
	else if (function_nb == 3)
	{
		status = pthread_mutex_lock(mutex);
		if (status != 0)
			mutex_error(status);
	}
	else if (function_nb == 4)
	{
		status = pthread_mutex_unlock(mutex);
		if ((status != 0))
			mutex_error(status);
	}
	return (mutex);
}