/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:25:50 by ngragas           #+#    #+#             */
/*   Updated: 2021/10/31 16:30:19 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	interpret(t_state *state)
{
	t_list	*tokens_list;
	t_list	*cmds_list;

	tokens_list = get_tokens_list(state->line, &state->exit_status);
	if (state->should_free_line)
		free(state->line);
	if (check_tokens(tokens_list) == false)
	{
		state->exit_status = ERR_CODE_PARSE;
		return (0);
	}
	if (errno == ENOMEM)
		return (1);
	cmds_list = get_cmds_list(tokens_list);
	if (errno == ENOMEM)
		return (1);
	execute(cmds_list, &state->exit_status);
	ft_lstclear(&cmds_list, free_cmd);
	return (errno != EXIT_SUCCESS);
}

void	setup_environ(void)
{
	extern char	**environ;

	environ = copy_environ(ENV_DEEP_COPY_TRUE);
	if (environ == NULL)
		exit(errno);
}

void	setup_input(t_state *state, int argc, char **argv)
{
	state->argc = argc;
	state->argv = argv;
	state->should_free_line = DO_FREE_LINE;
	if (isatty(STDIN_FILENO))
	{
		state->read_user_line = readline_stdin_tty;
		state->is_input_interactive = true;
	}
	else if (argc > 1)
	{
		state->should_free_line = DONT_FREE_LINE;
		state->read_user_line = readline_arg;
	}
	else
		state->read_user_line = readline_stdin_non_tty;
}

int	main(int argc, char **argv)
{
	t_state	state;
	int		interpret_error;

	state = (t_state){};
	setup_environ();
	setup_input(&state, argc, argv);
	setup_signal_handlers(&state);
	interpret_error = 0;
	while (interpret_error == 0 && state.read_user_line(&state) > READLINE_EOF)
		interpret_error = interpret(&state);
	clean_up(&state);
	printf("EXIT STATUS %d\n", state.exit_status);
	printf("ERRNO %d: %s\n", errno, strerror(errno));
	if (state.exit_status)
		return (state.exit_status);
	else
		return (errno);
}
