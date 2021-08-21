/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/15 18:57:33 by katherine     #+#    #+#                 */
/*   Updated: 2021/08/15 19:53:30 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	exit(1);
}
