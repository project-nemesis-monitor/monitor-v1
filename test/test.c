#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    char resolved_path[PATH_MAX];

    // Chemin absolu du fichier
    const char *absolute_path = "s.txt";

    // Obtention du chemin d'accès absolu
    if (realpath(absolute_path, resolved_path) == NULL) {
        perror("Erreur lors de la résolution du chemin d'accès absolu");
        return EXIT_FAILURE;
    }

    printf("Chemin d'accès absolu : %s\n", resolved_path);

    return EXIT_SUCCESS;
}
