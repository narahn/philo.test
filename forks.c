#include "philo.h"

void take_forks(t_philo *philo)
{
    t_rules *rules = philo->rules;

    if (rules->nb_philo == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        // Wait until death
        smart_sleep(rules->time_to_die, rules);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
    }
}
