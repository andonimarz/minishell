/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:44:56 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/29 10:45:13 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS2_H
# define UTILS2_H
# include "utils.h"

char* erase_quotes(char *str);
 int	count_index(char *str);
//t_data	*ft_lstnew2(void *content);
void	ft_lstadd_back2(t_data **lst, t_data *new);
t_data	*ft_lstlast2(t_data *lst);
t_data *put_last_node(t_data *nodes);

#endif
