/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:12:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/09 15:00:22 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo {
	int				id;
	int				eat_count;
	long			time_last_eat;
}	t_philo;

typedef struct s_table {
	int				*pid;
	int				all_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				flag;
	int				ind;
	long			start_time;
	int				eat_count;
	int				free;
	sem_t			*fork;
	sem_t			*print;
	pthread_t		death;
	t_philo			*philo;
}	t_table;

int		ft_atoi(const char *nptr);
int		initialization(t_table *table, char **argv);
int		main_processing(t_table *table, pthread_t *thread);
void	*death_checker(void *data);

#endif