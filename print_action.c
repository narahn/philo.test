#include "philo.h"

void print_action(t_philo *philo, const char *msg)
{
    t_rules *rules = philo->rules;

    pthread_mutex_lock(&rules->death_mutex);
    int died = rules->someone_died;
    pthread_mutex_unlock(&rules->death_mutex);
    
    if (!died)
    {
        pthread_mutex_lock(&rules->print_mutex);
        printf("%ld %d %s\n", current_time_ms() - rules->start_time, philo->id, msg);
        pthread_mutex_unlock(&rules->print_mutex);
    }
}
