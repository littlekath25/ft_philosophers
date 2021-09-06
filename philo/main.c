/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/09 15:30:28 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/06 13:12:06 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_room	*init_room(t_room *room, char *argv[])
{
	room = (t_room *)malloc(sizeof(t_room) * 1);
	room->position = 1;
	room->num_philo = ft_atoi(argv[1]);
	room->time_die = ft_atoi(argv[2]);
	room->time_eat = ft_atoi(argv[3]);
	room->time_sleep = ft_atoi(argv[4]);
	if (room->num_philo < 2 || room->time_die < 0 \
	|| room->time_eat < 0 || room->time_sleep < 0)
		error_and_exit(wrong_args);
	if (argv[5])
	{
		room->min_times_eat = ft_atoi(argv[5]);
		if (room->min_times_eat < 0)
			error_and_exit(wrong_args);
	}
	else
		room->min_times_eat = -1;
	room->start_time = get_timestamp();
	return (room);
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
		create_room(room);
	}
	exit(0);
}
