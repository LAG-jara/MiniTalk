/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	itobit(int octet, int pid)
{
	int	aux;

	aux = 32;
	while (aux--)
	{
		if ((octet >> aux) % 2)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(ft_error(4));
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(ft_error(4));
		}
		usleep(200);
	}
}

void	chartobit(unsigned char octet, int pid)
{
	int	aux;

	aux = 8;
	while (aux--)
	{
		if ((octet >> aux) % 2)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(ft_error(2));
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(ft_error(2));
		}
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = -1;
	if (ac != 3)
		return (ft_error(1));
	if (!ft_isvalid(av[1]))
		return (ft_error(2));
	signal(SIGUSR2, ft_check);
	pid = ft_atoi(av[1]);
	itobit((int)ft_strlen(av[2]), pid);
	while (av[2][++i])
		chartobit((unsigned char)av[2][i], pid);
	chartobit('\0', pid);
	while (42)
		pause();
	return (0);
}
