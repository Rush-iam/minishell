/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:38:40 by ngragas           #+#    #+#             */
/*   Updated: 2021/10/31 22:27:20 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_cmd_subshell(t_list *tokens_list, t_cmd *cmd)
{
	int		brackets_to_close;
	t_token	*token;

	brackets_to_close = 1;
	token = tokens_list->content;
	*token->string = SUBSHELL_MAGIC_BYTE;
	while (brackets_to_close > 0)
	{
		ft_lstadd_back(&cmd->args_list,
			popconvert_tokenlst_to_stringlst(&tokens_list));
		token = tokens_list->content;
		if (token->type == TOKEN_OPERATOR)
		{
			if (get_operator_type(token->string) == SUBSHELL_IN)
				++brackets_to_close;
			else if (get_operator_type(token->string) == SUBSHELL_OUT)
				--brackets_to_close;
		}
	}
	free_token(ft_lstpop(&tokens_list));
	return (tokens_list);
}

static t_list	*get_operator_redirect(t_list *tokens_list, t_cmd *cmd,
										enum e_operator operator)
{
	t_redirect	*redirect;
	t_list		*redirectlst;

	redirectlst = tokens_list;
	tokens_list = tokens_list->next;
	redirectlst->next = NULL;
	redirect = redirectlst->content;
	free(redirect->target);
	redirect->target = ((t_token *)tokens_list->content)->string;
	redirect->type = operator;
	free(ft_lstpop(&tokens_list));
	ft_lstadd_back(&cmd->redirects, redirectlst);
	return (tokens_list);
}

static t_list	*get_operator(t_list *tokens_list, t_cmd *cmd,
							enum e_operator operator)
{
	if (operator == OPERATOR_PIPE
		|| operator == OPERATOR_OR
		|| operator == OPERATOR_AND)
	{
		cmd->next_operator = operator;
		free_token(ft_lstpop(&tokens_list));
	}
	else
		tokens_list = get_operator_redirect(tokens_list, cmd, operator);
	return (tokens_list);
}

t_list	*get_cmd(t_list *tokens_list, t_cmd *cmd)
{
	t_token			*token;
	enum e_operator	operator;

	operator = OPERATOR_NONE;
	while (tokens_list && operator != OPERATOR_PIPE && \
		operator != OPERATOR_OR && operator != OPERATOR_AND)
	{
		token = tokens_list->content;
		if (token->type == TOKEN_WORD)
			ft_lstadd_back(&cmd->args_list,
				popconvert_tokenlst_to_stringlst(&tokens_list));
		else if (token->type == TOKEN_OPERATOR)
		{
			operator = get_operator_type(token->string);
			if (operator == SUBSHELL_IN)
				tokens_list = get_cmd_subshell(tokens_list, cmd);
			else
				tokens_list = get_operator(tokens_list, cmd, operator);
		}
	}
	return (tokens_list);
}

t_list	*get_cmds_list(t_list *tokens_list)
{
	t_cmd	*cmd;
	t_list	*cmdlst;
	t_list	*cmds_list;

	cmds_list = NULL;
	while (tokens_list)
	{
		cmd = ft_calloc(1, sizeof(*cmd));
		cmdlst = ft_lstnew(cmd);
		if (cmd == NULL || cmdlst == NULL)
		{
			free(cmd);
			free(cmdlst);
			ft_lstclear(&tokens_list, free_token);
			return (error(strerror(errno), NULL, cmds_list, free_cmd));
		}
		ft_lstadd_front(&cmds_list, cmdlst);
		tokens_list = get_cmd(tokens_list, cmd);
	}
	return (debug_raw_cmds(ft_lstreverse(&cmds_list)));
}
