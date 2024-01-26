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

void	printf_handle(char *str, t_philo *p, uint64_t a, uint64_t b)
{
	mutex_handle(&p->print, 3);
	printf(str, get_current_time() - a, b);
	mutex_handle(&p->print, 4);
}