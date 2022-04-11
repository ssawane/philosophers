/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:05:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/05 17:31:06 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return((long)current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

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

void	*death_checker(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (1)
	{
		i = -1;
		while (++i < table->all_philo)
		{
			if (table->philo[i].time_to_die < get_time() - table->philo[i].time_last_eat)
			{
				table->death_check = 1;
				if (table->flag == 0 || (table->flag == 1 && table->philo[i].eat_count > 0))
					printf("%ld %d died\n",
						get_time() - table->start_time, table->philo[i].id);
				return ((void *)0);
			}
		}
	}
}

void	ft_next_step(t_table *table, int i)
{
	pthread_mutex_lock(&table->lock);
	table->philo[i].time_last_eat = get_time();
	if (table->death_check == 0)
		printf("%ld %d is eating\n", get_time() - table->start_time, table->philo[i].id);
	pthread_mutex_unlock(&table->lock);
	ft_usleep(table->philo[i].time_to_eat);
	if (table->philo[i].id == 1)
		pthread_mutex_unlock(&table->philo[table->all_philo - 1].fork);
	else
		pthread_mutex_unlock(&table->philo[i - 1].fork);
	pthread_mutex_unlock(&table->philo[i].fork);
	pthread_mutex_lock(&table->lock);
	if ((table->flag == 0 && table->death_check == 0)
		|| (table->flag == 1 && table->death_check == 0 && table->philo[i].eat_count != 1))
		printf("%ld %d is sleeping\n", get_time() - table->start_time, table->philo[i].id);
	pthread_mutex_unlock(&table->lock);
	ft_usleep(table->philo[i].time_to_sleep);
	pthread_mutex_lock(&table->lock);
	if ((table->flag == 0 && table->death_check == 0)
		|| (table->flag == 1 && table->death_check == 0 && table->philo[i].eat_count != 1))
		printf("%ld %d is thinking\n", get_time() - table->start_time, table->philo[i].id);
	pthread_mutex_unlock(&table->lock);
	table->philo[i].eat_count--;
}

void	*thread_proccessing(void *data)
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
			printf("%ld %d has taken a fork\n", get_time() - table->start_time, table->philo[i].id);
		pthread_mutex_lock(&table->philo[i].fork);
		if (table->death_check == 0)
			printf("%ld %d has taken a fork\n", get_time() - table->start_time, table->philo[i].id);
		ft_next_step(table, i);
	}
	return ((void *)0);
}

int	main_processing(t_table *table, pthread_t *thread)
{
	int i;
	
	i = -1;
	table->free = 3;
	table->start_time = get_time();
	while (++i < table->all_philo)
		table->philo[i].time_last_eat = table->start_time;
	table->ind = 0;
	while (table->ind < table->all_philo)
	{
		if (pthread_create(&thread[table->ind], NULL, thread_proccessing, (void *)table) != 0)
			return (1);
		usleep(50);
		table->ind += 2;
	}
	table->ind = 1;
	while (table->ind < table->all_philo)
	{
		if (pthread_create(&thread[table->ind], NULL, thread_proccessing, (void *)table) != 0)
			return (1);
		usleep(50);
		table->ind += 2;
	}
	return (0);
}

int	initialization(t_table *table, char **argv)
{
	int	i;

	i = -1;
	while(++i < table->all_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].time_to_die = ft_atoi(argv[2]);
		table->philo[i].time_to_eat = ft_atoi(argv[3]);
		table->philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (pthread_mutex_init(&table->philo[i].fork, NULL) != 0)
			return (1);
	}
	table->free = 2;
	return (0);
}