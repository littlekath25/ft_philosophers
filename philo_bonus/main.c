/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/17 13:46:41 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/25 16:44:01 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all(t_room *room)
{
	int	i;

	i = 0;
	printf("HELLO ----------\n");
	while (i < room->num_philo)
	{
		printf("KILL PHILO %i -- %i\n", room->philos[i].position, room->philos[i].id);
		kill(room->philos[i].id, SIGQUIT);
		i++;
	}
}

static void	fork_philos(t_room *room)
{
	int		i;
	int		res;

	i = 0;
	while (i < room->num_philo)
	{
		res = fork();
		if (res != 0)
			room->philos[i].id = res;
		else
			break ;
		i++;
	}
	if (res == 0)
		start_routine(&room->philos[i]);
	if (room->philo_died == 1)
		kill_all(room);
}

static void	start_process(t_room *room, char *argv[])
{
	pid_t	status;

	status = -1;
	room = init_room(room, argv);
	fork_philos(room);
	waitpid(status, NULL, 0);
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
	printf("RETURN SUCCES\n");
	return (0);
}
