/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narah <narah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:20:13 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/24 17:23:43 by narah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_rules *rules)
{
    int i;
    long now;

    i = 0;
    while (i < rules->nb_philo)
    {
        pthread_mutex_lock(&rules->finished_mutex);
        int died = rules->someone_died;
        pthread_mutex_unlock(&rules->finished_mutex);
        if (died)
            return 1;

        now = current_time_ms();
        pthread_mutex_lock(&rules->finished_mutex);
        if (now - rules->philos[i].last_meal > rules->time_to_die)
        {
            rules->someone_died = 1;
            pthread_mutex_unlock(&rules->finished_mutex);

            pthread_mutex_lock(&rules->print_mutex);
            printf("%ld %d died\n",
                   now - rules->start_time, rules->philos[i].id);
            pthread_mutex_unlock(&rules->print_mutex);
            return 1;
        }
        pthread_mutex_unlock(&rules->finished_mutex);
        i++;
    }
    return 0;
}

int check_meals(t_rules *rules)
{
    pthread_mutex_lock(&rules->finished_mutex);
    int finished = (rules->must_eat_count != -1
                    && rules->finished_eating == rules->nb_philo);
    if (finished)
        rules->someone_died = 1;
    pthread_mutex_unlock(&rules->finished_mutex);
    return finished;
}

void *monitor(void *arg)
{
    t_rules *rules = (t_rules *)arg;

    while (1)
    {
        if (check_death(rules) || check_meals(rules))
            break;
        usleep(1000);
    }
    return NULL;
}
