/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:12:38 by ssawane           #+#    #+#             */
/*   Updated: 2022/04/14 11:44:16 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo {
	int				id;
	long			time_last_eat;
}	t_philo;

typedef struct s_table {
	int				*pid;
	int				all_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				flag;
	int				ind;
	long			start_time;
	int				eat_count;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*end;
	sem_t			*kill;
	pthread_t		death;
	pthread_t		last;
	t_philo			*philo;
}	t_table;

int		ft_atoi(const char *nptr);
int		initialization(t_table *table, int argc, char **argv);
void	child_proccessing(t_table *table);
void	*death_checker(void *data);
long	get_time(void);
void	ft_usleep(long time);
void	*last_thread(void *data);

#endif