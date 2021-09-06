/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/15 18:57:33 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/06 16:31:33 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(int state, t_philo *philo)
{
	if (state == taken_fork)
		printf("%lli %i has taken a fork\n", get_timestamp() \
		- philo->room->start_time, philo->position);
	if (state == eating)
		printf("%lli %i is eating\n", get_timestamp() \
		- philo->room->start_time, philo->position);
	if (state == sleeping)
		printf("%lli %i is sleeping\n", get_timestamp() \
		- philo->room->start_time, philo->position);
	if (state == thinking)
		printf("%lli %i is thinking\n", get_timestamp() \
		- philo->room->start_time, philo->position);
	if (state == dead)
		printf("%lli %i died\n", get_timestamp() \
		- philo->room->start_time, philo->position);
}

long long	get_timestamp(void)
{
	struct timeval	time;
	long long		new_time;

	gettimeofday(&time, NULL);
	new_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (new_time);
}

long long	get_timediff(long long past, long long pres)
{
	return (past - pres);
}

void	*ft_calloc(size_t blocks, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (blocks < i || size < i)
		return (NULL);
	ptr = malloc(blocks * size);
	if (ptr == NULL)
		return ((void *)0);
	while (i < (blocks * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}

void	error_and_exit(int error)
{
	if (error == invalid_args)
		printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] \
		[number_of_times_each_philosopher_must_eat]\n");
	if (error == wrong_args)
		printf("Argument error\n");
	if (error == malloc_fail)
		printf("Malloc fail\n");
	if (error == mutex_error)
		printf("Mutex errror\n");
	exit(1);
}
