<<<<<<< Updated upstream
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
=======
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

void	error_handle(char *str, int exit_status)
{
	printf("\033[0;31m%s\033[00m\n", str);
	if (exit_status == 1)
		exit(1);
	else if (exit_status == 2)
		exit(2);
	else
		exit(0);
}

void	mutex_error(int status)
{
	if (status == EINVAL)
		error_handle("The value specified by mutex is invalid or by attr is invalid",
			2);
	else if (status == EDEADLK)
		error_handle("A deadlock would occur if the thread blocked waiting for the mutex",
			2);
	else if (status == ENOMEM)
		error_handle("The process does not have enough memory to create another mutex",
			2);
	else if (status == EBUSY)
		error_handle("Mutex is already locked", 2);
	else if (status == EPERM)
		error_handle("The current thread does not hold a lock on mutex", 2);
	else
		error_handle("pthread_mutex_init() error", 2);
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
>>>>>>> Stashed changes
}