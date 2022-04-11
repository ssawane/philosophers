/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:10:29 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/05 18:31:04 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validator(t_table *table, int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60 ||(argc == 6 && argv[5] <= 0))
		return (write(1, "Error\n", 6) && 1);
	if (argc == 6)
	{
		table->eat_count = ft_atoi(argv[5]);
		table->flag = 1;
	}
	else if (argc == 5)
		table->flag = 0;	
	table->all_philo = ft_atoi(argv[1]);
	table->death_check = 0;
	table->free = 0;
	table->philo = malloc(sizeof(t_philo) * table->all_philo);
	if (!table->philo || pthread_mutex_init(&table->lock, NULL) != 0)
		return (1);
	table->free = 1;
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

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitoring;
	pthread_t	*thread;

	thread = NULL;
	if (!(validator(&table, argc, argv)) && !(initialization(&table, argv)))
	{
		thread = malloc(sizeof(pthread_t *) * table.all_philo);
		if (!thread || (pthread_create(&monitoring, NULL, death_checker, &table) != 0)
			|| main_processing(&table, thread))
			return (ft_free(&table, 0, 0) && 1);
		table.ind = 0;
		while(table.ind < table.all_philo && table.all_philo > 1)
			pthread_join(thread[table.ind++], NULL);
		pthread_join(monitoring, NULL);
	}
	ft_free(&table, 1, thread);
	return (0);
}