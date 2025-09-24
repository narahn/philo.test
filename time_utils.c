/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narah <narah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:20:45 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/24 16:40:05 by narah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// long	current_time_ms(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// void smart_sleep(int ms, t_rules *rules)
// {
//     long start = current_time_ms();
//     while (current_time_ms() - start < ms)
//     {
//         if (rules->someone_died)
//             break;
//         usleep(500); // sleep in small chunks
//     }
// }

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void smart_sleep(int ms, t_rules *rules)
{
    long start = current_time_ms();
    while (current_time_ms() - start < ms)
    {
        // Safely check if someone died with mutex protection
        pthread_mutex_lock(&rules->death_mutex);
        int died = rules->someone_died;
        pthread_mutex_unlock(&rules->death_mutex);
        
        if (died)
            break;
        usleep(500); // sleep in small chunks
    }
}
