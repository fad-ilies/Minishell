/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:02:11 by ifadhli           #+#    #+#             */
/*   Updated: 2025/06/30 23:34:05 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_pipe(char *input)
{
    int     i;

    i = 0;
    while (input[i] == ' ')
        i++;
    if (input[i] == '|')
    {
        ft_putendl_fd("syntax error near unexpected token `|'", STDERR_FILENO);
        return ;
    }
    i = ft_strlen(input) - 1;

    if (input[i] == '|')
        ft_putendl_fd("bash: syntax error: unexpected end of file", STDERR_FILENO);
    i = 0;
    while (input[i])
    {
        if (input[i] == '|' && input[i + 1] == '|')
            ft_putendl_fd("syntax error near unexpected token `|'", STDERR_FILENO);
        i++;            
    }
}

void	neutralize_special_char_in_single_quote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && (input[i] == '\''))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else if (quote && (is_special_char(input[i]) || input[i] == '$'))
			input[i] *= -1;
		i++;
	}
	printf("BUFFER : %s\n", input);
}

void	neutralize_special_char_in_double_quote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && input[i] == '"')
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else if (quote && is_special_char(input[i]))
			input[i] *= -1;
		i++;
	}
}


int	is_quote_closed(char *input)
{
	int		i;
	char	first_quote;
	int		open;

	i = 0;
	first_quote = 0;
	open = 0;
	while (input[i])
	{
		if (!first_quote && (input[i] == '\'' || input[i] == '\"'))
		{
			first_quote = input[i];
			open = 1;
		}
		else if (input[i] == first_quote)
			open = !open;
		i++;
	}
	if (open)
	{
		if (first_quote == '\'')
			ft_putendl_fd("syntax error: unclosed single quote", STDERR_FILENO);
		else if (first_quote == '\"')
			ft_putendl_fd("syntax error: unclosed double quote", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '>' || c == '<');
}

void	token_error(char c)
{
	write(STDERR_FILENO, "syntax error near unexpected token `", 37);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "'\n", 2);
}

void	syntax_special_char(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (is_special_char(input[i]))
		return (token_error(input[i]));
	i = ft_strlen(input) - 1;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (i >= 0 && is_special_char(input[i]))
	{
		ft_putendl_fd("bash: syntax error: unexpected end of file",
			STDERR_FILENO);
		return ;
	}
	i = 0;
	while (input[i] && input[i + 1])
	{
		if (is_special_char(input[i]) && is_special_char(input[i + 1]))
			return (token_error(input[i + 1]));
		i++;
	}
}