/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:29:08 by moabid            #+#    #+#             */
/*   Updated: 2022/08/05 22:47:35 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_strcmp(const char *strg1, char *strg2)
{
	while ((*strg1 != '\0' && *strg2 != '\0') && *strg1 == *strg2)
	{
		strg1++;
		strg2++;
	}
	if (*strg1 == *strg2)
		return (0);
	else
		return (*strg1 - *strg2);
}

static void	printer(char *state, long long time, int id)
{
	if (!my_strcmp(state, EAT))
		printf("\x1B[31m%-5llu \x1B[36m[%2d] \x1B[32m%-22s\x1B[37m​​ 🍕\n",
			time, id, state);
	else if (!my_strcmp(state, THINK))
		printf("\x1B[31m%-5llu \x1B[36m[%2d] \x1B[32m%-22s\x1B[37m ​💬​​\n",
			time, id, state);
	else if (!my_strcmp(state, SLEEP))
		printf("\x1B[31m%-5llu \x1B[36m[%2d] \x1B[32m%-22s\x1B[37m​ 💤​​​\n",
			time, id, state);
	else if (!my_strcmp(state, FORK))
		printf("\x1B[31m%-5llu \x1B[36m[%2d] \x1B[32m%-22s\x1B[37m 🥄​\n",
			time, id, state);
	else if (!my_strcmp(state, DEATH))
		printf("\x1B[31m%-5llu \x1B[36m[%2d] \x1B[32m%-22s\x1B[37m​ 💀​​​\n",
			time, id, state);
}

void	print_state(struct s_data *data, int id, char *action)
{
	pthread_mutex_lock(&(data->log));
	if (!data->dead)
		printer(action, ft_gettime() - data->start_time, id);
	pthread_mutex_unlock(&(data->log));
}

long long	ft_gettime(void)
{
	struct timeval	time_value;
	long long		time;

	gettimeofday(&time_value, NULL);
	time = time_value.tv_sec * 1000 + time_value.tv_usec / 1000;
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_gettime();
	while ((ft_gettime() - start_time) < time_in_ms)
		usleep(200);
}
