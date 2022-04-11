/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:10:29 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/10 13:07:32 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	validator(t_table *table, int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60 ||(argc == 6 && argv[5] <= 0))
		return (write(1, "Error\n", 6) && 1);
	return (0);
}

int	ft_free(t_table *table, int flag, pthread_t *thread)
{
	int	i;

	i = -1;
	if (table->free > 0)
	{
		free(table->philo);
		pthread_mutex_destroy(&table->lock);
	}
	if (table->free > 1)
		while(++i < table->all_philo - 1)
			pthread_mutex_destroy(&(table->philo[i].fork));
	if (table->free > 2)
		free(thread);
	if (flag == 0)
		write(1, "Error\n", 6);
	return (0);
}

void	sem_initialization(t_table *table, char **argv)
{
	sem_close(table->fork);
	sem_close(table->print);
	sem_unlink(table->fork);
	sem_unlink(table->print);
	table->fork = sem_open("fork", O_CREAT, 0644, argv[1]);
	table->print = sem_open("print", O_CREAT, 0644, 1);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitoring;

	if (!(validator(&table, argc, argv)) && !(initialization(&table, argv)))
	{
		sem_initialization(table, argv);
		table.start_time = get_time();
		table.ind = -1;
		while (++table.ind < table.all_philo)
		{
			table.pid[table->ind] = fork();
			if (table.pid[table->ind] = 0)
				child_proccessing(&table);
		}
		table.ind = 0;
		while(table.ind < table.all_philo && table.all_philo > 1)
			pthread_join(thread[table.ind++], NULL);
		pthread_join(monitoring, NULL);
	}
	ft_free(&table, 1, thread);
	return (0);
}