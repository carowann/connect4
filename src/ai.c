/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:47:19 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 18:46:12 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect.h"

int is_winning_move(t_game *game, int col)
{
	int row;
	t_game *game_copy;

	row = find_drop_row(game, col);
	if (row == -1)
		return 0;
	game_copy = copy_game(game);
	add_move(game_copy, col);
	int ret = check_win(game_copy, col, row);
	free_game(game_copy);
	return ret;
}

// cambiare ordine di esplorazione, controllare prima gli alberi delle mosse centrali della board.
// codifica bitmap delle posizioni.
int negamax(t_game *game, int alpha, int beta)
{
	int order[] = {3, 2, 4, 1, 5, 0, 6}; // da cambiare in un metodo.
	int i;

	if (check_tie(game))
		return (0);
	i = 0;
	while (i < game->width)
	{
		if (is_winning_move(game, order[i]))
			return (game->width * game->height + 1 - game->round) / 2;
		i++;
	}

	int max = -(game->width * game->height - 1 - game->round) / 2;
	if (beta > max)
	{
		beta = max;
		if (alpha >= beta)
			return beta;
	}
	i = 0;
	while (i < game->width)
	{
		if (find_drop_row(game, order[i]) != -1)
		{
			t_game *G2;
			G2 = copy_game(game);
			add_move(G2, i);
			int score = -negamax(G2, -beta, -alpha);
			free_game(G2);
			if (score >= beta)
				return (score);
			if (score > alpha)
				alpha = score;
		}
		i++;
	}
	return (alpha);
}

int find_best_move(t_game *game)
{
	int best_col = -1;
	int best_score = -(game->height * game->width);
	int i = 0;

	while (i < game->width)
	{
		if (find_drop_row(game, i) != -1)
		{
			t_game *G2 = copy_game(game);
			add_move(G2, i);
			int score = -negamax(G2, -game->max_moves, game->max_moves);
			if (score > best_score)
			{
				best_col = i;
				best_score = score;
			}
			free_game(G2);
		}
		i++;
	}
	return best_col;
}

void ai_move(t_game *game)
{
	if (game->game_status == GAME_OVER)
		return;
	ft_printfd(STDOUT_FILENO, RED"AI is making its move...\n"RESET);
	add_move(game, find_best_move(game));
	game->player_turn = USER_TURN;
}
