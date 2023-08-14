/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2021/11/04 22:17:00 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_free(unsigned char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (0);
}

int	ft_error(int code)
{
	if (code == 1)
		ft_printf("Not valid num arguments: ./client <server_pid> <msg>\n");
	else if (code == 2)
		ft_printf("Server_pid must be valid.\n");
	else if (code == 3)
		ft_printf("Malloc error.\n");
	else if (code == 4)
		ft_printf("Server_pid must be the one displayed by a server.\n");
	return (-1);
}

int	ft_isvalid(char *id)
{
	int	int_id;
	int	i;

	i = -1;
	if (*id == '\0' || !id)
		return (0);
	while (id[++i])
	{
		if (!ft_isdigit(id[i]))
			return (0);
	}
	int_id = ft_atoi(id);
	if (int_id < 100 || int_id > 99998)
		return (0);
	return (1);
}

void	ft_check(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("OK\n");
	exit(1);
}
