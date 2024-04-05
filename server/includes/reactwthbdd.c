#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include <bcrypt.h>
#include <string.h>
#include <unistd.h>
#define POLL_INTERVAL_SECONDS 10
#include <sys/inotify.h>
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

void updateFile(MYSQL *conn, const char *old_path, const char *new_path, const char *new_name)
{
    char query[10000];
    snprintf(query, sizeof(query), "UPDATE checkfile SET path = '%s', filename = '%s' WHERE path = '%s'", new_path, new_name, old_path);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Error updating file: %s\n", mysql_error(conn));
    }
}

