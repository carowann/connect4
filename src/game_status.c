/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:35:57 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 19:28:02 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/connect.h"

int check_tie(t_game *game)
{
	if (game->round >= game->max_moves)
	{
		game->game_status = 0;
		return (1);
	}
	return (0);
}

static int check_horizontal(t_game *game, char player)
{
	int r, c, count;

	r = 0;
	while (r < game->height)
	{
		c = 0;
		count = 0;
		while (c < game->width)
		{
			if (game->board[r][c] == player)
			{
				count++;
				if (count >= 4)
					return (1);
			}
			else
				count = 0;
			c++;
		}
		r++;
	}
	return (0);
}

// vertical scan top to bottom
static int check_vertical(t_game *game, char player)
{
	int c, r, count;

	c = 0;

	while (c < game->width)
	{
		r = 0;
		count = 0;
		while (r < game->height)
		{
			if (game->board[r][c] == player)
			{
				count++;
				if (count >= 4)
					return (1);
			}
			else
				count = 0;
			r++;
		}
		c++;
	}
	return (0);
}

// diagonal top-left -> bottom-right
static int check_diag_tl_br(t_game *game, char player)
{
	int start_c, start_r, r, c, count;

	start_c = 0;
	while (start_c <= game->width - 4)
	{
		r = 0;
		c = start_c;
		count = 0;
		while (r < game->height && c < game->width)
		{
			if (game->board[r][c] == player)
			{
				count++;
				if (count >= 4)
					return (1);
			}
			else
				count = 0;
			r++;
			c++;
		}
		start_c++;
	}
	start_r = 1;
	while (start_r <= game->height - 4)
	{
		r = start_r;
		c = 0;
		count = 0;
		while (r < game->height && c < game->width)
		{
			if (game->board[r][c] == player)
			{
				count++;
				if (count >= 4)
					return (1);
			}
			else
				count = 0;
			r++;
			c++;
		}
		start_r++;
	}
	return (0);
}

static int check_diag_bl_tr(t_game *game, char player)
{
	int start_c, start_r, r, c, count;

	start_c = 0;
	while (start_c <= game->width - 4)
	{
		r = game->height - 1;
		c = start_c;
		count = 0;
		while (r >= 0 && c < game->width)
		{
			if (game->board[r][c] == player)
			{
				count++;
				if (count >= 4)
					return (1);
			}
			else
				count = 0;
			r--;
			c++;
		}
		start_c++;
	}
	start_r = game->height - 2;
	while (start_r >= 3)
	{
		r = start_r;
		c = 0;
		count = 0;
		while (r >= 0 && c < game->width)
		{
			if (game->board[r][c] == player)
			{
				count++;
				if (count >= 4)
					return (1);
			}
			else
				count = 0;
			r--;
			c++;
		}
		start_r--;
	}
	return (0);
}

int check_win(t_game *game, int column, int row)
{
	char player;

	if (!game || !game->board)
		return (0);
	if (row < 0 || row >= game->height || column < 0 || column >= game->width)
		return (0);

	player = game->board[row][column];
	if (player == ' ' || player == '\0')
		return (0);
	if (check_horizontal(game, player))
		return (1);
	if (check_vertical(game, player))
		return (1);
	if (check_diag_tl_br(game, player))
		return (1);
	if (check_diag_bl_tr(game, player))
		return (1);
	return (0);
}
