/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 16:23:04 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/10 15:30:37 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smartsleep(int ms)
{
	long long	time;
	long long	elapse;

	time = get_timestamp();
	elapse = get_timediff(get_timestamp(), time);
	while (elapse < ms)
	{
		usleep(100);
		elapse = get_timediff(get_timestamp(), time);
	}
}
