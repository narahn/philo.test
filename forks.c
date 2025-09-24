# include "philo.h"

int try_lock_fork(pthread_mutex_t *fork, t_philo *philo)
{
    while (!philo->rules->someone_died)
    {
        if (pthread_mutex_trylock(fork) == 0)
            return 1;
        usleep(100);
    }
    return 0;
}

void take_forks(t_philo *philo)
{
    if (philo->rules->someone_died)
        return;
    if (!try_lock_fork(philo->left_fork, philo))
        return;
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->someone_died)
        printf("%ld %d has taken a fork\n",
            current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
    if (philo->rules->nb_philo == 1)
    {
        usleep(philo->rules->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    if (!try_lock_fork(philo->right_fork, philo))
    {
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    pthread_mutex_lock(&philo->rules->print_mutex);
    if (!philo->rules->someone_died)
        printf("%ld %d has taken a fork\n",
            current_time_ms() - philo->rules->start_time, philo->id);
    pthread_mutex_unlock(&philo->rules->print_mutex);
}
