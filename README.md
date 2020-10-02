1. get pwd
in the function getcwd, we can put NULL and 0 to avoid memoty not enough. (man getcwd)

2. cd

in the func bt_cd(char **args, char **env), else if (ft_tablen(args) == 1 || !ft_strcmp(args[1], "~")) need to add condition: args[1] && !ft_strcmp(args[1], "~")
, if not there is seg fault.

3, need to think about the situation: cd .

4. cd -
 in the beginnig should ~ replace /home/user_name
