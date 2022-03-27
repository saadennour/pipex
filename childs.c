/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:31:16 by sfarhan           #+#    #+#             */
/*   Updated: 2022/03/24 18:38:04 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	elder_child(int file, int *fd, char **av, char **envp)
{
	char	*cmd;
	char	**exe;

	cmd = get_path(av[2], envp);
	if (!cmd)
		exit(0);
	exe = ft_split(av[2], ' ');
	dup2(file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(cmd, exe, envp);
}

void	younger_child(int file, int *fd, char **av, char **envp)
{
	char	*cmd;
	char	*buff;
	char	**exe;

	buff = NULL;
	if (read(fd[1], buff, 1) == 0)
	{
		printf ("Error \n");
		exit(1);
	}
	cmd = get_path(av[3], envp);
	if (!cmd)
		exit(0);
	exe = ft_split(av[3], ' ');
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(cmd, exe, envp);
}
