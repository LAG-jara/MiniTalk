/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:59:00 by alajara-          #+#    #+#             */
/*   Updated: 2023/08/02 19:35:54 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	int	ft_getlen(int sig, int len)
{
	len <<= 1;
	if (sig == SIGUSR2)
		len += 1;
	return (len);
}

static unsigned char	*ft_setstr(int len)
{
	unsigned char	*s;

	s = ft_calloc(sizeof(unsigned char) * len, sizeof(char));
	if (!s)
		exit(ft_error(3));
	return (s);
}

void	ft_constructbit(int sig, siginfo_t *info, void *context)
{
	static int				sig_cnt = 0;
	static int				len = 0;
	static unsigned char	*s;

	(void)context;
	if (++sig_cnt <= 32)
		len = ft_getlen(sig, len);
	if (sig_cnt == 32)
		s = ft_setstr(++len);
	if (sig_cnt > 32)
	{
		s[(sig_cnt - 33) / 8] <<= 1;
		if (sig == SIGUSR2)
			s[(sig_cnt - 33) / 8] += 1;
	}
	if (sig_cnt == 32 + (len * 8))
	{
		ft_printf("%s\n", s);
		free(s);
		sig_cnt = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(void)
{
	struct sigaction	act;
	int					id;

	act.sa_sigaction = ft_constructbit;
	id = getpid();
	ft_printf("%d\n", id);
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	while (42)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		pause();
	}
	return (0);
}

/*
void	ft_constructbit(int sig)
{
	static int				sig_cnt = 0;
	static int				len = 0;
	static unsigned char	*s;

	if (++sig_cnt <= 32)
		len = ft_getlen(sig, len);
	if (sig_cnt == 32)
	{
		s = ft_calloc(sizeof(unsigned char) * ++len, sizeof(char));
		if (!s)
			exit(ft_error(3));
	}
	if (sig_cnt > 32)
	{
		s[(sig_cnt - 33) / 8] <<= 1;
		if (sig == SIGUSR2)
			s[(sig_cnt - 33) / 8] += 1;
	}
	if (sig_cnt == 32 + (len * 8))
	{
		ft_printf("%s\n", s);
		free(s);
		sig_cnt = 0;
	}
}

int	main(void)
{
	int	id;

	id = getpid();
	ft_printf("%d\n", id);
	while (42)
	{
		signal(SIGUSR1, ft_constructbit);
		signal(SIGUSR2, ft_constructbit);
		pause();
	}
	return (0);
}
*/
