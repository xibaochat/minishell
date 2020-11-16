#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
char    **check_for_redir(char **arr, t_mini *sh)
{
        int     i;
        int     j;
        char    *file;
        char    **tmp;
        tmp = NULL;
        i = -1;
        while (arr[++i])
        {
                if (arr[i][0] == '<')
                {
                        if (ft_strlen(arr[i]) == 1)
                                if (!(file = arr[i + 1]))
                                        return (NULL);
                        else
                                file = arr[i] + 1;
                        if ((sh->newfd = open(file, O_CREAT | O_RDWR, 0600)) == -1)
                                printf("DEBUG : OPEN FAILED\n");
                        if (dup2(sh->newfd, 0) < 0)
                                printf("DEBUG : DUP2 FAILED\n");
                        close(sh->newfd);
                }
                if (arr[i][0] == '>')
                {
                        if (ft_strlen(arr[i]) == 1)
                        {
                                if (!(file = ft_strdup(arr[i + 1])))
                                        return (NULL);
                                tmp = ft_tabdup(arr, i);
/*                              j = 0;
                                while (tmp[j])
                                        printf("%s\n", tmp[j++]);
                                ft_tabfree(arr);
                                arr = tmp;
                                j = 0;
                                while (arr[j])
                                        printf("arr = %s\n", arr[j++]);
                                tmp = arr;
                                tmp[i] = NULL;*/
                        }
                        else
                        {
                                file = arr[i] + 1;
                                tmp = ft_tabdup(arr, i);
                        }
                        if ((sh->newfd = open(file, O_CREAT | O_RDWR, 0600)) == -1)
                                printf("DEBUG : OPEN FAILED\n");
                        if (dup2(sh->newfd, 1) < 0)
                                printf("DEBUG : DUP2 FAILED\n");
                        close(sh->newfd);
                }
        }
        return (tmp);
}
void manage_command(char **split_input, t_mini *sh)
{
        int     status;
        char    *full_cmd_path;
        char    **tmp;
        int     i;
//      tmp = NULL;
        sh->last_pid = fork();
        if (sh->last_pid < 0)
        {
                perror("created failed\n");
                exit(EXIT_FAILURE);
        }
        else if (!sh->last_pid) //not built in, child process
        {
                tmp = check_for_redir(split_input, sh);
/*              if (tmp)
                        printf("TMP EXISTS \n");
                i = 0;
                while (tmp[i])
                {
                        printf("tmp[%d] = %s\n", i, tmp[i]);
                        i++;
                }*/
//      WHEN I UNCOMMENT THE TWO FOLLOWING LINES, NOTHING WORKS ANYMORE...
                ft_tabfree(split_input);
                split_input = tmp;
                if (!ft_strcmp(split_input[0], "echo"))
                        echo(split_input);
                else if (!ft_strcmp(split_input[0], "pwd"))
                        pwd(sh);
                else if (!ft_strcmp(split_input[0], "cd"))
                        cd(split_input, sh);
                else if (!ft_strcmp(split_input[0], "env"))
                        env(sh);
                else if (!ft_strcmp(split_input[0], "export"))
                        export(split_input, sh);
                else if (!ft_strcmp(split_input[0], "unset"))
                        unset(split_input, sh);
                else if (!ft_strcmp(split_input[0], "exit"))
                        ft_exit(split_input, sh);
                else if (full_cmd_path = get_full_cmd_path(split_input[0], sh))
                {
                        execve(full_cmd_path, split_input, sh->env);
                        free_str(full_cmd_path);
                }
                // if execve this function its self failed, not the result is bad
                // if execve is success, it will kill the fork, child process
                ft_putstr_fd("Exec format error: ", 2);
                ft_putstr_w_new_line_fd(full_cmd_path, 2);
                exit(EXIT_FAILURE);
        }
        else
        {
                waitpid(sh->last_pid, &status, 0);
                sh->last_return = status>>8;
                //ft_printf("status id %d\n", status>>8);
        }
}
void split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
        char **arr;
        int j;
        j = 0;
        arr = ft_split_w_quotes(str, sep[i]);
        if (!arr || !arr[0])
                return;
        if (sep[i] == ' ')
        {
                check_quote_close(arr, sh);
                if (!sh->last_return)
                {
                        replace_var_sub_by_true_value(arr, sh);
                        delete_quotes_from_arr(arr);
                        delete_slash_from_arr(arr);
                        manage_command(arr, sh);
                }
        }
        else
                while (arr[j])
                {
                        split_and_execute(arr[j], sep, i + 1, sh);
                        j++;
                }
        ft_tabfree(arr);
}
void manage_input(t_mini *sh)
{
        char *input;
        int i;
        char sep[4] = ";| ";
        i = 0;
        input = NULL;
        ft_signal(sh);
        while (print_prompt(sh) && get_next_line(0, &input))
        {
                sh->exit_v = sh->last_return;
                sh->line = input;
                sh->is_cmd = 1;
                split_and_execute(input, sep, i, sh);
                sh->is_cmd = 0;
                free_str(input);
        }
        ft_putstr_fd("exit", 2);
        free_str(input);
}
int main(int ac, char **av, char **env)
{
        t_mini **sh;
        //manage_signals();
        //sh.last_pid = 0;
        //      show_cat();
        //      show_welcome_mes();
        init_sh(env);
        sh = get_sh();
        if (!ft_find_env(ENV_HOME, (*sh)->env))
                ft_printf(HOME_ERROR, RED, WHITE);
        manage_input(*sh);
        if ((*sh)->env)
                ft_tabfree((*sh)->env);
        free(*sh);
        *sh = NULL;
        return (0);
}