/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:36:40 by ngragas           #+#    #+#             */
/*   Updated: 2021/10/20 11:13:05 by dpowdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CLEAR_UNDO_LIST	1

static void	sigint_handler(int signum)
{
	extern int	rl_done;

	(void)signum;
	rl_done = true;
}

// Readline won't react to `rl_done` if this handler is undefined
// and `rl_event_hook` is `NULL`.
int	do_nothing(void)
{
	return (0);
}

static void	suppress_ctrl_chars_echo(void)
{
	struct termios	tty_attrs;

	tcgetattr(STDIN_FILENO, &tty_attrs);
	tty_attrs.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &tty_attrs);
}

void	setup_signal_handlers(t_state *state)
{
	extern rl_hook_func_t	*rl_event_hook;
	extern int				errno;
	struct sigaction		on_quit;
	struct sigaction		on_int;

	if (state->is_input_interactive)
	{
		suppress_ctrl_chars_echo();
		rl_event_hook = do_nothing;
		on_quit = (struct sigaction){};
		on_int = (struct sigaction){};
		on_quit.sa_handler = SIG_IGN;
		on_int.sa_handler = sigint_handler;
		if (sigaction(SIGQUIT, &on_quit, NULL) < 0
			|| sigaction(SIGTERM, &on_quit, NULL) < 0
			|| sigaction(SIGINT, &on_int, NULL) < 0)
		{
			error(strerror(errno), NULL, NULL, NULL);
			clean_up();
			exit(errno);
		}
	}
}

bool	setup_child_signal_handlers(void)
{
	struct sigaction	sigact;

	sigact = (struct sigaction){};
	sigact.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &sigact, NULL) < 0
		|| sigaction(SIGTERM, &sigact, NULL) < 0
		|| sigaction(SIGINT, &sigact, NULL) < 0)
		return (false);
	return (true);
}
