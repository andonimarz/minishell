/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:13:36 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/05 10:37:57 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//Prints the path of the actual working directory
void	ft_pwd(void);

//Changes current working directoy, updating PWD and OLDPWD
void	ft_chdir(char *dir, char **env);

//Adds/replaces variable in environment
//Hay que meter '=' después de var porque si no puede confundir
//variables que empiecen igual.
void	ft_export(char *var, char *value, char ***env);

//Prints the env
void	ft_env(char **env);

//Removes variable from environment
//Si no coincide no hace nada
//Hay que meter '=' después de var porque si no puede confundir
//variables que empiecen igual.
void	ft_unset(char *var, char ***env);
#endif