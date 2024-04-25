#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include <string.h>
#include <unistd.h>
#define POLL_INTERVAL_SECONDS 10
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include "reactwthbdd.h"
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))
#define PATH_MAX 4096
#define clear() printf("\033[H\033[J")

typedef struct
{
    const char *path;
    int check_mod;
} FileInfo;
void init_shell()
{

    clear();
    printf("\n\n\n\n******************"
           "************************"
           "**************************\n\n");
    printf("\n\t\t⠀⠀⠀⠀⠀⠀⠀⠀  ⢀⣀⣤⣤⣤⣤⣴⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⠀⠀⣀⣴⣾⠿⠛⠋⠉⠁⠀⠀⠀⠈⠙⠻⢷⣦⡀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⣤⣾⡿⠋⠁⠀⣠⣶⣿⡿⢿⣷⣦⡀⠀⠀⠀⠙⠿⣦⣀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⢀⣴⣿⡿⠋⠀⠀⢀⣼⣿⣿⣿⣶⣿⣾⣽⣿⡆⠀⠀⠀⠀⢻⣿⣷⣶⣄⠀\n");
    printf("\t\t⠀⣴⣿⣿⠋⠀⠀⠀⠀⠸⣿⣿⣿⣿⣯⣿⣿⣿⣿⣿⠀⠀⠀⠐⡄⡌⢻⣿⣿⡷\n");
    printf("\t\t⢸⣿⣿⠃⢂⡋⠄⠀⠀⠀⢿⣿⣿⣿⣿⣿⣯⣿⣿⠏⠀⠀⠀⠀⢦⣷⣿⠿⠛⠁\n");
    printf("\t\t⠀⠙⠿⢾⣤⡈⠙⠂⢤⢀⠀⠙⠿⢿⣿⣿⡿⠟⠁⠀⣀⣀⣤⣶⠟⠋⠁⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠈⠙⠿⣾⣠⣆⣅⣀⣠⣄⣤⣴⣶⣾⣽⢿⠿⠟⠋⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠙⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\n\n\n");

    printf("\t███    ██ ███████ ███    ███ ███████ ███████ ██ ███████ \n");
    printf("\t████   ██ ██      ████  ████ ██      ██      ██ ██      \n");
    printf("\t██ ██  ██ █████   ██ ████ ██ █████   ███████ ██ ███████ \n");
    printf("\t██  ██ ██ ██      ██  ██  ██ ██           ██ ██      ██ \n");
    printf("\t██   ████ ███████ ██      ██ ███████ ███████ ██ ███████ \n");

    printf("\n\t\t-HOW ABOUT CHECKING FILE PROPERTIES ?-");
    printf("\n\t\t-v1.0 Nemesis Group-");
    printf("\n\n\n\n*******************"
           "***********************"
           "*************************");
    printf("\n\n\n\t\t - Monitoring server -\n\n\n");
    sleep(3);
    // clear();
}
FileInfo *selectAllFiles(MYSQL *conn, int *num_path)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *query = "SELECT path, check_mod FROM checkfile";

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Error executing SQL query: %s\n", mysql_error(conn));
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "Error retrieving result set: %s\n", mysql_error(conn));
        return NULL;
    }

    *num_path = mysql_num_rows(res);

    FileInfo *files = malloc(*num_path * sizeof(FileInfo));
    if (files == NULL)
    {
        fprintf(stderr, "Error allocating memory for files\n");
        mysql_free_result(res);
        return NULL;
    }

    int i = 0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        files[i].path = strdup(row[0]);
        files[i].check_mod = atoi(row[1]);
        i++;
    }

    mysql_free_result(res);

    return files;
}

char *remove_last_component(const char *path)
{
    char *new_path = strdup(path);
    if (new_path == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int length = strlen(new_path);

    int i;
    for (i = length - 1; i >= 0; i--)
    {
        if (new_path[i] == '/')
        {
            break;
        }
    }
    if (i >= 0)
    {
        new_path[i] = '\0';
    }
    return new_path;
}

void check_file_changes(MYSQL *conn)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    int fd, wd;
    char buffer[BUF_LEN];
    char *old_path;
    struct stat statbuff;

    fd = inotify_init();
    if (fd < 0)
    {
        fprintf(stderr, "Error initializing inotify\n");
    }

    if (mysql_query(conn, "SELECT path FROM checkfile WHERE check_mod = 1"))
    {
        fprintf(stderr, "Error querying database: %s\n", mysql_error(conn));
    }

    result = mysql_store_result(conn);
    if (result == NULL)
    {
        fprintf(stderr, "Error storing result set: %s\n", mysql_error(conn));
    }

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        char *folder_file;
        if (stat(row[0], &statbuff) == 0)
        {
            if(S_ISDIR(statbuff.st_mode)){
                folder_file = row[0];
            } else {
                folder_file = remove_last_component(row[0]);
            }
        }
        
        wd = inotify_add_watch(fd, folder_file, IN_ATTRIB | IN_MOVE_SELF | IN_MOVED_TO | IN_MODIFY | IN_DELETE);

        if (wd < 0)
        {
            fprintf(stderr, "Error adding watch for file %s\n", row[0]);
            continue;
        }
        else
        {
            old_path = row[0];
            printf("Watch added in folder %s for file: %s\n", folder_file, row[0]);
        }
    }

    while (1)
    {
        int bytes = read(fd, buffer, BUF_LEN);
        if (bytes < 0)
        {
            fprintf(stderr, "Error reading inotify events\n");
            break;
        }

        char *ptr = buffer;
        while (ptr < buffer + bytes)
        {
            struct inotify_event *event = (struct inotify_event *)ptr;

            switch (event->mask)
            {
            case IN_MOVE_SELF:
            case IN_MOVED_TO:
                printf("File renamed: ");
                char resolved_path[PATH_MAX];
                if (realpath(event->name, resolved_path) == NULL)
                {
                    perror("Error getting absolute path");
                }

                updateFile(conn, old_path, resolved_path, event->name);
                break;
            case IN_ATTRIB:
                printf("File attributes changed: ");
                struct stat file_stat;
                if (stat(event->name, &file_stat) == 0)
                {
                    mode_t perm = file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX);
                    char *perm_str = permissions_to_octal(perm);
                    updatePermissionFile(conn, event->name, perm_str);
                    free(perm_str);
                }
                else
                {
                    perror("Error getting file attributes");
                }
                break;
            case IN_MODIFY:
                printf("File modified: ");
                break;
            case IN_DELETE:
                printf("File deleted: ");
                break;
            default:
                printf("Unhandled event: ");
                break;
            }

            if (event->len > 0)
            {
                printf("%s\n", event->name);
            }
            else
            {
                printf("(No name available)\n");
            }

            ptr += sizeof(struct inotify_event) + event->len;
        }
    }

    close(fd);
    mysql_free_result(result);
}
