/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/09 15:30:28 by katherine     #+#    #+#                 */
/*   Updated: 2021/08/25 12:10:11 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_room	*init_room(t_room *room, char *argv[])
{
	room = (t_room *)malloc(sizeof(t_room) * 1);
	room->num_philo = ft_atoi(argv[1]);
	room->time_die = ft_atoi(argv[2]);
	room->time_eat = ft_atoi(argv[3]);
	room->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		room->min_times_eat = ft_atoi(argv[5]);
	else
		room->min_times_eat = -1;
	return (room);
}

void	*test(void *ptr)
{
	printf("HELLO WORLD\n");
	return (ptr);
}

void	create_philos(t_room *room)
{
	int	i;
	int	len;

	i = 0;
	len = room->num_philo + 1;
	room->threads = (pthread_t *)ft_calloc(len, sizeof(pthread_t));
	while (i < room->num_philo)
	{
		pthread_create(&room->threads[i], NULL, &test, NULL);
		printf("ID: %li - %i\n", room->threads[i], i);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_room	*room;

	room = NULL;
	if (check_input(argc, argv) == 0)
		error_and_exit(invalid_args);
	else
	{
		room = init_room(room, argv);
		create_philos(room);
		// print_room(room);
	}
	exit(0);
}
