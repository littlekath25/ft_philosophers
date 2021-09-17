/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/17 13:46:54 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/17 16:59:10 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

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
	sem_t				forks[200];
	t_philo				philos[200];
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
void		*ft_calloc(size_t blocks, size_t size);
long long	get_timediff(long long past, long long pres);
long long	get_timestamp(void);

t_room		*init_room(t_room *room, char *argv[]);

void		print_state(int state, t_philo *philo);
void		print_error(int error);

#endif