/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:33:02 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 18:24:30 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect.h"

void game_loop(t_game *game)
{
	while (game->game_status != GAME_OVER)
	{
		if (game->player_turn == USER_TURN)
			prompt_player_move(game);
		else
			ai_move(game);
		print_board(game);
		check_tie(game);
	}
}

int	find_drop_row(t_game *game, int col)
{
	if (!game || col < 0 || col >= game->width)
		return (-1);
	for (int row = game->height - 1; row >= 0; row--)
	{
		if (game->board[row][col] == ' ')
			return (row);
	}
	return (-1);
}

int get_drop_row(t_game *game, int col)
{
	int row;

	if (!game || col < 0 || col >= game->width)
		return -1;
	row = find_drop_row(game, col);
	return (row);
}

void prompt_player_move(t_game *game)
{
	int		chosen_col;
	int		row;
	char	*line;

	while (1)
	{
		ft_printfd(STDOUT_FILENO, YELLOW"Play your move {1...%i}\n"RESET, game->width);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return;
		if (check_user_input(line, game) == ERROR)
		{
			free(line);
			continue;
		}
		chosen_col = ft_atoi(line);
		free(line);
		row = get_drop_row(game, chosen_col - 1);
		if (row >= 0)
			break;
	}
	add_move(game, chosen_col - 1);
	game->player_turn = AI_TURN;
}

int	add_move(t_game *game, int col)
{
	int		row;
	char	player_char;

	if (!game)
		return (0);
	player_char = (game->player_turn == USER_TURN) ? 'X' : 'O';
	row = get_drop_row(game, col);
	if (row < 0)
		return (0);
	game->board[row][col] = player_char;
	game->round++;
	if (check_win(game, col, row))
	{
		if (game->player_turn == USER_TURN)
			game->winner = 'X';
		else
			game->winner = 'O';
		game->game_status = 0;
	}
	else
		check_tie(game);
	return (1);
}

void rand_first_player(t_game *game)
{
	if (!game)
		return;
	srand(time(NULL));
	if (rand() % 2 == 0)
		game->player_turn = USER_TURN;
	else
		game->player_turn = AI_TURN;
	if (game->player_turn == USER_TURN)
		ft_printfd(STDOUT_FILENO, YELLOW"You play first!\n"RESET);
	else
		ft_printfd(STDOUT_FILENO, RED"AI goes first!\n"RESET);
}
