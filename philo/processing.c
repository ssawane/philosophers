/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:05:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/13 18:45:25 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	long	end;
	long	start;

	start = get_time();
	end = start + time;
	while (start < end)
	{
		usleep(500);
		start = get_time();
	}
}

void	ft_next_step_v2(t_table *table, int i)
{
	pthread_mutex_lock(&table->lock);
	if ((table->flag == 0 && table->death_check == 0)
		|| (table->flag == 1 && table->death_check == 0
			&& table->philo[i].eat_count != 1))
		printf("%ld %d is thinking\n",
			get_time() - table->start_time, table->philo[i].id);
	pthread_mutex_unlock(&table->lock);
	table->philo[i].eat_count--;
}

void	ft_next_step(t_table *table, int i)
{
	pthread_mutex_lock(&table->lock);
	table->philo[i].time_last_eat = get_time();
	if (table->death_check == 0)
		printf("%ld %d is eating\n",
			get_time() - table->start_time, table->philo[i].id);
	pthread_mutex_unlock(&table->lock);
	ft_usleep(table->philo[i].time_to_eat);
	if (table->philo[i].id == 1)
		pthread_mutex_unlock(&table->philo[table->all_philo - 1].fork);
	else
		pthread_mutex_unlock(&table->philo[i - 1].fork);
	pthread_mutex_unlock(&table->philo[i].fork);
	pthread_mutex_lock(&table->lock);
	if ((table->flag == 0 && table->death_check == 0)
		|| (table->flag == 1 && table->death_check == 0
			&& table->philo[i].eat_count != 1))
		printf("%ld %d is sleeping\n",
			get_time() - table->start_time, table->philo[i].id);
	pthread_mutex_unlock(&table->lock);
	ft_usleep(table->philo[i].time_to_sleep);
	ft_next_step_v2(table, i);
}

void	*thr_prc(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	i = table->ind;
	table->philo[i].eat_count = table->eat_count;
	table->philo[i].time_last_eat = get_time();
	while (table->death_check != 1)
	{
		if (table->flag == 1 && table->philo[i].eat_count == 0)
			return ((void *)0);
		if (table->philo[i].id == 1)
			pthread_mutex_lock(&table->philo[table->all_philo - 1].fork);
		else
			pthread_mutex_lock(&table->philo[i - 1].fork);
		if (table->death_check == 0)
			printf("%ld %d has taken a fork\n",
				get_time() - table->start_time, table->philo[i].id);
		pthread_mutex_lock(&table->philo[i].fork);
		if (table->death_check == 0)
			printf("%ld %d has taken a fork\n",
				get_time() - table->start_time, table->philo[i].id);
		ft_next_step(table, i);
	}
	return ((void *)0);
}

int	main_processing(t_table *table, pthread_t *thread)
{
	int		i;

	table->free = 3;
	table->start_time = get_time();
	i = -1;
	while (++i < table->all_philo)
		table->philo[i].time_last_eat = table->start_time;
	table->ind = 0;
	while (table->ind < table->all_philo)
	{
		if (pthread_create(&thread[table->ind], NULL, thr_prc, table) != 0)
			return (1);
		usleep(50);
		table->ind += 2;
	}
	table->ind = 1;
	while (table->ind < table->all_philo)
	{
		if (pthread_create(&thread[table->ind], NULL, thr_prc, table) != 0)
			return (1);
		usleep(50);
		table->ind += 2;
	}
	return (0);
}
