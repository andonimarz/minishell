/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:13:36 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/03 13:29:55 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//Prints the path of the actual working directory
void	ft_pwd(void);

//Changes current working directoy, updating PWD and OLDPWD
void	ft_chdir(char *dir, char **env);

#endif