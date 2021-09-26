/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/17 13:46:41 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/26 16:19:33 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->num_philo)
	{
		kill(room->philos[i].id, SIGKILL);
		i++;
	}
}

static void	fork_philos(t_room *room)
{
	int		i;
	int		res;
	int		status;

	i = 0;
	while (i < room->num_philo)
	{
		res = fork();
		if (res != 0)
			room->philos[i].id = res;
		if (res == 0)
		{
			start_routine(&room->philos[i]);
			break ;
		}
		i++;
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == DEATH_EXIT)
			kill_all(room);
	}
}

static void	start_process(t_room *room, char *argv[])
{
	pid_t	status;

	status = -1;
	room = init_room(room, argv);
	fork_philos(room);
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
