/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahosni <fahosni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:19:58 by fahosni           #+#    #+#             */
/*   Updated: 2025/09/13 16:19:59 by fahosni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_mutexes(&rules))
		return (1);
	rules.philos = malloc(sizeof(t_philo) * rules.nb_philo);
	if (!rules.philos)
	{
		cleanup(NULL, rules.forks, &rules);
		return (1);
	}
	init_philosophers(&rules, rules.philos);
	start_simulation(&rules);
	cleanup(rules.philos, rules.forks, &rules);
	return (0);
}
