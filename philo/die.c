/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:49:59 by ahkalama          #+#    #+#             */
/*   Updated: 2023/07/29 15:48:33 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	must_eating_check(t_table *table) // 6.argüman kontrolü
{
	int	i;

	if (table->number_of_must_eat < 0)
		return (0);
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_lock(&table->count_eat);
		if (table->philos[i++].eat_count < table->number_of_must_eat)
		{
			pthread_mutex_unlock(&table->count_eat);
			return (0);
		}
		else
			pthread_mutex_unlock(&table->count_eat);
	}
	return (1);
}

int	check_die(t_table *table, int i)
{
	while (table->number_of_philo > 1)
	{
		i = -1;
		while (++i < table->number_of_philo)
		{
			pthread_mutex_lock(&table->eat_last);
			pthread_mutex_lock(&table->is_die);
			if ((current_time() - table->philos[i].last_eat)
				>= table->time_to_die)
			{
				print(table->philos + i, "\033[0;32mPhilosop died");
				pthread_mutex_lock(&table->stop_count);
				table->stop = 1;
				pthread_mutex_unlock(&table->stop_count);
				pthread_mutex_unlock(&table->eat_last);
				return (0);
			}
			else
				pthread_mutex_unlock(&table->eat_last);
			pthread_mutex_unlock(&table->is_die);
		}
		if (must_eating_check(table))
			break ;
	}
	return (1);
}

void	die_check(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_of_philo == 1)
		print(table->philos, DIE);
	if (!(check_die(table, i)))
		return ;
	pthread_mutex_lock(&table->stop_count); // eğer must_eating_check in varsa yukarda döngüden çıkar buraya gelir.
		table->stop = 1;
	pthread_mutex_unlock(&table->stop_count);
}
