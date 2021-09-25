/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/17 13:46:41 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/25 14:34:37 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	fork_philos(t_room *room)
{
	int		i;
	pid_t	id;

	i = 0;
	while (i < room->num_philo)
	{
		id = fork();
		if (id == 0)
			start_routine(&room->philos[i]);
		i++;
	}
}

static void	start_process(t_room *room, char *argv[])
{
	int		status;

	status = 0;
	room = init_room(room, argv);
	fork_philos(room);
	while (wait(&status) > 0)
	{
	}
}

int	main(int argc, char *argv[])
{
	t_room	*room;
	int		check;

	room = NULL;
	if (argc > 1)
	{
		check = check_input(argc, argv);
		if (check == 1)
			print_error(wrong_args);
		else if (check == 2)
			print_error(invalid_args);
		else
			start_process(room, argv);
		free(room);
	}
	else
		print_error(invalid_args);
	return (0);
}
