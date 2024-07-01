/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:35:31 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:36:03 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong amount of arguments.\n", 27);
		return (1);
	}
	if (wrong_input(argv + 1))
		return (1);
	data = init_data(argc, argv + 1);
	if (!data)
		return (1);
	if (start_exec(data))
		return (1);
	stop_exec(data);
	return (0);
}
