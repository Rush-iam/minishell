/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:51:41 by dpowdere          #+#    #+#             */
/*   Updated: 2021/10/21 18:51:56 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up(t_state *state)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
		free(*env++);
	free(environ);
	if (state->is_input_interactive)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	free_token(void *token_content)
{
	free(((t_token *)token_content)->string);
	free(token_content);
}

void	free_redirect(void *redirect_content)
{
	free(((t_redirect *)redirect_content)->word);
	free(redirect_content);
}

void	free_cmd(void *cmd_content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_content;
	free(cmd);
	ft_lstclear(&cmd->args_list, free);
	ft_lstclear(&cmd->redirect_in, free_redirect);
	ft_lstclear(&cmd->redirect_out, free_redirect);
	free(cmd_content);
}