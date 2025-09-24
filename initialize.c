/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahosni <fahosni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:19:52 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/19 15:26:27 by fahosni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	init_mutexes(t_rules *rules)
// {
// 	int	i;

// 	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
// 	if (!rules->forks)
// 		return (1);
// 	i = 0;
// 	while (i < rules->nb_philo)
// 	{
// 		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
// 		{
// 			cleanup(NULL, rules->forks, rules);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
// 	{
// 		cleanup(NULL, rules->forks, rules);
// 		return (1);
// 	}
// 	return (0);
// }


int	init_mutexes(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		{
			cleanup(NULL, rules->forks, rules);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
	{
		cleanup(NULL, rules->forks, rules);
		return (1);
	}
	// Initialize the death_mutex
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
	{
		cleanup(NULL, rules->forks, rules);
		return (1);
	}
	// Initialize the finished_mutex
	if (pthread_mutex_init(&rules->finished_mutex, NULL) != 0)
	{
		cleanup(NULL, rules->forks, rules);
		return (1);
	}
	// Initialize the meal_mutex
	if (pthread_mutex_init(&rules->meal_mutex, NULL) != 0)
	{
		cleanup(NULL, rules->forks, rules);
		return (1);
	}
	return (0);
}


void	init_philosophers(t_rules *rules, t_philo *philos)
{
	int		i;
	long	now;

	i = 0;
	now = current_time_ms();
	while (i < rules->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].rules = rules;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
		philos[i].meals_eaten = 0;
		philos[i].last_meal = now;
		i++;
	}
}
