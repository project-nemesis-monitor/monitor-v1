#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include <bcrypt.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h> 
#include<sys/wait.h>
#define POLL_INTERVAL_SECONDS 10
#include <sys/inotify.h>
#include <limits.h>
#include "reactwthbdd.h"
#define PATH_MAX 4096
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))
#define clear() printf("\033[H\033[J")
typedef struct
{
    const char *path;
    int check_mod;
} FileInfo;

typedef struct {
    uint32_t cookie;
    char *old_name;
} EventMap;

FileInfo *selectAllFiles(MYSQL *conn, int *num_path);
void check_file_changes(MYSQL *conn);
char* remove_last_component(const char *path);
void init_shell();
void countFiles();