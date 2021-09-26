/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 13:48:25 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/26 16:00:16 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	smartsleep(int ms, t_philo *philo)
{
	long long	start;

	start = get_timestamp();
	while (!philo->room->philo_died)
	{
		if (get_timediff(start, get_timestamp()) >= ms)
			break ;
		usleep(100);
	}
}

static void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (get_timediff(philo->last_eaten, \
	get_timestamp()) < philo->room->time_die)
	{
		if (philo->room->satisfied == philo->room->min_times_eat)
			return (ptr);
		smartsleep(100, philo->room->philos);
	}
	print_state(dead, philo);
	philo->room->philo_died = 1;
	return (ptr);
}

static void	start_eating(t_philo *philo)
{
	sem_wait(&philo->room->forks[philo->left_fork]);
	print_state(taken_fork, philo);
	sem_wait(&philo->room->forks[philo->right_fork]);
	print_state(taken_fork, philo);
	philo->last_eaten = get_timestamp();
	philo->is_eating = 1;
	print_state(eating, philo);
	smartsleep(philo->room->time_eat, philo);
	philo->is_eating = 0;
	philo->times_eaten++;
	sem_post(&philo->room->forks[philo->left_fork]);
	sem_post(&philo->room->forks[philo->right_fork]);
}

void	start_routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	philo->id = getpid();
	if (pthread_create(&monitor_thread, NULL, &monitor, philo))
		exit(-1);
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
	if (philo->room->philo_died == 1)
		exit(DEATH_EXIT);
}
