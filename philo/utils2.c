/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 16:23:04 by kfu           #+#    #+#                 */
/*   Updated: 2021/09/06 16:43:33 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smartsleep(int ms)
{
	int	i;

	i = 0;
	while (i < (ms * 10))
	{
		usleep(100);
		i++;
	}
}
