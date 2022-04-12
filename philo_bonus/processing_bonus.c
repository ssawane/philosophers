/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:05:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/12 14:47:07 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	t_table	*table;
	int		i;

	table = (t_table *)data;
	i = -1;
	while (1)
	{
		if (table->time_to_die < get_time() - table->philo[table->ind].time_last_eat)
			{
				sem_wait(table->print);
				printf("%ld %d died\n", get_time() - table->start_time, table->philo[table->ind].id);
				//sem_post(table->print);
				while(++i < table->all_philo)
					sem_post(table->end);
			}
	}
	return ((void *)0);
}

void	*last_thread(void *data)
{
	t_table *table;

	table = (t_table *)data;
	sem_wait(table->end);
	exit (0);
}

void	ft_next_step(t_table *table, int i)
{
	sem_wait(table->print);
	printf("%ld %d is sleeping\n", get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
	ft_usleep(table->time_to_sleep);
	sem_wait(table->print);
	printf("%ld %d is thinking\n", get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
}

void	getting_forks(t_table *table, int i)
{
	sem_wait(table->fork);
	sem_wait(table->print);
	printf("%ld %d has taken a fork\n", get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
	sem_wait(table->fork);
	sem_wait(table->print);
	printf("%ld %d has taken a fork\n", get_time() - table->start_time, table->philo[i].id);
	printf("%ld %d is eating\n", get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
	table->philo[i].time_last_eat = get_time();
	ft_usleep(table->time_to_eat);
	sem_post(table->fork);
	sem_post(table->fork);
}

void	child_proccessing(t_table *table)
{
	int		i;
	int		j;
	
	i = table->ind;
	j = 0;
	table->philo[table->ind].time_last_eat = table->start_time;
	pthread_create(&table->death, NULL, death_checker, (void *)table);
	pthread_create(&table->last, NULL, last_thread, (void *)table);
	while ((j < table->eat_count && table->flag == 1) || table->flag == 0)
	{
		getting_forks(table, table->ind);
		j++;
		if (table->flag == 1 && j == table->eat_count)
		{
			pthread_detach(table->death);
			pthread_detach(table->death);
			exit(0);
		}
		ft_next_step(table, i);
	}
}

int	initialization(t_table *table, int argc, char **argv)
{
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->flag = 0;	
	table->all_philo = ft_atoi(argv[1]);
	table->free = 0; //free
	table->philo = malloc(sizeof(t_philo) * table->all_philo);
	table->pid = malloc(sizeof(int) * table->all_philo);
	if (!table->philo || !table->pid)
		return (1);
	table->free = 1; //free
	table->ind = -1;
	while(++table->ind < table->all_philo)
		table->philo[table->ind].id = table->ind + 1;
	if (argc == 5)
		return (0);
	table->eat_count = ft_atoi(argv[5]);
	table->flag = 1;
	return (0);
}