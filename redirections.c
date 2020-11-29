#include "minishell.h"

#define READ 0
#define WRITE 1
#define APPEND 2

typedef struct	t_red
{
	int		red_type;
	char	*filename;
	int		fd;
	int		error;
	char	*error_msg;
	int		p[2];

}				t_red;

t_red init_red_struct(void)
{
	t_red s;

	s.filename = NULL;
	s.fd = -1;
	s.error = 0;
	s.p[0] = -1;
	s.p[1] = -1;
	return (s);
}

int is_redir_char(const char c)
{
	return (c == '>' || c == '<');
}

int is_white_space(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' ||c == '\r');
}

int jump_to_redir_char(const char *cmd, int *i)
{
	while (cmd[*i] && !(is_redir_char(cmd[*i])))
		++(*i);
	if (!cmd[*i])
		return (0);
	return (1);
}

/*
  Validate that the combinaison of redirection char is a valid one
  Examples:
      1. "> > >"
	  2. "><"
	  3. "<<"
	  4. ">>>"
	  5. ">\0"
  return:
      on error: 0
	  on success: 1
*/
int valid_red_char_combinaison(const char *cmd, int i)
{
	if (!cmd[i])
		return (0);
	return (1);
}

/*
  Identify redirection type of first occurence in given cmd
      - <  = READ   = 0
	  - >  = WRITE  = 1
	  - >> = APPEND = 2
*/
void set_red_type(const char *cmd, int i, t_red *red)
{
	if (cmd[i] == '<')
		red->red_type = READ;
	else if (cmd[i] == '>' && cmd[i + 1] == '>')
		red->red_type = APPEND;
	else
		red->red_type = WRITE;
}

/*
  Validate and set redirection type of first redirection occurence in given cmd
  return:
      on error: -1
	  on success: 0
*/
int manage_redir_type(const char *cmd, int i, t_red *red)
{
	if (!valid_red_char_combinaison(cmd, i))
	{
		red->error = 1;
		red->error_msg = ft_strdup("minishell: error invalid redirection");
		return (-1);
	}
	set_red_type(cmd, i, red);
}

/*
  Increase given index until meeting the begining of a filename
  At this point in the code, only a valid redirection is expected.
*/
int jump_i_to_filename(const char *cmd, int *i)
{
	while (cmd[*i] && is_redir_char(cmd[*i]))
		++(*i);
	while (cmd[*i] && is_white_space(cmd[*i]))
		++(*i);
}

/*
  Count how much char their is in the first filename occurence from given cmd
  Example:
      cmd = "   boid 42 > test2"
	  return: 4
*/
int get_filename_len(const char *cmd, int i)
{
	int len;

	len = 0;
	while (cmd[i] && !is_white_space(cmd[i]) && !is_redir_char(cmd[i]))
	{
		++len;
		++i;
	}
	return (len);
}

/*
  Extract first filename from given cmd and store it in red->filename
  Exemple:
      cmd = ">file0>file1"
	  stored: "file0"
*/
void store_red_filename(char *cmd, int i, t_red *red)
{
	int		name_len;
	char	*filename;

	jump_i_to_filename(cmd, &i);
	name_len = get_filename_len(cmd, i);
	filename = ft_strnew(name_len + 1);
	ft_strncat(filename, cmd + i, name_len);
	red->filename = filename;
}

/*
  Try to open red->filename based on redirection type (for permission)
  and store the fd on success
  return:
      on error: -1
	  on sucess: 0
*/
int store_fd_from_filename(t_red *red)
{
	char *f;

	f = red->filename;
	if (red->red_type == READ)
		red->fd = open(f, O_RDWR, 0600);
	else if (red->red_type == WRITE)
		red->fd = open(f, O_CREAT | O_RDWR | O_APPEND, 0600);
	else if (red->red_type == APPEND)
		red->fd = open(f, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (red->fd == -1)
	{
		red->error = 1;
		/* Possibly manage error based on red->red_type */
		red->error_msg = ft_strdup("Invalid file: ");
		return (-1);
	}
	return (0);
}

/*
  Manage redirection extractaction:
  1. validate redirection chars combinaison
  2. redirection type identification (< or > or >>)
  3. open related filename
  return:
      on error: 0
	  on success: 1
 */
int extract_red(char *cmd, int i, t_red *red)
{
	if (manage_redir_type(cmd, i, red) == -1)
		return (0);
	store_red_filename(cmd, i, red);
	if (store_fd_from_filename(red) == -1)
		return (0);
	return (1);
}

void skip_redir_char(t_red *red, int *i)
{
	if (red->red_type == READ || red->red_type == WRITE)
		++(*i);
	else
		(*i) = (*i) + 2;
}

int manage_redir(char *cmd, t_mini *sh)
{
	t_red red;
	int		i;

	red = init_red_struct();
	i = 0;
	if (!jump_to_redir_char(cmd, &i))
		return (-1);
	while (extract_red(cmd, i, &red))
	{
		ft_printf("_%s_\n", red.filename);
		/* make_io_redirection(cmd[i], filename); */
		/* cmd = remove_redir_from_cmd(cmd); */
		skip_redir_char(&red, &i);
		if (!jump_to_redir_char(cmd, &i))
			return (0);
	}
	if (red.error)
		return (-1);
	return (0);
}

/*
  Check if given string contain a redirection char
  return:
      True: 1
	  False: 0
*/
int redir_in_str(const char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (is_redir_char(s[i]))
			return (1);
	return (0);
}

char **invalid_redir(t_mini *sh)
{
	;
}

char	**check_for_redir(char **arr, t_mini *sh)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = NULL;
	i = -1;
	while (arr[++i])
	{
		ft_printf("boid0\n");
		if (redir_in_str(arr[i]))
		{
			/* ls > boid */
 			/* arr[0] = "ls" */
			/* arr[1] = ">" */
			/* arr[2] = "boid" */
			/* if (lonely_redir_char(arr[i])) */
			/* 	merge_two_args(&arr, i); */
			if (manage_redir(arr[i], sh) == -1)
				return (invalid_redir(sh));
		}
	}
	return (tmp);
}
