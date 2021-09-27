/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 11:31:57 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/27 14:05:23 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <errno.h>

# define DEATH_EXIT 3

typedef struct s_philo
{
	int				position;
	int				is_eating;
	int				times_eaten;
	long long		last_eaten;
	struct s_room	*room;
	pid_t			id;
	pthread_t		monitor;
}	t_philo;

typedef struct s_room
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					min_times_eat;
	int					philo_died;
	sem_t				monitor;
	sem_t				*forks;
	t_philo				philos[201];
	long long			start_time;
	sem_t				*print;
}	t_room;

typedef enum e_errors
{
	invalid_args,
	wrong_args,
	malloc_fail,
	semaphore_error,
	fork_error
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
void		start_routine(t_philo *philo);
void		smartsleep(int ms, t_philo *philo);
t_room		*init_room(t_room *room, char *argv[]);
void		print_state(int state, t_philo *philo);
void		print_error(int error);
sem_t		*create_semaphore(char *name, int i);

#endif