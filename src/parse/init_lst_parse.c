/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:07 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/24 15:41:56 by hbouyssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini/mini.h"

// fonction pour gerer les quotes
int	manage_quotes(char c, int quote)
{
	if (c == '\"')
	{
		if (quote == 0)
			return (2);
		if (quote == 2)
			return (0);
	}
	else if (c == '\'')
	{
		if (quote == 0)
			return (1);
		if (quote == 1)
			return (0);
	}
	return (quote);
}

// je compte les futurs token que je ferai avec strtok pour savoir quoi malloc
size_t	ft_count_str(char *str, char sep)
{
	size_t		i;
	size_t		count;
	int			quote;

	i = 0;
	count = 0;
	quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = manage_quotes(str[i], quote);
		if (i != 0 && str[i] == sep && str[i - 1] != sep && quote == 0)
			count++;
		i++;
	}
	if (i != 0 && str[i - 1] != sep)
		count++;
	return (count);
}

// on construit la structure cmd
void	init_cmd(t_data *data, char *argv)
{
	char		**pips;
	size_t		i;
	char		*tok;

	i = 0;
	data->number_of_pip = ft_count_str(argv, '|') - 1;
	data->number_of_cmd = data->number_of_pip + 1;
	pips = malloc(sizeof(char *) * (data->number_of_cmd + 1));
	tok = ft_strtok(argv, "|", false);
	while (tok)
	{
		pips[i] = tok;
		tok = ft_strtok(NULL, "|", false);
		i++;
	}
	pips[i] = NULL;
	fill_cmd_content(data, pips);
}

void	fill_cmd_content(t_data *data, char **pips)
{
	size_t		i;
	t_node_cmd	*ptr;

	i = 1;
	data->cmd = cmd_get_content(pips[0], 0);
	free(pips[0]);
	ptr = data->cmd;
	while (pips[i])
	{
		ptr->next = cmd_get_content(pips[i], i);
		free(pips[i]);
		ptr = ptr->next;
		i++;
	}
	free(pips);
}

// ca remplit cmd->content donc par exemple : [echo] [-n] [salut]
t_node_cmd	*cmd_get_content(char *str, size_t index)
{
	size_t		i;
	char		*tok;
	t_node_cmd	*cmd;

	i = 0;
	cmd = ft_lstnew_cmd(index);
	cmd->content = malloc(sizeof(char *) * (ft_count_str(str, ' ') + 1));
	cmd->content[i] = ft_strtok(str, " \t", true);
	i++;
	tok = ft_strtok(NULL, " \t", true);
	while (tok)
	{
		if (*tok == '>' || *tok == '<')
		{
			fill_redirs(tok, &cmd->redir);
			break ;
		}
		cmd->content[i] = tok;
		i++;
		tok = ft_strtok(NULL, " \t", true);
	}
	cmd->content[i] = NULL;
	return (cmd);
}

// main de test
// int	main()
// {
// 	t_data	*data = malloc(sizeof(t_data));
// 	char	*str = NULL;
// 	while(!str)
// 		str = readline(NULL);
// 	init_cmd(data, str);
// 	free(str);
// 	t_node_cmd	*ptr = data->cmd;
// 	t_redir *red_ptr;
// 	size_t	i = 0;
// 	size_t	y;
// 	printf("number of pip = %i\n", data->number_of_pip);
// 	while (ptr)
// 	{
// 		printf("node %i:\n", ptr->index);
// 		y = 0;
// 		while (ptr->content[y])
// 		{
// 			printf("%i: %s\n", (int)y, ptr->content[y]);
// 			y++;
// 		}
// 		red_ptr = ptr->redir;
// 		while (red_ptr)
// 		{
// 			if (red_ptr->in)
// 				printf("in : ");
// 			if (red_ptr->out)
// 				printf("out : ");
// 			if (red_ptr->rdocs)
// 				printf("rdocs : ");
// 			if (red_ptr->d_out)
// 				printf("d_out : ");
// 			printf("%s\n", red_ptr->content);
// 			red_ptr = red_ptr->next;
// 		}
// 		printf("\n");
// 		ptr = ptr->next;
// 		i++;
// 	}
// 	ft_lstclear_cmd(&data->cmd);
// 	free(data);
// 	return (0);
// }
