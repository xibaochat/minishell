void split_on_space_and_exec(char *cmd, int have_pipe_redirection)
{
     if (have_pipe_redirection)
        manage_pipe_redirection();
    [...]
}

void split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
    char **arr;
    int j;
    j = 0;
    arr = ft_split_w_quotes(str, sep[i]);
    if (!arr || !arr[0])
        return;
    //------------------
    // NEW CODE TO MANAGE PIPE
    if (sep[i] == '|')
    {
        if (length(arr) == 1)
            return (split_on_space_and_exec(arr[0], have_pipe_redirection=False));
        else
            while (arr[j])
            {
                split_on_space_and_exec(arr[0], have_pipe_redirection=True);
                j++;
            }
    }
    // -----------------
    else if (sep[i] == ';')
        while (arr[j])
        {
            split_and_execute(arr[j], sep, i + 1, sh);
            j++;
        }
    ft_tabfree(arr);
}
