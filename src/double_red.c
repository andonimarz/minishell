/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:07:06 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/18 18:21:12 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "signals.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>

char	*add_line_break(char *aux, char *str)
{
	char	*array;

	array = aux;
	aux = ft_strjoin(aux, "\n");
	free(array);
	array = aux;
	aux = ft_strjoin(aux, str);
	free(array);
	return (aux);
}

char	*double_redirection(char *key)
{
	char	*aux;
	char	*str;

	aux = 0;
	while (1)
	{
		ft_signals_in_cat();
		str = readline("heredoc> ");
		if (!ft_strncmp(str, key, __INT_MAX__))
			break ;
		if (!aux)
			aux = ft_strdup(str);
		else
			aux = add_line_break(aux, str);
		free(str);
	}
	free(str);
	return (aux);
}
