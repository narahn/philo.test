# include "philo.h"

void print_action(t_philo *philo, const char *msg)
{
    t_rules *rules = philo->rules;

    pthread_mutex_lock(&rules->print_mutex);
    pthread_mutex_lock(&rules->death_mutex);
    if (!rules->someone_died)
        printf("%ld %d %s\n", current_time_ms() - rules->start_time, philo->id, msg);
    pthread_mutex_unlock(&rules->death_mutex);
    pthread_mutex_unlock(&rules->print_mutex);
}
