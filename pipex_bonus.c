/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:08:47 by asabir            #+#    #+#             */
/*   Updated: 2024/04/16 23:22:56 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void case_1(int (*fd)[2], t_params *tpar, char **argv, int* i)
{
	char *initialize;

	initialize = "initializig";
	if(tpar->path_cmd)
	{
		free(tpar->path_cmd);
		tpar->path_cmd = NULL;
	}
	if(tpar->here_doc == 1)
	{
		fd[tpar->nb_fds][0]= manage_here_doc(argv);
		close(fd[tpar->nb_fds][0]);
		fd[tpar->nb_fds][0] = open("here_doc",O_CREAT | O_RDWR , 0644);
	}
	else
		fd[tpar->nb_fds][0]= open(argv[1], O_RDONLY);
	tpar->cmd = return_cmd_arr(&(tpar->path_cmd), argv[2], tpar->env);
	child_process(fd, fd[tpar->nb_fds][0], fd[*i][1], tpar);
	clean_up(tpar);
	tpar->path_cmd = ft_strdup(initialize);
}

void case_2(int (*fd)[2], t_params *tpar, char **argv, int* i)
{
	if(tpar->path_cmd)
	{
		free(tpar->path_cmd);
		tpar->path_cmd = NULL;
	}	
	tpar->cmd = return_cmd_arr(&(tpar->path_cmd), argv[*i+3], tpar->env);
	fd[tpar->nb_fds][1] = open(argv[tpar->nb_fds+3], O_CREAT | O_RDWR | O_TRUNC, 0644);
	child_process(fd, fd[*i][0], fd[tpar->nb_fds][1], tpar);
	clean_up(tpar);
}

void case_3(int (*fd)[2], t_params *tpar, char **argv, int* i)
{
	char *initialize;

	if(tpar->path_cmd)
	{
		free(tpar->path_cmd);
		tpar->path_cmd = "NULL"; //rje3
	}
	initialize = "initializig";
	tpar->cmd = return_cmd_arr(&(tpar->path_cmd), argv[*i+3], tpar->env);
	child_process(fd, fd[*i][0], fd[*i+1][1], tpar);
	clean_up(tpar);
	tpar->path_cmd = ft_strdup(initialize);
}


void manage_pipes(int nb_fd ,char **argv, t_params *tpar)
{
    int fd[nb_fd+1][2];
    int i;
	
    i = 0;
    while(i < nb_fd)
    {
        if (pipe(fd[i]) == -1)
		    exit(-1);
        i++;
    }
	i = 0;
	
    while(i < nb_fd)
	{
		if(i == 0)
			case_1(fd, tpar,argv,&i);
		if (i == nb_fd-1)
			case_2(fd, tpar,argv,&i);
		if (i != nb_fd-1)
			case_1(fd, tpar,argv,&i);
		i++;
	}

}

int main(int argc, char **argv, char **env)
{
	char *initialize;
	char *error_message;

	error_message = "Error message : type at least four agruments";
	if(argc >= 5)
	{
		t_params *tpar;
		tpar = malloc(sizeof(t_params));
		if(ft_strcmp(argv[1], "here_doc")==0)
		{
			tpar->nb_fds = argc-5;
			argv++;
			tpar->name_infile = "NULL"; //rje3
			tpar->here_doc=1;
		}
		else
		{
			tpar->nb_fds = argc-4;
			tpar->name_infile = argv[1]; //DF case of here_doc
			tpar->here_doc = 0;
		}
		initialize = "initializig";
		tpar->cmd = NULL;
		tpar->path_cmd = ft_strdup(initialize);
		tpar->env = env;
		manage_pipes(tpar->nb_fds, argv, tpar);
		free(tpar);
	}
	else
		write(2, error_message, strlen(error_message));
		
}

