/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:50:28 by ahkalama          #+#    #+#             */
/*   Updated: 2023/07/29 15:20:48 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_valid(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Error: The number of arguments must be 5 or 6\n");
		exit(1);
	}
	if (unsigned_atoi(av[1]) <= 0)
	{
		ft_err("Error: Number of philosophers is not valid\n");
		exit(1);
	}
	while (av[i])
	{
		if (!is_digit(av[i]) || unsigned_atoi(av[i]) == 0)
		{
			ft_err("Error: Arguments are must be digit\n");
			exit(1);
		}
		i++;
	}
	return (1);
}

t_table	*parse(int ac, char **av)
{
	t_table	*table;

	if (!check_valid(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
	{
		free(table);
		return (NULL);
	}
	table->number_of_philo = unsigned_atoi(av[1]);
	table->time_to_die = unsigned_atoi(av[2]);
	table->time_to_eat = unsigned_atoi(av[3]);
	table->time_to_sleep = unsigned_atoi(av[4]);
	table->number_of_must_eat = -1;
	if (ac == 6)
		table->number_of_must_eat = unsigned_atoi(av[5]);
	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	table->time = current_time();
	table->stop = 0;
	return (table);
}
