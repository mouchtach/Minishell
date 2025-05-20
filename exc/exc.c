/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:32:48 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/18 18:27:06 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



bool   set_redirection(t_cmd *command)                                              // hna khasni nhadd in ol out dyal kola cmmd m3a close;
{
    command->fd_io[0] = STDIN_FILENO;
    command->fd_io[1] = STDOUT_FILENO;

                                                                                      // hna ghadi check wach kin chi derection dyal input 
    t_redirec *tmp;

    
    tmp = command->input;
    while(tmp)
    {                                                          
        if(tmp->type ==  D_IN)                                                  // ila kan chi input ghadi nseteh l had variabl ft_files[0]
        {                                                                            // hna ila kan type dyalo D_IN  ya3ni khsni nopeni file 
            command->fd_io[0] = open(tmp->name, O_RDONLY, 0777);
            if (command->fd_io[0] == -1)
                return(perror("no such file or directory"), false);
            
        }
        if(tmp->type ==  D_HERDOC)
        {                                                                            // hna ila kan type dyalo D_HEERDOC  ya3ni khsni call herdoc fuction 
            command->fd_io[0] = open(HEREDOC_FILE, O_RDONLY, 0777);                                                                      
            if (command->fd_io[0] == -1)
                return(perror("no such file or directory"), false);
        }
        if(tmp->next)
        {
            close(command->fd_io[0]);
        }
        tmp = tmp->next;
    }

    tmp = command->output;
    while(tmp)
    {                                                                              // hna ila kant chi file out put ghadi nsete ft_files[1]
        if(tmp->type == D_OUT)
        {
            command->fd_io[1] = open (tmp->name, O_CREAT | O_TRUNC | O_RDWR , 0777);
            if (command->fd_io[1] == -1)
                return(perror("open faild"), false);
        }
        if(tmp->type == D_APPEND)
        {
            command->fd_io[1] = open (tmp->name, O_CREAT | O_APPEND | O_RDWR , 0777);
            if (command->fd_io[1] == -1)
                return(perror("open faild"), false);
        }
        if(tmp->next)
        {
            close(command->fd_io[1]);
        }
        tmp = tmp->next;

    }
                                                                                        // had laan salina m3a redirection                                                                                 //PIPES
    if(command->prev)                                                                   //check bli kina chi command 9bal
    {                                                                                   //imta ghadi tkon pip dyal prev hia input  ila ta9at had condition
        if(command->prev->fd_pip[0] != 0 && command->fd_io[0] == STDIN_FILENO)
        {
            command->fd_io[0] = command->prev->fd_pip[0];
        }
    }
    
    if(command->next) //check bli kina chi command b3d
    {
        if(command->fd_pip[1] != 0 && command->fd_io[1] == STDOUT_FILENO)
        {
            command->fd_io[1] = command->fd_pip[1];
        }
        else
            close(command->fd_pip[1]);
    }
    if(command->fd_pip[0] != 0 )
        close(command->fd_pip[0]);
    

                                                                                // hna daba ghdi ndir dup2 l in ol out files 
    if(command->fd_io[1] != STDOUT_FILENO)
    {
        dup2(command->fd_io[1], STDOUT_FILENO);
        close(command->fd_io[1]);
    }  
    if(command->fd_io[0] != STDIN_FILENO)
    {
        dup2(command->fd_io[0], STDIN_FILENO);
        close(command->fd_io[0]);
    }
    return (true);
                                                                          
}


void    ft_childe_process(t_exc *val, t_cmd *cmd)
{
    char *path;

    path = get_path_cmd(val->path, cmd->cmd[0]);
    if(!path)
    {
        perror("command not found");
        exit(0);
    }
    set_redirection(cmd);
    execve(path, cmd->cmd, NULL);    
}

void    ft_excution(t_exc *val)
{
    
    ft_herdoc(val);
    t_cmd *command;
    int    fork_pid;


    
    command = val->list;
    while(command)
    {
        command->fd_pip[0] = 0;
        command->fd_pip[1] = 0;
        if(command->next)
        {
            printf("%sOPEND PIPES[0][1]  CMD = %s%s\n ", BLUE,command->cmd[0] ,  RESET);
            pipe(command->fd_pip);
        }
        fork_pid = fork();
        if(fork_pid < 0)
            perror("fork faild");
        if(fork_pid == 0)
        {
            ft_childe_process(val, command);
            
        }
        // if(command->prev) 
        // {
        //     printf("%sCLOSED PIPES[0][1]  CMD = %s%s\n ", BLUE,command->prev->cmd[0],  RESET);
        //     close(command->prev->fd_pip[0]);
        //     close(command->prev->fd_pip[1]);
        // }
        command = command->next;
        
    }
    while(wait(NULL) > 0);
    
    if (access(HEREDOC_FILE, F_OK) == 0) {
        unlink(HEREDOC_FILE);
    }
    
}









// void    child_process(t_cmd *cmd)
// {
//     t_redirec *re;

//     re = cmd->input;

//     cmd->fd_io[1] = STDOUT_FILENO;
//     cmd->fd_io[0] = STDIN_FILENO;
    
//     printf("%sCHILD /////////  CDM = %s%s\n", RED, cmd->cmd[0] , RESET);
//     int i = 1;
//     while(re)
//     {
//         cmd->fd_io[0] = 9;
//         printf("%sCHILD /////////  i have redirection < input  : %d\n%s", RED,  i, RESET);
//         re = re->next;
//         i++;
//     }
//     i = 1;
//     re = cmd->output; 
//     while(re)
//     {
//         cmd->fd_io[1] = 9;
//         printf("%sCHILD /////////  i have redirection > output  : %d\n%s",RED, i, RESET);
//         re = re->next;
//         i++;
//     }
    
//     if(cmd->prev && cmd->fd_io[0] == 0)
//     {
//         cmd->fd_io[1] = 5;
//         printf("%sCHILD /////////  i have PIP[0] | input < %s  and CLOSED\n%s ", RED,cmd->prev->cmd[0],  RESET);
//         // printf("%sCHILD /////////  i have PIP | input <\n%s", RED, RESET);
//     }
//     else 
//     {
//         // if(cmd->fd_io[0] == STDIN_FILENO)
//         //     printf("%sCHILD /////////  i have STDIN input < %s\n%s ", RED,cmd->prev->cmd[0],  RESET);
//         if(cmd->fd_pip[0] != 0)
//             printf("%sCHILD /////////  CLOSED PIP[0]\n%s", RED , RESET);

//     }
//     if(cmd->next && cmd->fd_io[1] == STDOUT_FILENO)
//     {
//         cmd->fd_io[1] = 5;
//         printf("%sCHILD /////////  i have PIP[1] | output < %s  and CLOSED\n%s ", RED,cmd->next->cmd[0],  RESET);
//     }
//     else
//     {
//         // if(cmd->fd_io[1] == STDOUT_FILENO)
//         //     printf("%sCHILD /////////  i have STDOUT output < \n%s ", RED, RESET);
        
//         if(cmd->fd_pip[1] != 0)
//             printf("%sCHILD /////////  CLOSED PIP[1]\n%s", RED, RESET);
//     }
//     if(cmd->fd_io[1] == STDOUT_FILENO)
//         printf("%sCHILD /////////   STDOUT output%s \n ", RED, RESET);
//     if(cmd->fd_io[0] == STDIN_FILENO)
//         printf("%sCHILD /////////   STDIN input%s  \n ", RED, RESET);
// }


// void    excution(t_exc *val)
// {
//     t_cmd *cmd;
//     t_cmd *last;
//     int     pid_fork;
    
//     printf("%sSTART /////////%s\n", GREEN, RESET);

//     cmd = val->list;
//     if(!cmd)
//         return;
    
//     // int i = 1;
//     while(cmd)
//     {
//         ////////////////////
//         cmd->fd_pip[1] = 0;
//         cmd->fd_pip[0] = 0;
//         ////////////////////
        
//         if(cmd->next)
//         {   
//             printf("PIP[0] OPEN    (%s)\n", cmd->cmd[0]);            
//             printf("PIP[1] OPEN    (%s)\n", cmd->cmd[0]);            
//             pipe(cmd->fd_pip);
//         }
        
//         pid_fork = fork();
//         if(pid_fork ==  0)
//         {
//             // printf("%sSTART /////////%s\n", RED, RESET);
//             child_process(cmd);
//             exit(0);
            
//         }
//         if (pid_fork > 0)
//         {
//             // usleep(10000);
//             // printf("PARENT PROCESS\n");
//             if(cmd->fd_pip[1] != 0)
//                 printf("CLOSE PIP[1] - P  CMD = %s\n", cmd->cmd[0]);
//             if(cmd->prev)
//             {
//                 if(cmd->prev->prev)
//                     printf("CLOSE PIP[0] - P  CMD =  prev->prev \n");
//             }
//         }  
//         // i++;
//         if(!cmd->next)
//             last = cmd;
//         cmd = cmd->next;
//     }
//     if(last->prev)
//     { 
//         if(last->prev->fd_pip[0] != 0)
//             printf("CLOSE PIP[0] - P  CMD = %s\n", last->prev->cmd[0]);
//     }
    
//     while(wait(NULL) > 0);
//     printf("%sFINESHED /////////%s\n", GREEN, RESET);

// }