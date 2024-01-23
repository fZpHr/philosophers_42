/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:46:37 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/22 18:40:26 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_status
{
	DEAD,
	ALIVE
};
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
void				mutex_error(int status);
void				error_handle(char *str, int exit_status);
int					ft_usleep(size_t milliseconds);
void				*mutex_handle(pthread_mutex_t *mutex, int function_nb);

#endif