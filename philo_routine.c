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

// void finish_eating(t_philo *philo)
// {
//     t_rules *rules = philo->rules;

//     // Update last meal safely
//     pthread_mutex_lock(&rules->finished_mutex);
//     philo->last_meal = current_time_ms();
//     philo->meals_eaten++;
//     if (rules->must_eat_count > 0
//         && philo->meals_eaten == rules->must_eat_count)
//     {
//         rules->finished_eating++;
//     }
//     pthread_mutex_unlock(&rules->finished_mutex);

//     print_action(philo, "is eating");
//     smart_sleep(rules->time_to_eat, rules);

//     pthread_mutex_unlock(philo->left_fork);
//     pthread_mutex_unlock(philo->right_fork);
// }


// void *philo_routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;
//     t_rules *rules = philo->rules;

//     // if(rules->nb_philo == 1)
//     //     print_action(philo, "has taken a fork");
//     if (philo->id % 2 == 0)
//         usleep(100); // offset for even philosophers

//     while (1)
//     {
//         // Check if simulation ended
//         int done = (rules->must_eat_count != -1
//                     && rules->finished_eating == rules->nb_philo);
//         if (rules->someone_died || done)
//             break;

//         // Take forks and eat
//         take_forks(philo);
//         if (rules->nb_philo > 1) // already handled in take_forks for 1
//             finish_eating(philo);

//         // Sleep
//         if (rules->someone_died)
//             break;
//         print_action(philo, "is sleeping");
//         smart_sleep(rules->time_to_sleep, rules);

//         // Think
//         if (rules->someone_died)
//             break;
//         print_action(philo, "is thinking");
//     }
//     return NULL;
// }



int check_if_died(t_rules *rules)
{
    pthread_mutex_lock(&rules->death_mutex);
    int died = rules->someone_died;
    pthread_mutex_unlock(&rules->death_mutex);
    return died;
}

int check_if_all_eaten(t_rules *rules)
{
    pthread_mutex_lock(&rules->finished_mutex);
    int done = (rules->must_eat_count != -1
                && rules->finished_eating == rules->nb_philo);
    pthread_mutex_unlock(&rules->finished_mutex);
    return done;
}

void finish_eating(t_philo *philo)
{
    t_rules *rules = philo->rules;

    // Update last meal and meals eaten safely with meal_mutex
    pthread_mutex_lock(&rules->meal_mutex);
    philo->last_meal = current_time_ms();
    philo->meals_eaten++;
    int meals_count = philo->meals_eaten; // capture the current count
    pthread_mutex_unlock(&rules->meal_mutex);

    print_action(philo, "is eating");
    smart_sleep(rules->time_to_eat, rules);

    // Check if this philosopher finished all required meals AFTER eating
    if (rules->must_eat_count > 0 && meals_count >= rules->must_eat_count)
    {
        pthread_mutex_lock(&rules->finished_mutex);
        rules->finished_eating++;
        pthread_mutex_unlock(&rules->finished_mutex);
    }

    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

int check_if_philo_done(t_philo *philo)
{
    t_rules *rules = philo->rules;
    if (rules->must_eat_count <= 0)
        return 0; // No meal limit, never done
    
    pthread_mutex_lock(&rules->meal_mutex);
    int done = (philo->meals_eaten >= rules->must_eat_count);
    pthread_mutex_unlock(&rules->meal_mutex);
    return done;
}



void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_rules *rules = philo->rules;

    if (rules->nb_philo == 1)
    {
        print_action(philo, "has taken a fork");
        smart_sleep(rules->time_to_die, rules);
        return NULL; // Exit - single philo will die
    }
    if (philo->id % 2 == 0)
        usleep(100); // offset for even philosophers

    while (1)
    {
        // Check if simulation ended - use safe checks
        if (check_if_died(rules) || check_if_all_eaten(rules) || check_if_philo_done(philo))
            break;

        // Take forks and eat
        take_forks(philo);
        if (rules->nb_philo > 1) // already handled in take_forks for 1
            finish_eating(philo);

        // Check again after eating in case this philosopher just finished
        if (check_if_philo_done(philo))
            break;

        // Sleep - use safe check
        if (check_if_died(rules))
            break;
        print_action(philo, "is sleeping");
        smart_sleep(rules->time_to_sleep, rules);

        // Think - use safe check
        if (check_if_died(rules))
            break;
        print_action(philo, "is thinking");
    }
    return NULL;
}

