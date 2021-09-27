/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 11:40:42 by katherine     #+#    #+#                 */
/*   Updated: 2021/09/27 14:24:17 by kfu           ########   odam.nl         */
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
	sem_unlink("/forks");
	sem_unlink("/print");
}

static void	start_forks(t_room *room)
{
	int	i;
	int	res;
	int	status;

	i = 0;
	room->start_time = get_timestamp();
	while (i < room->num_philo)
	{
		res = fork();
		if (res)
			room->philos[i].id = res;
		else
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
		{
			room = init_room(room, argv);
			start_forks(room);
		}
	}
	else
		print_error(invalid_args);
	return (0);
}
