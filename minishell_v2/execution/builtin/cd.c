/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:26:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/03 20:05:28 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

char    *get_value(t_list *env, char *key)
{
    t_list *tmp;

    if(!env || !key)
        return (NULL);
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
            tmp->eg = true;
            return;
        }
        tmp = tmp->next;
    }
    add_back_env(env, list_new_node(value, key, true));
}

char *resolve_cd_path(char *str, t_list *env)
{
    char *ret;

    if(str == NULL || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "~") == 0)
    {
        ret = get_value(env, "HOME");
        if(!ret)
            return(printf("cd: HOME not set\n"), NULL);
        return(ret);
    }
    else if(!ft_strcmp(str, "-"))
    {
        ret = get_value(env, "OLDPWD");
        if(!ret)
            return(printf("cd: OLDPWD not set\n"), NULL);
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
    path = resolve_cd_path(path, env);
    if(!oldpwd)
        return(error_message(errno, path));
    if(chdir(path) == -1)
        return(free(oldpwd),error_message(errno, path));
    if(!ft_strncmp(path, "~/", 2)) // hna khdamt strjoin
        free(path);
    path = getcwd(NULL, 0);
    if(!path)
        return(free(oldpwd), error_message(errno, path));//  free buffer
    update_env("PWD", path, &env);
    update_env("OLDPWD",oldpwd, &env);
    free(path);
    free(oldpwd);
}