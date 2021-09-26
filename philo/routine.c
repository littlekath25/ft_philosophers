/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 13:48:25 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/26 21:35:44 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smartsleep(int ms, t_philo *philo)
{
	long long	start;

	start = get_timestamp();
	while (!philo->room->philo_died)
	{
		if (get_timediff(start, get_timestamp()) >= ms)
			break ;
		else if (philo->is_eating == 0)
		{
			if (get_timediff(philo->last_eaten, get_timestamp()) >= philo->room->time_die)
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
	pthread_mutex_lock(&philo->room->forks[philo->left_fork]);
	print_state(taken_fork, philo);
	pthread_mutex_lock(&philo->room->forks[philo->right_fork]);
	print_state(taken_fork, philo);
	philo->last_eaten = get_timestamp();
	philo->is_eating = 1;
	print_state(eating, philo);
	smartsleep(philo->room->time_eat, philo);
	philo->is_eating = 0;
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->room->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->room->forks[philo->right_fork]);
}

void	*start_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->position % 2)
		usleep(1000);
	while (!philo->room->philo_died)
	{
		start_eating(philo);
		if (philo->room->min_times_eat > 0 && \
		philo->times_eaten >= philo->room->min_times_eat)
		{
			philo->room->satisfied++;
			break ;
		}
		print_state(sleeping, philo);
		smartsleep(philo->room->time_sleep, philo);
		print_state(thinking, philo);
	}
	return (ptr);
}
