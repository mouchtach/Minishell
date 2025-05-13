/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:18:48 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/13 00:31:30 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXC_H
#define EXC_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif


typedef struct s_exc
{
  t_cmd *list;
  t_env *env;
  t_env **path;

}   t_exc;

typedef enum s_type 
{
  D_FILE,
  D_APPEND,
  D_HERDOC
}       t_type;

typedef struct s_env 
{
    char *key;
    char *value;
    struct s_env *next;
}       t_env;

typedef struct s_redirec
{
    char    *name;
    t_type  type;
    struct s_redirec *next;
}       t_redirec;


typedef struct s_cmd
{
	char			**cmd;
	t_redirec		*input;
	t_redirec		*output;
	struct s_cmd	*next;
}						t_cmd;


// LIBFT
char	  *ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	  **ft_split(char const *s, char c);
char	  *ft_strchr(const char *s, int c);
char	  *ft_substr(char const *s, unsigned int start, size_t len);
int     ft_strcmp(char *s1,  char *s2);

// CMD
t_cmd *set_struct();
// ENV
t_env *set_env(char **env);
// PATH
char **set_path(t_env *v);
//GET_NEXT_LINE
char	*get_next_line(int fd);

#endif