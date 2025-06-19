/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:49:22 by macbookpro        #+#    #+#             */
/*   Updated: 2025/06/19 16:11:19 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int    is_built(char *cmd)
{
    if(ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "ECHO")  == 0)
        return(1);
    if(ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD")  == 0)
        return(1);
    if(ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV")  == 0)
        return(1);
    if(ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "EXPORT")  == 0)
        return(1);
    if(ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "CD")  == 0)
        return(1);
    return(0);
}

bool    check_n(char *parm)
{
    int i = 0;

    if(parm[i] == '-')
        i++;
    while(parm[i] == 'n')
        i++;
    if(parm[i] == '\0' && i >= 2)
        return (true);
    return(false);
}

void    ft_echo(char **cmd) // echo -n
{
    int i = 1;
    int ck = 0;
    while (cmd[i] && check_n(cmd[i]))
    {
        ck = 1;
        i++;
    }
    while(cmd[i])
    {
        printf("%s", cmd[i]);
        if(cmd[i + 1])
            printf(" ");
        i++;
    }
    if(ck == 1)
        return ;
    printf("\n");
}

void    ft_list(t_list *env)
{
    t_list *tmp;

    tmp = env;
    while(tmp)
    {
        if(tmp->eg == true)
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}


void    desplay_list(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while(tmp)
    {
        if(tmp->eg == true)
            printf("%s='%s'\n", tmp->key, tmp->value);
        else
            printf("%s\n", tmp->key);
        tmp = tmp->next;
    }
}

t_list *ft_copy_env(t_list *env)
{
    t_list *list;
    t_list *new = NULL;

    list = env;
    while(list)
    {
        add_back_env(&new, creat_new_env(list->value, list->key, list->eg));
        list = list->next;
    }
    return(new);
}

void sort_export(t_list *var)
{
    t_list *new = NULL;
    t_list *tmp;
    t_list *tmp2;
    t_list *small;

    new = ft_copy_env(var);
    tmp = new;
    while (tmp)
    {
        small = tmp;
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (ft_strcmp(tmp2->key, small->key) < 0)
                small = tmp2;
            tmp2 = tmp2->next;
        }
        if (small != tmp)
        {
            char *temp_key = tmp->key;
            bool eg = tmp->eg;
            char *temp_value = tmp->value;
            tmp->key = small->key;
            tmp->value = small->value;
            tmp->eg = small->eg;
            small->key = temp_key;
            small->value = temp_value;
            small->eg = eg;
        }
        tmp = tmp->next;
    }
    desplay_list(new);
    //clear list;
}

int    add_export_list(t_list **env,char *value, char *key, bool eg)
{
    t_list *tmp;

    tmp = *env;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, key))
        {
            free(tmp->value);
            tmp->value = value;
            return (0);
        }
        tmp = tmp->next;
    }
    add_back_env(env, creat_new_env(value, key , eg));
    return(1);

}

void    ft_export(t_shell *var, char **cmd)
{
    bool eg = false;
    char *value;
    char *key;

    int j = 1;
    if(!cmd[j])
        sort_export(var->env);
    while(cmd[j])
    {
        int i = 0;
        while(cmd[j][i] && cmd[j][i] != '=')
            i++;
        if(cmd[j][i] == '=')
        {
            value = ft_strdup(cmd[j] + i + 1);
            eg = true;
        }
        else
            value = ft_strdup(cmd[j] + i);
        key = ft_substr(cmd[j], 0, i);
        if(!add_export_list(&var->env, value, key, eg))
            free(value);
        else
        {
            free(value);
            free(key);
        }
        j++;
    }
}
void    update_env(char *key, char *value, t_list **env)
{
    t_list *tmp;

    tmp = *env;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, key))
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return;
        }
        tmp = tmp->next;
    }
    add_back_env(env, creat_new_env(value, key, true));
}

char    *get_value(t_list *env, char *key)
{
    t_list *tmp;

    tmp = env;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, key))
            return(tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

char *get_path(char *str, t_list *env)
{
    char *ret;

    if(!ft_strcmp(str, "-"))
    {
        ret = get_value(env, "OLDPWD");
        if(!ret)
            return(printf("cd: OLDPWD not set\n"), NULL);
        return(ret);
    }
    else if((!ft_strcmp(str, "--")))
    {
        ret = get_value(env, "HOME");
        if(!ret)
            return(printf("cd: HOME not set\n"), NULL);
        return(ret);
    }
    else if(!ft_strncmp(str, "~/", 2))
    {
        ret = ft_strjoin(get_value(env, "HOME"), str + 1);
        return(ret);
    }
    else
        return(str);
}

void    ft_cd(t_list *env, char *path)
{
    char *oldpwd;

    if(!path)
        return;
    oldpwd = getcwd(NULL, 0);
    path = get_path(path, env);
    if(!oldpwd)
        return(perror("getcwd"));
    if(chdir(path) == -1)
        return(free(oldpwd), perror("cd"));
    if(!ft_strncmp(path, "~/", 2)) // hna khdamt strjoin
        free(path);
    path = getcwd(NULL, 0);
    if(!path)
        return(free(oldpwd), perror("getcwd"));//  free buffer
    update_env("PWD", path, &env);
    update_env("OLDPWD",oldpwd, &env);
    free(path);
    free(oldpwd);
}

void    built_in_function(char **cmd, t_shell *val)
{
    printf("build in\n");
    if(ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "ECHO")  == 0)
        ft_echo(cmd);
    if(ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "PWD")  == 0)
        printf("%s\n", get_value(val->env, "PWD"));
    if(ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "ENV")  == 0)
        ft_list(val->env);
    if(ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "EXPORT")  == 0)
        ft_export(val, cmd);
    if(ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "CD")  == 0)
        ft_cd(val->env, cmd[1]);
    printf("end\n");

}

