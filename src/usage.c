/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:26:42 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/08 16:27:04 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/connect.h"

int	print_usage_and_exit(const char *prog_name)
{
	ft_printfd(STDERR_FILENO, "Usage: %s <grid_width> <grid_height>\n\n", prog_name);
	ft_printfd(STDERR_FILENO, "Both grid_width and grid_height must be integers greater than or equal to 7 and 6 respectively.\n");
	ft_printfd(STDERR_FILENO, "Grid width and height must be less than or equal to %d and %d respectively.\n", MAX_WIDTH, MAX_HEIGHT);
	exit(EXIT_FAILURE);
}

static void	validate_format(const char *prog_name, char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i = 1;
	if (!arg[i])
		print_usage_and_exit(prog_name);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			print_usage_and_exit(prog_name);
		i++;
	}
	return ;
}

void	validate_args(char *argv[])
{
	long	width;
	long	height;

	validate_format(argv[0], argv[1]);
	width = ft_atol(argv[1]);
	if (width < 7 || width > MAX_WIDTH)
		print_usage_and_exit(argv[0]);
	validate_format(argv[0], argv[2]);
	height = ft_atol(argv[2]);
	if (height < 6 || height > MAX_HEIGHT)
		print_usage_and_exit(argv[0]);
}

int	check_user_input(char *line, t_game *game)
{
	long	move;

	if (!line)
		return (ERROR);
	move = ft_atol(line);
	if (move < 1 || move > game->width)
	{
		ft_printfd(STDOUT_FILENO, "Invalid move. Please enter a column between 1 and %i.\n", game->width);
		return (ERROR);
	}
	return (0);
}
