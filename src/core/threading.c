/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:22:42 by moabid            #+#    #+#             */
/*   Updated: 2022/08/05 22:42:04 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	threading(struct s_data *data)
{
	if (threading_launch(data, data->philo) == false)
	{
		free(data->fork);
		free(data->philo);
		return (false);
	}
	francisco_is_watching(data, data->philo, 0);
	return (true);
}

bool	threading_launch(struct s_data *data, struct s_philo *philo)
{
	int	i;

	pthread_mutex_lock(&(data->wait));
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(philo[i].philo_thread),
				NULL, life_cycle, &(philo[i])) != 0)
			ft_error(THREAD_ERR);
		i += 1;
		usleep(2);
	}
	data->created = true;
	data->start_time = ft_gettime();
	pthread_mutex_unlock(&(data->wait));
	fflush(stdout);
	return (true);
}

void	*life_cycle(void *philo_void)
{
	struct s_philo	*philo;
	struct s_data	*data;

	philo = (struct s_philo *) philo_void;
	data = philo->data;
	pthread_mutex_lock(&(data->wait));
	pthread_mutex_unlock(&(data->wait));
	philo->last_eating_time = ft_gettime();
	if ((philo->philo_id + 1) % 2 == 0)
		ft_usleep(data->time_to_eat);
	while (1)
	{
		if (data->dead)
			return (NULL);
		philo_eat_cycle(data, philo);
		if (philo_meals_check(data, philo) == true || data->nb_philo == 1)
			return (NULL);
		philo_sleep(data, philo);
		philo_think(data, philo);
	}
	return (NULL);
}

void	francisco_is_watching(struct s_data *data, struct s_philo *philo, int i)
{
	while (1)
	{
		i = 0;
		ft_usleep(data->time_to_die);
		while (i < data->nb_philo && !data->dead)
		{
			data->death_time = ft_gettime() - philo[i].last_eating_time;
			if (data->death_time > data->time_to_die - 1)
			{
				print_state(data, philo[i].philo_id, DEATH);
				pthread_mutex_lock(&(data->death));
				data->dead = true;
				pthread_mutex_unlock(&(data->death));
			}
			i++;
		}
		if (data->dead)
			return ;
		if (data->nb_of_meal != -1
			&& ft_eat_enough(data, philo) == data->nb_philo)
			break ;
	}
}
