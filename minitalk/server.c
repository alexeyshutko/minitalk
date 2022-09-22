/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:03:36 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/03/13 13:52:59 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include<signal.h>
#include<unistd.h>

int	g_i;

void	handler(int signum)
{
	static unsigned char	a = 0;

	if (signum == SIGUSR2)
	{
	a = a | 1;
	}
		g_i++;
	if (g_i == 8)
	{
		write(1, &a, 1);
		g_i = 0;
		a = 0;
	}
	else
		a = a << 1;
}

int	main(void)
{
	printf("Process id: %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	g_i = 0;
	while (1)
		sleep(5);
	return (0);
}
