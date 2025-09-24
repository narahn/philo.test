/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahosni <fahosni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:20:19 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/13 16:23:04 by fahosni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo invalide number of arguments\n");
		return (1);
	}
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat_count = ft_atoi(argv[5]);
	else
		rules->must_eat_count = -1;
	// pthread_mutex_lock(&rules->death_mutex);
	rules->someone_died = 0;
	// pthread_mutex_unlock(&rules->death_mutex);
	if (rules->nb_philo <= 0 || rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0 || (argc == 6
			&& rules->must_eat_count <= 0))
	{
		printf("Error: invalide arguments\n");
		return (1);
	}
	return (0);
}


