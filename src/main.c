/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:47:01 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 18:42:20 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/connect.h"

int main(int argc, char *argv[])
{
	int		width, height;
	t_game	*game;

	if (argc != 3)
		print_usage_and_exit(argv[0]);
	validate_args(argv);
	width = ft_atoi(argv[1]);
	height = ft_atoi(argv[2]);
	game = create_game(width, height);
	rand_first_player(game);
	if (game->player_turn == USER_TURN)
		print_board(game);
	game_loop(game);
	print_game_result(game);
	free_game(game);
	return (0);
}
