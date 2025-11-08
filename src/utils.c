/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:47:09 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 19:26:46 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect.h"

void free_game(t_game *game)
{
	if (!game)
		return;
	if (game->board)
	{
		for (int r = 0; r < game->height; r++)
		{
			if (game->board[r])
				free(game->board[r]);
		}
		free(game->board);
	}
	free(game);
}

t_game *copy_game(const t_game *src_game)
{
	t_game *game;

	if (!src_game)
		return NULL;
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return NULL;
	game->round = src_game->round;
	game->game_status = src_game->game_status;
	game->max_moves = src_game->max_moves;
	game->width = src_game->width;
	game->height = src_game->height;
	game->board = ft_calloc(game->height, sizeof(char *));
	if (!game->board)
	{
		free(game);
		return NULL;
	}
	for (int r = 0; r < game->height; r++)
	{
		game->board[r] = (char *)ft_calloc(game->width + 1, sizeof(char));
		if (!game->board[r])
		{
			for (int k = 0; k < r; k++)
				free(game->board[k]);
			free(game->board);
			free(game);
			return NULL;
		}
		ft_memcpy(game->board[r], src_game->board[r], game->width);
		game->board[r][game->width] = '\0';
	}
	return game;
}

t_game *create_game(int width, int height)
{
	t_game *game;

	if (width <= 0 || height <= 0)
		return (NULL);
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->round = 0;
	game->game_status = 1;
	game->max_moves = width * height;
	game->width = width;
	game->height = height;
	game->board = ft_calloc((size_t)game->height, sizeof(char *));
	if (!game->board)
	{
		free(game);
		return (NULL);
	}
	for (int r = 0; r < game->height; r++)
	{
		game->board[r] = ft_calloc((size_t)game->width + 1, sizeof(char));
		if (!game->board[r])
		{
			for (int k = 0; k < r; k++)
				free(game->board[k]);
			free(game->board);
			free(game);
			return (NULL);
		}
		ft_memset(game->board[r], ' ', game->width);
		game->board[r][game->width] = '\0';
	}
	ft_printfd(STDOUT_FILENO, "\t==========================\n");
	ft_printfd(STDOUT_FILENO, BOLD"\t\tCONNECT4\n"RESET);
	ft_printfd(STDOUT_FILENO, "\t==========================\n\n");
	return (game);
}

void print_board(t_game *game)
{
	int		i, j, w, h;
	char	c;

	if (!game)
		return;
	w = game->width;
	h = game->height;
	ft_printfd(STDOUT_FILENO, "\n\t  ");
	for (j = 0; j < w; j++)
		ft_printfd(STDOUT_FILENO, "| %d ", j + 1);
	ft_printfd(STDOUT_FILENO, "|\n");
	ft_printfd(STDOUT_FILENO, "\t  +");
	for (j = 0; j < w; j++)
		ft_printfd(STDOUT_FILENO, "---+");
	ft_printfd(STDOUT_FILENO, "\n");
	for (i = 0; i < h; i++)
	{
		ft_printfd(STDOUT_FILENO, "\t  |");
		for (j = 0; j < w; j++)
		{
			c = game->board[i][j];
			if (c == 'X')
				ft_printfd(STDOUT_FILENO, " " YELLOW "●" RESET " |");
			else if (c == 'O')
				ft_printfd(STDOUT_FILENO, " " RED "●" RESET " |");
			else
				ft_printfd(STDOUT_FILENO, " %c |", c);
		}
		ft_printfd(STDOUT_FILENO, "\n");
		ft_printfd(STDOUT_FILENO, "\t  +");
		for (j = 0; j < w; j++)
			ft_printfd(STDOUT_FILENO, "---+");
		ft_printfd(STDOUT_FILENO, "\n");
	}
	ft_printfd(STDOUT_FILENO, "\n");
}

void print_game_result(t_game *game)
{
	if (!game)
		return;
	if (game->winner == 'X')
		ft_printfd(STDOUT_FILENO, GREEN"\nCongratulations! You win!\n"RESET);
	else if (game->winner == 'O')
		ft_printfd(STDOUT_FILENO, RED"\nAI wins! Better luck next time.\n"RESET);
	else
		ft_printfd(STDOUT_FILENO, YELLOW"\nIt's a tie!\n"RESET);
}
