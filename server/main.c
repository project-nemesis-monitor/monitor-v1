#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include <bcrypt.h>
#include "includes/liblinux.h"
#include <unistd.h>
#include<sys/types.h> 
#include<sys/wait.h>
#define clear() printf("\033[H\033[J")

#define POLL_INTERVAL_SECONDS 10

int main(int argc, char const *argv[])
{
    MYSQL *conn;
    int num_files;
    FileInfo *files;
    init_shell();
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        fprintf(stderr, "Error initializing MySQL connection\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost", "admin", "2002", "nemesisbdd", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    files = selectAllFiles(conn, &num_files);
    printf("Liste des fichiers :\n");
    for (int i = 0; i < num_files; i++)
    {
        printf("Chemin : %s, check mod : %s\n", files[i].path, (files[i].check_mod == 1 ? "actif" : "en arret"));
    }

    if (files == NULL)
    {
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    check_file_changes(conn);
    return 0;
}
