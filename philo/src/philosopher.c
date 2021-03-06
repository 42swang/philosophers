/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:03:02 by swang             #+#    #+#             */
/*   Updated: 2021/11/01 14:43:21 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philosopher(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_of_philo)
	{
		philo[i].last_eat = data->start_time; // 시작시간을 여기서 넣어줌
		pthread_create(&(philo[i].thread), NULL, &(philo_thread), &(philo[i]));
		pthread_create(&(philo[i].monitor), NULL, &(monitor_thread), &(philo[i]));
		usleep(10); // 생성 후 시간줘서 쓰레드 꼬임 방지
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(philo[i].thread, 0);
		pthread_join(philo[i].monitor, 0);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&(data->fork[i]));
		pthread_mutex_destroy(&(philo[i].eat));
		i++;
	}
	pthread_mutex_destroy(data->print);
	ft_free(data, philo);
}
