/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahosni <fahosni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:20:13 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/19 15:25:40 by fahosni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_rules *rules)
{
    int i;
    long now;

    i = 0;
    while (i < rules->nb_philo && !rules->someone_died)
    {
        now = current_time_ms();
        if (now - rules->philos[i].last_meal > rules->time_to_die)
        {
            pthread_mutex_lock(&rules->print_mutex);
            if (!rules->someone_died)
            {
                printf("%ld %d died\n",
                    now - rules->start_time, rules->philos[i].id);
                rules->someone_died = 1;
            }
            pthread_mutex_unlock(&rules->print_mutex);
            return (1);
        }
        i++;
    }
    return (0);
}

int check_meals(t_rules *rules)
{
    if (rules->must_eat_count != -1
        && rules->finished_eating == rules->nb_philo)
    {
        pthread_mutex_lock(&rules->print_mutex);
        rules->someone_died = 1;
        pthread_mutex_unlock(&rules->print_mutex);
        return (1);
    }
    return (0);
}

void *monitor(void *arg)
{
    t_rules *rules = (t_rules *)arg;

    while (!rules->someone_died)
    {
        if (check_death(rules) || check_meals(rules))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}
