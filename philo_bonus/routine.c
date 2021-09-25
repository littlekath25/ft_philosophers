/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 13:48:25 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/25 14:58:55 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->room->num_philo)
	{
		kill(philo->room->philos[i].id, SIGKILL);
		i++;
	}
}

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
	while (get_timediff(philo->last_eaten, get_timestamp()) \
	< philo->room->time_die)
	{
		if (philo->room->satisfied == philo->room->min_times_eat)
			return (ptr);
		smartsleep(50, philo->room->philos);
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

	if (pthread_create(&monitor_thread, NULL, &monitor, philo))
		return ;
	philo->id = getpid();
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
	kill_all(philo);
}
