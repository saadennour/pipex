/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:40:35 by sfarhan           #+#    #+#             */
/*   Updated: 2022/03/24 18:22:18 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// > < file1 cmd1 | cmd2 > file2
// ./pipex infile cmd1 cmd2 outfile

// int	find_space(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == ' ')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

char	*get_cmd(char *av, char **envp, int i)
{
	int		j;
	char	*path;
	char	**cmd;
	char	**exe;

	j = -1;
	path = envp[i];
	cmd = ft_split(&path[5], ':');
	exe = ft_split(av, ' ');
	if (access(exe[0], F_OK) != -1)
		return (exe[0]);
	while (cmd[++j])
	{
		cmd[j] = ft_strjoin(cmd[j], "/");
		cmd[j] = ft_strjoin(cmd[j], exe[0]);
		if (access(cmd[j], F_OK) != -1)
			return (cmd[j]);
	}
	return (0);
}

char	*get_path(char *av, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (envp[i][0] == 'P')
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				return (get_cmd(av, envp, i));
		}
	}
	exit (0);
	return (0);
}

void	pipex(int file1, int file2, char **av, char **envp)
{
	int		fd[2];
	int		child1;
	int		child2;

	if (pipe(fd) == -1)
	{
		printf ("Error\n");
		exit(0);
	}
	child1 = fork();
	if (child1 < 0)
		perror("Error\n");
	if (child1 == 0)
		elder_child(file1, fd, av, envp);
	child2 = fork();
	if (child2 < 0)
		perror ("Error\n");
	if (child2 == 0)
		younger_child(file2, fd, av, envp);
	close (fd[0]);
	close (fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int		fd1;
	int		fd2;

	if (ac != 5)
	{
		printf("Error\n");
		exit(0);
	}
	fd1 = open (av[1], O_RDONLY);
	fd2 = open (av[4], O_CREAT | O_RDWR);
	if (fd1 == -1 || fd2 == -1)
	{
		printf ("Error\n");
		exit(0);
	}
	pipex(fd1, fd2, av, envp);
	close(fd1);
	close(fd2);
	return (0);
}
