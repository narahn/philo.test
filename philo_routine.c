/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahosni <fahosni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:20:28 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/19 14:56:49 by fahosni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void finish_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->someone_died)
        printf("%ld %d is eating\n",
            current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
    philo->last_meal = current_time_ms();
    long start = current_time_ms();
    while (!philo->rules->someone_died
           && current_time_ms() - start < philo->rules->time_to_eat)
        usleep(100);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    philo->meals_eaten++;
    if (philo->rules->must_eat_count != -1
        && philo->meals_eaten == philo->rules->must_eat_count)
    {
        pthread_mutex_lock(&philo->rules->finished_mutex);
        philo->rules->finished_eating++;
        pthread_mutex_unlock(&philo->rules->finished_mutex);
    }
}

void philo_eat(t_philo *philo)
{
    if (philo->rules->someone_died)
        return;
    take_forks(philo);
    if (philo->rules->nb_philo == 1 || philo->rules->someone_died)
        return;
    finish_eating(philo);
}

void philo_sleep_think(t_philo *philo)
{
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->someone_died)
        printf("%ld %d is sleeping\n",
            current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
    long start = current_time_ms();
    while (!philo->rules->someone_died
           && current_time_ms() - start < philo->rules->time_to_sleep)
        usleep(100);
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->someone_died)
        printf("%ld %d is thinking\n",
            current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 1)
        usleep(1000);
    while (!philo->rules->someone_died)
    {
        philo_eat(philo);
        if (philo->rules->someone_died)
            break;
        philo_sleep_think(philo);
    }
    return (NULL);
}
