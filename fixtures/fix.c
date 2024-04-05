#include <stdlib.h>
#include <stdio.h>
#include <mariadb/mysql.h>
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    MYSQL *conn;

    // Initialisation de la connexion MySQL
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error initializing MySQL connection\n");
        exit(EXIT_FAILURE);
    }

    // Connexion à la base de données
    if (mysql_real_connect(conn, "localhost", "admin", "2002", "nemesisbdd", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Déclaration des données de test
    const char *insert_query = "INSERT INTO checkfile (file_id, check_mod, path, upload_by, upload_at) VALUES (?, ?, ?, ?, ?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (stmt == NULL) {
        fprintf(stderr, "Error initializing MySQL statement\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query)) != 0) {
        fprintf(stderr, "Error preparing SQL statement: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Paramètres liés aux colonnes de la table
    char file_id[20] = "testbvh"; // Vous devez générer un ID unique pour chaque enregistrement
    unsigned char check_mod = 1;  // Exemple de modificateur à 1 (true)
    char path[100] = "/chemin/vers/fichier2";
    char upload_by[200] = "301d1246-93bd-4e7f-b570-fd7fb2c4d2b1"; // Remplacez "id_utilisateur" par l'ID de l'utilisateur réel
    MYSQL_TIME upload_at;
    time_t current_time = time(NULL);
    struct tm *tm_info = localtime(&current_time);
    upload_at.year = tm_info->tm_year + 1900;
    upload_at.month = tm_info->tm_mon + 1;
    upload_at.day = tm_info->tm_mday;
    upload_at.hour = tm_info->tm_hour;
    upload_at.minute = tm_info->tm_min;
    upload_at.second = tm_info->tm_sec;

    MYSQL_BIND bind_params[5];
    memset(bind_params, 0, sizeof(bind_params));

    bind_params[0].buffer_type = MYSQL_TYPE_STRING;
    bind_params[0].buffer = file_id;
    bind_params[0].buffer_length = strlen(file_id);

    bind_params[1].buffer_type = MYSQL_TYPE_TINY;
    bind_params[1].buffer = &check_mod;
    bind_params[1].is_unsigned = 1;
    bind_params[1].is_null = 0;

    bind_params[2].buffer_type = MYSQL_TYPE_STRING;
    bind_params[2].buffer = path;
    bind_params[2].buffer_length = strlen(path);

    bind_params[3].buffer_type = MYSQL_TYPE_STRING;
    bind_params[3].buffer = upload_by;
    bind_params[3].buffer_length = strlen(upload_by);

    bind_params[4].buffer_type = MYSQL_TYPE_TIMESTAMP;
    bind_params[4].buffer = &upload_at;

    if (mysql_stmt_bind_param(stmt, bind_params) != 0) {
        fprintf(stderr, "Error binding parameters: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Exécution de la requête d'insertion
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "Error executing SQL statement: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Libération des ressources
    mysql_stmt_close(stmt);
    mysql_close(conn);

    printf("Fixtures créées avec succès.\n");

    return 0;
}
