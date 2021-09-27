/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 13:48:25 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/27 14:20:49 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo->times_eaten == philo->room->min_times_eat)
			break ;
		if (get_timediff(philo->last_eaten, get_timestamp()) > \
		philo->room->time_die)
		{
			print_state(dead, philo);
			philo->room->philo_died = 1;
			break ;
		}
		smartsleep(50, philo);
	}
	return (ptr);
}

void	smartsleep(int ms, t_philo *philo)
{
	long long	start;

	start = get_timestamp();
	while (get_timediff(start, get_timestamp()) < ms)
	{
		if (philo->is_eating == 0)
		{
			if (get_timediff(philo->last_eaten, \
			get_timestamp()) >= philo->room->time_die)
			{
				print_state(dead, philo);
				philo->room->philo_died = 1;
				break ;
			}
		}
		usleep(100);
	}
}

static void	start_eating(t_philo *philo)
{
	sem_wait(philo->room->forks);
	print_state(taken_fork, philo);
	sem_wait(philo->room->forks);
	print_state(taken_fork, philo);
	philo->last_eaten = get_timestamp();
	philo->is_eating = 1;
	print_state(eating, philo);
	smartsleep(philo->room->time_eat, philo);
	philo->is_eating = 0;
	philo->times_eaten++;
	sem_post(philo->room->forks);
	sem_post(philo->room->forks);
}

void	start_routine(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, &monitor, philo))
		print_error(semaphore_error);
	while (!philo->room->philo_died)
	{
		start_eating(philo);
		if (philo->times_eaten == philo->room->min_times_eat)
			exit(0);
		print_state(sleeping, philo);
		smartsleep(philo->room->time_sleep, philo);
		print_state(thinking, philo);
	}
}
