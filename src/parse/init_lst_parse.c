/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouyssi <hbouyssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:07 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/05/24 11:03:47 by hbouyssi         ###   ########.fr       */
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
	size_t	i = 0;
	size_t	count = 0;
	int			quote;

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

// j'arrete strtok quand je trouve '>' ou '<'
char	*tok_stop_redir(char *str, size_t i)
{
	char	c;
	char	*tok;

	c = str[i];
	str[i] = 0;
	tok = ft_strdup(str);
	str[i] = c;
	return (tok);
}

// strtok les redirections
char	*tok_redir(char *str, size_t *i)
{
	char	*tok;
	int		quote;

	*i = 0;
	quote = 0;
	while (str[*i] == '<' || str[*i] == '>')
		*i = *i + 1;
	while (str[*i] && ((str[*i] != '<' && str[*i] != '>') || quote != 0))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			quote = manage_quotes(str[*i], quote);
		*i = *i + 1;
	}
	tok = tok_stop_redir(str, *i);
	return (tok);
}

// je decoupe la string avec des separateurs a la facon d'un GNL
char	*ft_strtok(char	*str, char sep, bool redir)
{
	static char	*ptr;
	char		*tok;
	size_t		i;
	int			quote;

	quote = 0;
	i = 0;
	if (str)
	{
		ptr = str;
		while (*ptr == sep)
			ptr++;
	}
	else if (!ptr || !*ptr)
		return (NULL);
	if (redir && (*ptr == '>' || *ptr == '<'))
	{
		tok = tok_redir(ptr, &i);
		ptr = &ptr[i];
		return (tok);
	}
	while (ptr[i] && (ptr[i] != sep || quote != 0))
	{
		if (ptr[i] == '\'' || ptr[i] == '\"')
			quote = manage_quotes(ptr[i], quote);
		if (quote == 0 && redir && (ptr[i] == '<' || ptr[i] == '>'))
			break;
		i++;
	}
	if (quote == 0 && redir && (ptr[i] == '<' || ptr[i] == '>'))
		tok = tok_stop_redir(ptr, i);
	else if (ptr[i] == sep && quote == 0)
	{
		ptr[i] = 0;
		tok = ft_strdup(ptr);
		while (ptr[i] && ptr[i] == sep)
			i++;
	}
	else
		tok = ft_strdup(ptr);
	ptr = &ptr[i];
	return (tok);
}

// on construit la structure cmd
char	**init_cmd(t_data *data ,char *argv)
{
	t_node_cmd	*ptr;
	char		**pips;
	size_t		i;
	char		*tok;

	i = 0;
	data->number_of_pip = ft_count_str(argv, '|') - 1;
	data->number_of_cmd = data->number_of_pip + 1;
	pips = malloc(sizeof(char *) * (data->number_of_cmd + 1));
	tok = ft_strtok(argv, '|', false);
	while (tok)
	{
		pips[i] = tok;
		tok = ft_strtok(NULL, '|', false);
		i++;
	}
	pips[i] = NULL;
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
	return (NULL);
}

char	*trim_redir(char *tok, int i)
{
	char	*str;

	while (tok[i] && (tok[i] == ' ' || tok[i] == '\t'))
		i++;
	str = ft_strdup(&tok[i]);
	free(tok);
	return (str);
}

// je remplis la liste chainee t_redir
t_redir	*fill_redirs(char *tok)
{
	t_redir	*redir;
	t_redir	*ptr;

	if (*tok == '>')
	{
		if (tok[1] == '>')
			redir = redir_lst_new(4, trim_redir(tok, 2));
		else
			redir = redir_lst_new(2, trim_redir(tok, 1));
	}
	else if (*tok == '<')
	{
		if (tok[1] == '<')
			redir = redir_lst_new(3, trim_redir(tok, 2));
		else
			redir = redir_lst_new(1, trim_redir(tok, 1));
	}
	else
		return (NULL);
	ptr = redir;
	tok = ft_strtok(NULL, ' ', true);
	while (tok)
	{
		if (*tok == '>')
		{
			if (tok[1] == '>')
			{
				trim_redir(tok, 1);
				ptr->next = redir_lst_new(4, trim_redir(tok, 2));
			}
			else
				ptr->next = redir_lst_new(2, trim_redir(tok, 1));
		}
		else if (*tok == '<')
		{
			if (tok[1] == '<')
				ptr->next = redir_lst_new(3, trim_redir(tok, 2));
			else
				ptr->next = redir_lst_new(1, trim_redir(tok, 1));
		}
		tok = ft_strtok(NULL, ' ', true);
		ptr = ptr->next;
	}
	return (redir);
}

// ca remplit cmd->content donc par exemple : [echo] [-n] [salut]
t_node_cmd	*cmd_get_content(char *str, size_t index)
{
	size_t	i;
	char	*tok;
	t_node_cmd *cmd;

	i = 0;
	cmd = ft_lstnew_cmd(index);
	cmd->content = malloc(sizeof(char *) * (ft_count_str(str, ' ') + 1));
	cmd->content[i] = ft_strtok(str, ' ', true);
	i++;
	tok = ft_strtok(NULL, ' ', true);
	while (tok)
	{
		if (*tok == '>' || *tok == '<')
		{
			cmd->redir = fill_redirs(tok);
			break;
		}
		cmd->content[i] = tok;
		i++;
		tok = ft_strtok(NULL, ' ', true);
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
// 		while (ptr->redir)
// 		{
// 			if (ptr->redir->in)
// 				printf("in : ");
// 			if (ptr->redir->out)
// 				printf("out : ");
// 			if (ptr->redir->rdocs)
// 				printf("rdocs : ");
// 			if (ptr->redir->d_out)
// 				printf("d_out : ");
// 			printf("%s\n", ptr->redir->content);
// 			ptr->redir = ptr->redir->next;
// 		}
// 		printf("\n");
// 		ptr = ptr->next;
// 		i++;
// 	}
// 	ft_lstclear_cmd(&data->cmd);
// 	free(data);
// 	return (0);
// }
