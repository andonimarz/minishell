/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:35 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/26 13:12:42 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "double_red.h"
#include "fd_utils.h"
#include "utils.h"
#include "executor.h"
#include "builtins.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

//Makes required redirections before executing the command
static int	ft_dup_work(t_fd *fd, int mode)
{
	if (fd->fdin == -1)
	{
		close(fd->fdin);
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		if (mode == 0)
			exit (1);
		return (0);
	}
	if (mode == 1)
		fd->fdin = -2;
	if (fd->fdin >= 0)
	{
		dup2(fd->fdin, STDIN_FILENO);
		close (fd->fdin);
	}
	if (fd->fdout >= 0)
	{
		dup2(fd->fdout, STDOUT_FILENO);
		close (fd->fdout);
	}
	return (1);
}

//Calls ft_get_fd for every redirection
static void	ft_dups(char **redir, t_fd *fd)
{
	int	i;

	i = 0;
	if (redir != NULL)
	{
		while (redir[i])
		{
			if (ft_strncmp(redir[i], "<", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 0, fd);
			else if (ft_strncmp(redir[i], ">", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 1, fd);
			else if (ft_strncmp(redir[i], ">>", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 2, fd);
			else if (ft_strncmp(redir[i], "<<", ft_strlen(redir[i])) == 0)
				ft_get_fd(redir[i + 1], 3, fd);
			i++;
		}
	}
}

//Makes the required dups and executes the command
static void	ft_child(t_data *node, char **envp, t_fd *fd, int ret)
{
	ft_dup_work(fd, 0);
	if (node->cmd)
	{
		if (ft_is_builtin(node->cmd))
		{
			ft_call_builtin(node->cmd, &envp);
			ret = 0;
		}
		else if (execve(node->path, node->cmd, envp) == -1)
			ft_putendl_fd("Un comando malo ha llegado a ft_child", 2);
	}
	free(node->path);
	exit(ret);
}

//Creates a pipe and makes a fork.
//Calls ft_child in the child process
//Parent process closes fdin and fdout and waits for the child to end
static void	ft_pipex(t_data *node, char **envp, t_fd *fd, int ret)
{
	pid_t	pid;

	ft_dups(node->redirection, fd);
	pipe(fd->pipe);
	pid = fork();
	if (pid < 0)
		perror("Error");
	if (pid == 0)
	{
		close(fd->pipe[0]);
		dup2(fd->pipe[1], STDOUT_FILENO);
		close (fd->pipe[1]);
		ft_child(node, envp, fd, ret);
	}
	else
	{
		close(fd->pipe[1]);
		dup2(fd->pipe[0], STDIN_FILENO);
		close (fd->pipe[0]);
		ft_close(&fd->fdin, 1);
		ft_close(&fd->fdout, 1);
		waitpid(pid, &ret, 0);
	}
}

int	ft_check_cmd(t_data *node, t_fd *fd, int *ret, int mode)
{
	if (node->path || ft_is_builtin(node->cmd))
		return (1);
	*ret = 32512;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmd[0], 2);
	ft_putendl_fd(" command not found", 2);
	ft_close(&fd->fdin, 1);
	ft_close(&fd->fdout, 1);
	if (mode == 1)
	{
		close(0);
		close(1);
	}
	ft_reset_fd(fd);
	return (0);
}

void	ft_exec(t_data *node, char ***envp)
{
	int		node_nb;
	int		pid;
	t_fd	fd;
	int		ret;

	ft_init_fd(&fd);
	node_nb = ft_count_nodes(node);
	signal(SIGINT, SIG_IGN);
	if (node_nb == 1 && ft_is_builtin(node->cmd) == 2)
	{
		ft_dups(node->redirection, &fd);
		ft_close(&fd.fdin, 0);
		if (ft_dup_work(&fd, 1))
			ft_call_builtin(node->cmd, envp);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			perror("Error");
		if (pid == 0)
		{
			while (--node_nb)
			{
				if (ft_check_cmd(node, &fd, &ret, 1))
					ft_pipex(node, *envp, &fd, ret);
				node = node->next;
			}
			if (ft_check_cmd(node, &fd, &ret, 0))
			{
				ft_dups(node->redirection, &fd);
				ft_child(node, *envp, &fd, ret);
			}
		}
		else
		{
			waitpid(pid, &ret, 0);
			printf("STATUS exec = %d\n", ret);
		}
	}
	ft_close_all(&fd);
	ft_reset_fd(&fd);
}
