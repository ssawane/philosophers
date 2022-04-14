/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 23:45:59 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/14 12:16:35 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			k;
	long int	j;

	i = 0;
	j = 0;
	k = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + k * (str[i] - '0');
		i++;
		if (j < -2147483648 || j > 2147483647)
			exit(write(1, "Error\n", 6));
	}
	return (j);
}

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long)current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	t;

	t = get_time();
	while (get_time() - t < time)
		usleep(100);
}

void	*last_thread(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	sem_wait(table->end);
	exit (0);
}
