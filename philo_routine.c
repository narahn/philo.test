/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narah <narah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:20:28 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/24 17:23:31 by narah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

void finish_eating(t_philo *philo)
{
    t_rules *rules = philo->rules;

    // Update last meal safely
    pthread_mutex_lock(&rules->finished_mutex);
    philo->last_meal = current_time_ms();
    philo->meals_eaten++;
    if (rules->must_eat_count > 0
        && philo->meals_eaten == rules->must_eat_count)
    {
        rules->finished_eating++;
    }
    pthread_mutex_unlock(&rules->finished_mutex);

    print_action(philo, "is eating");
    smart_sleep(rules->time_to_eat, rules);

    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}



void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_rules *rules = philo->rules;

    if (philo->id % 2 == 0)
        usleep(100); // offset for even philosophers

    while (1)
    {
        // Check if simulation ended
        pthread_mutex_lock(&rules->finished_mutex);
        int done = (rules->must_eat_count != -1
                    && rules->finished_eating == rules->nb_philo);
        pthread_mutex_unlock(&rules->finished_mutex);

        if (rules->someone_died || done)
            break;

        // Take forks and eat
        take_forks(philo);
        if (rules->nb_philo > 1) // already handled in take_forks for 1
            finish_eating(philo);

        // Sleep
        if (rules->someone_died)
            break;
        print_action(philo, "is sleeping");
        smart_sleep(rules->time_to_sleep, rules);

        // Think
        if (rules->someone_died)
            break;
        print_action(philo, "is thinking");
    }
    return NULL;
}