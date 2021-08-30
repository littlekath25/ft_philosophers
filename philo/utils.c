/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/15 18:57:33 by katherine     #+#    #+#                 */
/*   Updated: 2021/08/30 16:04:18 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_room(t_room *room)
{
	printf("NUM OF PHILO: %i\n", room->num_philo);
	printf("TIME TO DIE: %i\n", room->time_die);
	printf("TIME TO EAT: %i\n", room->time_eat);
	printf("TIME TO SLEEP: %i\n", room->time_sleep);
	printf("TIMES EAT: %i\n", room->min_times_eat);
}

void	error_and_exit(int error)
{
	if (error == invalid_args)
		printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
	if (error == wrong_args)
		printf("Argument error\n");
	if (error == malloc_fail)
		printf("Malloc fail\n");
	if (error == mutex_error)
		printf("Mutex errror\n");
	exit(1);
}
