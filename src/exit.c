/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 07:51:39 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/29 15:04:43 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "general_function.h"

extern int	g_status;

int	ft_get_exit_nb(char *str, int mode)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	if (mode == 0)
		while (str[i] && str[i] != ')')
			num = num * 10 + (str[i++] - 48);
	else if (mode == 1)
		while (str[i])
			num = num * 10 + (str[i++] - 48);
	return (num * sign);
}

static void	ft_exit_error(char *str, int len)
{
	ft_putstr_fd("minishell: exit: ", 2);
	while (len--)
		write(1, str++, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(0);
}

int	ft_isnum(char *str, int len)
{
	int	i;
	int	isnum;

	i = 0;
	isnum = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i] && i < len)
		if (!ft_isdigit(str[i++]))
			ft_exit_error(str, len);
	return (1);
}

int	ft_exit(char *str)
{
	if (ft_strncmp(str, "exit", 4) == 0 && ft_strlen(str) == 4)
	{
		free(str);
		exit(0);
	}
	else if (ft_strncmp(str, "exit(", 5) == 0 && str[ft_strlen(str) - 1] == ')')
	{
		if (ft_isnum(&str[5], (ft_strlen(str) - 6)))
		{
			free(str);
			exit(ft_get_exit_nb(&str[5], 0));
		}
	}
	else if (ft_strncmp(str, "exit ", 5) == 0)
	{
		if (ft_isnum(&str[5], (ft_strlen(str) - 5)))
		{
			free(str);
			exit(ft_get_exit_nb(&str[5], 1));
		}
	}
	return (0);
}

char	*ft_getenv2(char *s)
{
	if (getenv(s))
		return (getenv(s));
	else if (ft_strncmp(s, "?", ft_strlen(s)) == 0)
		return (ft_itoa(g_status));
	else
		return (NULL);
}
