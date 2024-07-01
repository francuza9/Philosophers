/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:35:35 by gtskitis          #+#    #+#             */
/*   Updated: 2024/04/23 23:35:37 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_atoi(char *str)
{
	long int	num;
	int			i;

	num = 0;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = (num * 10) + (str[i] - '0');
		else
			return (-1);
		i++;
	}
	if (num > MAX_INT)
		return (-1);
	return ((int)num);
}

bool	wrong_input(char **argv)
{
	if ((ft_atoi(argv[0]) < 1 || ft_atoi(argv[0]) > MAX_PHILOS) \
	|| ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 \
	|| ft_atoi(argv[3]) < 0 \
	|| (argv[4] && ft_atoi(argv[4]) <= 0))
	{
		write(2, "Invalid arguments.\n", 19);
		return (true);
	}
	return (false);
}
