/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:12:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/05 17:19:01 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo {
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long			time_last_eat;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_table {
	int				all_philo;
	int				flag;
	int				ind;
	int				death_check;
	long			start_time;
	int				eat_count;
	int				free;
	t_philo			*philo;
	pthread_mutex_t	lock;
}	t_table;

int		ft_atoi(const char *nptr);
int		initialization(t_table *table, char **argv);
int		main_processing(t_table *table, pthread_t *thread);
void	*death_checker(void *data);

#endif