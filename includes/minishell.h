
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "printf.h"
# include <errno.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env			*env;
	char			*oldpwd;
}					t_data;

typedef struct s_cmd
{
	char			**envp;
	char			**args;

}					t_cmd;

t_env				*create_env_list(char **envp);
void				add_env_node(t_env **env_list, char *name, char *value);

// builtin
int					builtin_echo(char **args);
int					builtin_env(t_env *env_list);
int					builtin_pwd(void);
t_env				*builtin_unset(t_env *env, char *cmd);
void				ft_cd(char *path);
void				exec_builtin(char **args, t_env *env_list, char *input);
int					builtin_export(t_env *env_list, char **cmd);
void				builtin_exit(t_env *env_list, char **args, char *input);
void				cleanup(t_env *env_list, char **args, char *input);

// caracteres
int					are_double_quotes_closed(char *input);
int					are_single_quotes_closed(char *input);
int					is_special_char(char c);
void				neutralize_special_char_in_double_quote(char *input);
void				neutralize_special_char_in_single_quote(char *input);

// syntax
void				syntax_special_char(char *input);

// utils
// int					ft_strcmp(char *s1, char *s2);
t_env				*free_list(t_env *a);
// pipe
int					is_quote_closed(char *input);

#endif