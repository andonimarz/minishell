/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:31:39 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/18 13:51:32 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "utils.h"

void	ft_signals_rl(void);
void	ft_signals(void);
void	rl_replace_line(const char *text, int clear_undo);
void	ft_check_rl(char *str, t_data **data);

#endif