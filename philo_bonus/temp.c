/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:15:01 by ssawane           #+#    #+#             */
/*   Updated: 2022/02/14 17:49:07 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_t		t1;
pthread_t		t2;
pthread_mutex_t	mut;

void	*print_smth(void *arg)
{
	pthread_mutex_lock(&mut);
	int	i;

	i = -1;
	while (++i < 10)
	{
		printf("%s: ", (char *)arg);
		printf("%d\n", i);
		usleep(200000);
	}
	pthread_mutex_unlock(&mut);
	return NULL;
}

int	main(void)
{
	char		*str1;
	char		*str2;

	str1 = "NANOBOOST";
	str2 = "SHUTTER";
	pthread_mutex_init(&mut, NULL);
	pthread_create(&t1, NULL, print_smth, (void *)str1);
	pthread_create(&t2, NULL, print_smth, (void *)str2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	// pthread_detach(t2);

	//pthread_join(t1, NULL);
	// usleep(2000000);
	// print_smth(str);
	pthread_detach(t1);
}