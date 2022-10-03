/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:35:02 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/03 13:42:35 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../libft/libft.h"
#include "../includes/environment.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	printf("%s\n", pwd);
	free (pwd);
}

void	ft_chdir(char *dir, char **env)
{
	char	*str;

	str = NULL;
	if (ft_strlen(dir) == 1 && ft_strncmp(dir, "~", 1) == 0)
	{
		str = ft_getenv(env, "HOME");
		printf("HOME = %s\n", str);
		printf("Error = %d\n", chdir(str));
		//free (str);
	}
	else
		chdir(dir);
}

/* int	main(void)
{
	char s[100];
    printf("%s\n", getcwd(s, 100));
    chdir("..");
    printf("%s\n", getcwd(s, 100));
	ft_pwd();
	ft_chdir("/Users/amarzana/proyectos/minishell_pruebas");
	return (0);
}
 */
