/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/09 15:30:40 by katherine     #+#    #+#                 */
/*   Updated: 2021/08/25 16:04:57 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	position;
	int	*left_fork;
	int	*right_fork;
}	t_philo;

typedef struct s_room
{
	int			num_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			min_times_eat;
	t_philo		*philos;
	int			*forks;
	pthread_t	*threads;
}	t_room;

typedef enum e_errors
{
	invalid_args,
	wrong_args,
	malloc_fail
}	t_errors;

void	error_and_exit(int error);
int		ft_isspace(int c);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isalldigits(char *str);
void	print_room(t_room *room);
t_room	*init_room(t_room *room, char *argv[]);
int		check_input(int argc, char *argv[]);
void	*ft_calloc(size_t blocks, size_t size);
void	create_room(t_room *room);

#endif