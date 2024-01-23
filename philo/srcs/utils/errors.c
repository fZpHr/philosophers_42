/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:09:12 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/22 18:04:40 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	error_handle(char *str, int exit_status)
{
	printf("%s\n", str);
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