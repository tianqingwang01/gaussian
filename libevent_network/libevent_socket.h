#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <time.h>

#define BACKLOG   5
typedef struct fd_s{
    int fd;
    time_t last_time;
}fd_t;

int set_socket_reusable(int fd);
int set_socket_linger(int fd);
int set_socket_reusable(int fd);
int socket_setup(int nPort);

int set_rlimit(long nMaxCore,int nMaxConnection);

void fd_init(int nMaxConnection);
int  fd_insert(int fd);
int  fd_del(int fd);
int  fd_update_last_time(int fd,time_t last_time);
int  check_closewait_timeout(time_t now);

#endif