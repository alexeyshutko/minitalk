/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolyxen <gpolyxen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:53:50 by gpolyxen          #+#    #+#             */
/*   Updated: 2022/03/10 17:54:05 by gpolyxen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	atoi(const char *a)
{
	int	num;
	int	i;
	int	flag;

	num = 0;
	flag = 1;
	i = 0;
	while (a[i] == '\f' || a[i] == '\n' || a[i] == ' '
		|| a[i] == '\t' || a[i] == '\v' || a[i] == '\r')
	{
		i++;
	}
	if (a[i] == '-')
	{
		i++;
		flag = -1;
	}
	while (a[i])
	{
		num += a[i] - '0';
		num *= 10;
		i++;
	}
	num /= 10;
	return (num * flag);
}

void	send_char(int pid, unsigned char a)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(100);
		if ((a & 128) == 0)
		{
			kill(pid, SIGUSR1);
		}
		else
			kill(pid, SIGUSR2);
		a = a << 1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc == 3)
	{
		pid = atoi(argv[1]);
		i = 0;
		while (argv[2][i])
		{
			usleep(100);
			send_char(pid, (unsigned char)argv[2][i]);
			i++;
		}
	}
	else
		return (0);
}
