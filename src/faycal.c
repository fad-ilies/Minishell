// int    ft_export(t_structdata, char **cmd)
// {
//     int    i;

//     i = 1;
//     if (!cmd[1])
//     {
//         return (print_export(data->env), 1);
//     }
//     else
//     {
//         while (cmd[i])
//         {
//             if (is_valid_export(cmd[i]))
//             {
//                 if (!add_or_replace_env_var(data, cmd[i]))
//                 {
//                     return (0);
//                 }
//             }
//             i++;
//         }
//     }
//     return (1);
// }




void    print_after_equal(char cpy_env, int i, int j, int flag)
{
    while (cpy_env[i][j] != '\0')
    {
        if (cpy_env[i][j] == '=' &&flag == 0)
        {
            *flag = 1;
            ft_printf("="");
        }
        else
            ft_printf("%c", cpy_env[i][j]);
        j++;
    }
}

void    print_export(char cpy_env)
{
    int    flag;
    int    flag2;
    int    j;
    int    i;

    flag = 0;
    i = 0;
    while (cpy_env[i] != NULL)
    {
        flag2 = 0;
        if (ft_strncmp(cpyenv[i], "=", 2) != 0)
        {
            flag2 = 1;
            ft_printf("declare -x ");
            j = 0;
            flag = 0;
            print_after_equal(cpy_env, i, j, &flag);
            if (flag == 1)
                ft_printf(""");
        }
        if (flag2 == 1)
            ft_printf("\n");
        i++;
    }
}

void    sorted_export(char **cpy_env, int len_env)
{
    int        sorted;
    char    *tmp;
    int        i;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        i = 0;
        while (i < len_env - 1)
        {
            if (ft_strcmp(cpy_env[i], cpy_env[i + 1]) > 0)
            {
                tmp = cpy_env[i];
                cpy_env[i] = cpy_env[i + 1];
                cpy_env[i + 1] = tmp;
                sorted = 0;
            }
            i++;
        }
    }
}
