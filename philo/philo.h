/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 11:31:57 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/21 15:11:45 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				position;
	int				is_eating;
	int				times_eaten;
	int				left_fork;
	int				right_fork;
	long long		last_eaten;
	struct s_room	*room;
	pthread_t		thread;
}	t_philo;

typedef struct s_room
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					min_times_eat;
	int					philo_died;
	int					satisfied;
	pthread_mutex_t		monitor;
	pthread_mutex_t		forks[201];
	t_philo				philos[201];
	long long			start_time;
}	t_room;

typedef enum e_errors
{
	invalid_args,
	wrong_args,
	malloc_fail,
	mutex_error,
	thread_error
}	t_errors;

typedef enum e_states
{
	taken_fork,
	eating,
	sleeping,
	thinking,
	dead
}	t_states;

int			check_input(int argc, char *argv[]);
int			ft_atoi(const char *str);
long long	get_timestamp(void);
long long	get_timediff(long long past, long long pres);
void		*ft_calloc(size_t blocks, size_t size);
void		*start_routine(void *ptr);
void		smartsleep(int ms, t_philo *philo);

t_room		*init_room(t_room *room, char *argv[]);

void		print_state(int state, t_philo *philo);
void		print_error(int error);

#endif