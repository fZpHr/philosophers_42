/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:46:37 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/19 16:24:49 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	char			**av;
	int				ac;
	int				id;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	int				sleep;
	int				is_eating;
	long			last_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*eat;

}					t_philo;

int					check_argv(char **argv, int argc);
int					ft_atoi(const char *nptr);
int					ft_isdigit(int c);
void				init(t_philo *p);

#endif