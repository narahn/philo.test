/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narah <narah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:20:35 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/24 17:20:13 by narah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_rules	t_rules;

struct s_rules
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    int someone_died;
    int finished_eating;
    pthread_mutex_t finished_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t *forks;
    long start_time;
    t_philo *philos;
};

struct s_philo
{
    int id;
    int meals_eaten;
    long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_rules *rules;
};

int						ft_atoi(const char *str);
int						parse_args(int argc, char **argv, t_rules *rules);
long					current_time_ms(void);
void					*philo_routine(void *arg);
void					init_philosophers(t_rules *rules, t_philo *philos);
int						init_mutexes(t_rules *rules);
void					*monitor(void *arg);
void					start_simulation(t_rules *rules);
void					cleanup(t_philo *philos, pthread_mutex_t *forks,
							t_rules *rules);
void 					take_forks(t_philo *philo);
void smart_sleep(int ms, t_rules *rules);
void print_action(t_philo *philo, const char *msg);

#endif
