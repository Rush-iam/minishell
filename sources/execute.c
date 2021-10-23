/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:39:48 by ngragas           #+#    #+#             */
/*   Updated: 2021/10/11 22:05:52 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_list *cmd_list, t_state *state)
{
	t_list	*cursor;
	t_cmd	*cmd;

	cursor = cmd_list;
	while (cursor)
	{
		cmd = get_cooked_cmd((t_cmd *)cursor->content);
		/*
		** - Если stdout команды присоединен к каналу, добавить канал последним
		**   в список редиректов redirect_out;
		**
		** - Если stdin команды присоединен к каналу, добавить его первым
		**   в список редиректов redirect_in;
		**
		** - Открыть последовательно все файлы редиректов (в т.ч. каналы), либо
		**   заменяя их с пом dup* на дескрипторы STDIN_FILENO и STDOUT_FILENO
		**   (в итоге, как в bash, запись пойдет только в последний файл вывода,
		**   а чтение только из последнего файла ввода), либо, как в zsh,
		**   последовательно читать из всех файлов ввода и писать во все файлы
		**   вывода, не заменяя их дескрипторы на дескрипторы стандартных
		**   потоков ввода и вывода;
		**
		** - Запустить команду в форке и сохранить pid в список children_to_wait;
		*/
		(void)state;
		if (cursor->next == NULL || cmd->next_operator != OPERATOR_PIPE)
		{
			(void)0;
			/*
			** - Ждать каждый процесс из списка state->children_to_wait
			** - Cохранить код возврата последнего ребенка, в state->cmd_retval
			** - Очистить список children_to_wait
			*/
		}
		cursor = cursor->next;
	}
}
