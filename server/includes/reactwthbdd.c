#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
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
char *permissions_to_octal(mode_t perm)
{
    char *result = (char *)malloc(sizeof(char) * 5);
    if (result == NULL)
    {
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    snprintf(result, 5, "%o", perm);
    return result;
}
void updatePermissionFile(MYSQL *conn, const char *filename, const char *perm)
{
    char query[10000];
    snprintf(query, sizeof(query), "UPDATE checkfile SET permissions = '%s' WHERE filename = '%s'", perm, filename);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Error updating file: %s\n", mysql_error(conn));
    }
}