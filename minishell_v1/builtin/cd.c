/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:26:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/06/21 10:50:10 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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
    else if(!str || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "~") == 0)
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