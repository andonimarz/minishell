/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:35:02 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/05 10:36:41 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/environment.h"
#include "../includes/utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_env(char **env)
{
	while (*env)
		printf("%s\n", *env++);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	printf("%s\n", pwd);
	free (pwd);
}

static char	**ft_add_var(char *var, char *value, char **env)
{
	char	**new_env;
	int		i;
	int		len;

	len = 0;
	while (env[len])
		len++;
	new_env = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i++] = ft_strjoin(var, value);
	new_env[i] = 0;
	return (new_env);
}

void	ft_export(char *var, char *value, char ***env)
{
	int		i;
	int		coin;
	char	**aux;
	char	**env2;

	env2 = *env;
	i = 0;
	coin = 0;
	while (env2[i])
	{
		if (var && ft_strnstr(env2[i], var, ft_strlen(var)))
		{
			free (env2[i]);
			env2[i] = ft_strjoin(var, value);
			coin++;
		}
		i++;
	}
	if (coin == 0)
	{
		aux = ft_add_var(var, value, env2);
		free_d_array(env2);
		*env = aux;
	}
}

void	ft_chdir(char *dir, char **env)
{
	char	*pwd;

	pwd = NULL;
	if (ft_strlen(dir) == 1 && ft_strncmp(dir, "~", 1) == 0)
		dir = ft_getenv(env, "HOME");
	ft_export("OLDPWD=", getcwd(pwd, 0), &env);
	chdir(dir);
	ft_export("PWD=", getcwd(pwd, 0), &env);
}
