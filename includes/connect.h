/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:47:06 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 18:43:13 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT_H
# define CONNECT_H

# include <time.h>
# include "../libft/libft.h"

# define RED	"\033[0;31m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"
# define GREEN	"\033[0;32m"
# define BOLD	"\033[1m"

# define MAX_WIDTH 100
# define MAX_HEIGHT 100
# define ERROR -1
# define GAME_OVER 0
# define USER_TURN 1
# define AI_TURN 2

typedef struct s_game
{
	char **board;
	int width;
	int height;
	int max_moves;
	int round;
	int game_status;
	char winner;
	int *moveorder;
	int player_turn;
}			t_game;


t_game *create_game(int width, int height);
t_game *copy_game(const t_game *src);
int check_win(t_game *game, int column, int row);
void ai_move(t_game *game);
int check_tie(t_game *game);
void free_game(t_game *game);
int find_drop_row(t_game *game, int column);
void print_board(t_game *game);
int add_move(t_game *game, int column);
int	print_usage_and_exit(const char *prog_name);
void	validate_args(char *argv[]);
int	check_user_input(char *line, t_game *game);
size_t ft_count_matrix_row(const void **matrix);
char **ft_duplicate_char_matrix(const char **matrix);
int get_drop_row(t_game *game, int col);
void prompt_player_move(t_game *game);
void rand_first_player(t_game *game);
void print_game_result(t_game *game);
void game_loop(t_game *game);


#endif