/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:37:20 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/23 15:35:45 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_outoflimit(long n, int s, int count)
{
	if (n > 9223372036854775807 || count > 19)
		return (-1);
	n = n * s;
	return (n);
}

int	ft_skipzero(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (!ft_isdigit(str[i]) && i > 0)
		i--;
	return (i);
}

long	ft_atoi(char *str)
{
	int		s;
	int		i;
	long	nbr;
	int		count;

	(1) && (i = 0, s = 1, nbr = 0, count = 0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	i = i + ft_skipzero(str + i);
	while (ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i] - 48);
		count++;
		i++;
	}
	if (str[i])
		return (-1);
	return (ft_outoflimit(nbr, s, count));
}
