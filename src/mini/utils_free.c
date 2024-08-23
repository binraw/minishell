#include "./mini.h"

void	ft_lstclear_content(t_node_cmd *current)
{
	size_t	i;

	i = 0;
	while (current->content[i])
	{
		free(current->content[i]);
		i++;
	}
	free(current->content[i]);
	free(current->content);
}
