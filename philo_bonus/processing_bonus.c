/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:05:23 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/14 12:15:54 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_checker(void *data)
{
	t_table	*table;
	int		i;
	int		time;

	table = (t_table *)data;
	i = -1;
	while (1)
	{
		time = (get_time() - table->philo[table->ind].time_last_eat) * 1000;
		if (time > table->time_to_die)
		{
			sem_wait(table->print);
			printf("%ld %d died\n", get_time()
				- table->start_time, table->philo[table->ind].id);
			pthread_detach(table->death);
			pthread_detach(table->last);
			sem_post(table->kill);
			while (++i <= table->all_philo)
				sem_post(table->end);
		}
	}
	return ((void *)0);
}

void	ft_next_step(t_table *table, int i)
{
	sem_wait(table->print);
	printf("%ld %d is sleeping\n",
		get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
	ft_usleep(table->time_to_sleep / 1000);
	sem_wait(table->print);
	printf("%ld %d is thinking\n",
		get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
}

void	getting_forks(t_table *table, int i)
{
	sem_wait(table->fork);
	sem_wait(table->print);
	printf("%ld %d has taken a fork\n",
		get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
	sem_wait(table->fork);
	sem_wait(table->print);
	printf("%ld %d has taken a fork\n",
		get_time() - table->start_time, table->philo[i].id);
	printf("%ld %d is eating\n",
		get_time() - table->start_time, table->philo[i].id);
	sem_post(table->print);
	ft_usleep(table->time_to_eat / 1000);
	table->philo[i].time_last_eat = get_time();
	sem_post(table->fork);
	sem_post(table->fork);
}

void	child_proccessing(t_table *table)
{
	int		i;
	int		j;

	j = 0;
	i = table->ind;
	pthread_create(&table->death, NULL, death_checker, (void *)table);
	pthread_create(&table->last, NULL, last_thread, (void *)table);
	while ((j < table->eat_count && table->flag == 1) || table->flag == 0)
	{
		getting_forks(table, i);
		j++;
		if (table->flag == 1 && j == table->eat_count)
		{
			pthread_detach(table->death);
			pthread_detach(table->last);
			exit(0);
		}
		ft_next_step(table, i);
	}
}

int	initialization(t_table *table, int argc, char **argv)
{
	int	i;

	i = -1;
	table->time_to_die = ft_atoi(argv[2]) * 1000;
	table->time_to_eat = ft_atoi(argv[3]) * 1000;
	table->time_to_sleep = ft_atoi(argv[4]) * 1000;
	table->flag = 0;
	table->all_philo = ft_atoi(argv[1]);
	table->start_time = get_time();
	table->philo = malloc(sizeof(t_philo) * table->all_philo);
	table->pid = malloc(sizeof(int *) * table->all_philo);
	if (!table->philo || !table->pid)
		return (1);
	while (++i < table->all_philo)
		table->philo[i].id = i + 1;
	if (argc == 5)
		return (0);
	table->eat_count = ft_atoi(argv[5]);
	table->flag = 1;
	return (0);
}
