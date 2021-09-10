/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/09 15:30:40 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/10 16:40:45 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_room
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					min_times_eat;
	int					position;
	int					philo_died;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	long long			start_time;
}	t_room;

typedef struct s_philo
{
	int				position;
	int				is_eating;
	int				times_eaten;
	long long		last_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_room			*room;
}	t_philo;

typedef enum e_errors
{
	invalid_args,
	wrong_args,
	malloc_fail,
	mutex_error
}	t_errors;

typedef enum e_states
{
	taken_fork,
	eating,
	sleeping,
	thinking,
	dead
}	t_states;

void		error_and_exit(int error);
int			ft_atoi(const char *str);
void		print_room(t_room *room);
t_room		*init_room(t_room *room, char *argv[]);
int			check_input(int argc, char *argv[]);
void		*ft_calloc(size_t blocks, size_t size);
void		create_room(t_room *room);
long long	get_timestamp(void);
long long	get_timediff(long long past, long long pres);
int			check_death(t_philo *philo, pthread_t *death);
t_philo		*create_philo(t_room *room, t_philo *philo);
void		*start_routine(void *ptr);
void		print_state(int state, t_philo *philo);
int			smartsleep(int ms, t_philo *philo);

#endif