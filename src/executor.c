/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:13:35 by amarzana          #+#    #+#             */
/*   Updated: 2022/10/16 16:50:00 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fd_stuff.h"
#include "utils.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "double_red.h"
#include "builtins.h"

//Makes required redirections before executing the command
static void	ft_dup_work(t_fd *fd)
{
	if (fd->fdin != -1)
	{
		dup2(fd->fdin, STDIN_FILENO);
		close (fd->fdin);
	}
	if (fd->fdout != -1)
	{
		dup2(fd->fdout, STDOUT_FILENO);
		close (fd->fdout);
	}
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
static void	ft_child(t_data *node, char **envp, t_fd *fd)
{
	int fd1[2];
	pid_t pid;
	ft_dup_work(fd);
	if(fd->here_doc == 1)
	{
		 
		pipe(fd1);
		pid = fork();
		if(pid == 0)
		{	close(fd1[0]);
			dup2(fd1[1], STDOUT_FILENO);
			close(fd1[1]);
			double_redirection(fd->key);
		}
		else if(pid>0)
		{
			 
			close(fd1[1]);
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);
		}
	}
	
	if (execve(node->path, node->cmd, envp) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(node->cmd[0], 2);
		ft_putendl_fd("bash: command not found", 2);
		exit(0);
	}
}

//Creates a pipe and makes a fork.
//Calls ft_child in the child process
//Parent process closes fdin and fdout and waits for the child to end
static void	ft_pipex(t_data *node, char **envp, t_fd *fd)
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
		ft_child(node, envp, fd);
	}
	else
	{
		close(fd->pipe[1]);
		dup2(fd->pipe[0], STDIN_FILENO);
		close (fd->pipe[0]);
		ft_close(fd->fdin);
		fd->fdin = -1;
		ft_close(fd->fdout);
		fd->fdout = -1;
		wait(NULL);
	}
}

//Returns the number of nodes of a linked list
static int	ft_count_nodes(t_data *node)
{
	int		node_nb;

	node_nb = 1;
	while (node->next)
	{
		node_nb++;
		node = node->next;
	}
	return (node_nb);
}

//Checks if given command is ft_builtin
//Returns	1 if cmd is "pwd", "echo" or "env"
//and		2 if cmd is "export", "unset" or "chdir"
int	ft_is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0 || \
		ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 || \
		ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 || \
		ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0 || \
		ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (2);
	return (0);
}

int	ft_check_var(char *var, char *cmd)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		len--;
	i = 0;
	while (var[i] && i < len)
	{
		if (!ft_isalnum(var[i]))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": `", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_call_builtin(char **cmd, char ***envp)
{
	char	*var;

	var = NULL;
	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
	{
		var = ft_subst_var(cmd[1]);
		if (var)
			if (ft_check_var(var, cmd[0]))
				ft_export(var, (ft_strchr(cmd[1], '=') + 1), envp);
	}
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
	{
		if (ft_check_var(cmd[1], cmd[0]))
			ft_unset(cmd[1], envp);
	}
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		ft_chdir(cmd[1], envp);
	if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)	//QUITAR MAS ADELANTE. Se tienen que hacer en el loop
		ft_env(*envp);
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)	//QUITAR MAS ADELANTE
		ft_pwd();
	if (var)
		free(var);
}

//Creates a t_fd structure and calls ft_pipex for every command
// except for the last or if there is only one.
//Closes all used fd and restores original STDIN and STDOUT
void	ft_exec(t_data *node, char ***envp)
{
	int		node_nb;
	int		pid;
	t_fd	fd;

	ft_init_fd(&fd);
	node_nb = ft_count_nodes(node);
	if (node_nb == 1 && ft_is_builtin(node->cmd[0])/* == 2*/)
		ft_call_builtin(node->cmd, envp);
	else
	{
		pid = fork();
		if (pid < 0)
			perror("Error");
		if (pid == 0)
		{
			while (--node_nb)
			{
				ft_pipex(node, *envp, &fd);
				node = node->next;
			}
			ft_dups(node->redirection, &fd);
			ft_child(node, *envp, &fd);
		}
		else
		{
			wait(NULL);
			ft_close_all(&fd);
			ft_reset_fd(&fd);
		}
	}
}
