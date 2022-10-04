/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:35:02 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/04 11:55:27 by amarzana         ###   ########.fr       */
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

void	ft_export(char *var, char *value, char ***env1)
{
	int		i;
	int		coin;
	char	**aux;
	char	**env;

	env = *env1;
	i = 0;
	coin = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], var, ft_strlen(var)))
		{
			free (env[i]);
			env[i] = ft_strjoin(var, value);
			coin++;
		}
		i++;
	}
	if (coin == 0)
	{
		aux = ft_add_var(var, value, env);
		free_d_array(env);
		*env1 = aux;
		//ft_env(env);
	}
}

void	ft_chdir(char *dir, char **env)
{
	char	*pwd;

	pwd = NULL;
	if (ft_strlen(dir) == 1 && ft_strncmp(dir, "~", 1) == 0)
		dir = ft_getenv(env, "HOME");
	//ft_env(env);
	ft_export("OLDPWD=", getcwd(pwd, 0), &env);
	chdir(dir);
	ft_export("PWD=", getcwd(pwd, 0), &env);
	//ft_export("olajijixd=", "probando", &env);
	ft_env(env);
}
