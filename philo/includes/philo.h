/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:46:37 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/26 18:04:58 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_philo
{
	pthread_mutex_t	lock;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
	pthread_mutex_t	monitor;
	pthread_mutex_t	*forks;
	pthread_t		*philosopher_threads;
	pthread_t		monitor_thread_id;
	long int		nb_of_philo;
	long int		nb_of_fork;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	long int		nb_of_meals;
	int				ok;
	uint64_t		*last_meal;
	int				id;
	char			**av;
	int				ac;

}					t_philo;

int					check_argv(char **argv, int argc);
int					ft_atoi(const char *nptr);
void				printf_handle(char *str, t_philo *p, uint64_t a, uint64_t b);
int					ft_isdigit(int c);
void				init(t_philo *p);
void				mutex_error(int status);
void				error_handle(char *str, int exit_status);
int					ft_usleep(size_t milliseconds);
void				*mutex_handle(pthread_mutex_t *mutex, int function_nb);
size_t				get_current_time(void);
void				free_end(t_philo *p);
#endif