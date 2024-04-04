#include <stdio.h>
#include <string.h>
#include <mariadb/mysql.h>
#include <bcrypt.h>

// Structure pour stocker les données utilisateur
struct User {
    char username[100];
    char password_hash[BCRYPT_HASHSIZE];
};

// Fonction pour comparer les mots de passe hachés
int compare_passwords(const char *provided_password, const char *stored_hash) {
    if (bcrypt_checkpw(provided_password, stored_hash) == 0) {
        // Le mot de passe fourni correspond au hachage stocké
        return 1;
    } else {
        // Le mot de passe fourni ne correspond pas au hachage stocké
        return 0;
    }
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "Erreur lors de l'initialisation de la connexion à la base de données.\n");
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "admin", "2002", "nemesisbdd", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Erreur lors de la connexion à la base de données : %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    if (mysql_query(conn, "SELECT username, password FROM users WHERE username='root'")) {
        fprintf(stderr, "Erreur lors de l'exécution de la requête : %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Erreur lors de la récupération du résultat de la requête.\n");
        mysql_close(conn);
        return 1;
    }

    struct User user;

    while ((row = mysql_fetch_row(res)) != NULL) {
        strcpy(user.username, row[0]);
        strcpy(user.password_hash, row[1]);
    }

    mysql_free_result(res);

    // Demander le mot de passe à l'utilisateur
    char password[100];
    printf("Entrez votre mot de passe : ");
    scanf("%s", password);

    // Comparer les mots de passe hachés
    if (compare_passwords(password, user.password_hash)) {
        printf("Le mot de passe est correct.\n");
    } else {
        printf("Le mot de passe est incorrect.\n");
    }

    mysql_close(conn);

    return 0;
}
