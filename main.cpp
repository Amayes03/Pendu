#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 6
#define MAX_LONG 100
#define MAX_WORDS 100


// Fonction "printHangman" pour afficher le pendu en fonction du nombre d'essais ratés
void printHangman(int nbr_tries) {
    switch (nbr_tries) {
        case 0:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 1:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 2:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 3:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 4:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 5:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /   |\n");
            printf("      |\n");
            printf("=========\n");
            break;
    }
}

int main() {
    int nbr_mots = 0; // Nombre de mots dans le tableau tab_mots

    const char* filename = "mots.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier '%s'\n", filename);
        exit(1); // Quitter le programme avec un code d'erreur
    }

    // Lecture des mots du fichier dans le tableau tab_mots
    char tab_mots[MAX_WORDS][MAX_LONG];
    nbr_mots = 0;
    while (nbr_mots < MAX_WORDS && fgets(tab_mots[nbr_mots], MAX_LONG, file) != NULL) {
        tab_mots[nbr_mots][strcspn(tab_mots[nbr_mots], "\n")] = '\0';
        nbr_mots++;
    }

    fclose(file);

    char mot_select[MAX_LONG];

    printf(" ____ _____ _ _ ____ _ _\n");
    printf("|  _ \\ | ____|| \\ | ||  _ \\| | | |\n");
    printf("| |_) || _| | \\| || | | | | | | |\n");
    printf("|  __/ | |___ | |\\ || |_| | |_| |\n");
    printf("|_| |  ___| |_| \\_||____/ \\___/\n\n");
    printf("Bienvenue au Pendu de la Word Company !\n");

    printf("Voulez-vous jouer contre un autre joueur ? (1 pour Oui, 0 pour Non): ");
    int two_players;
    scanf("%d", &two_players);

    if (two_players) {
        printf("Joueur 1, entrez le mot à deviner (en lettres minuscules, sans espaces) : ");
        scanf("%s", mot_select);
    } else {
        // Selection aleatoire du mot a partir de la liste
        srand(time(NULL));
        int random_index = rand() % nbr_mots;
        strcpy(mot_select, tab_mots[random_index]);
    }

    int mot_long = strlen(mot_select);
    char mot_dev[MAX_LONG];

    // Initialisation du mot masqué avec des tirets
    for (int i = 0; i < mot_long; i++) {
        mot_dev[i] = '_';
    }
    mot_dev[mot_long] = '\0';

    int nbr_tries = 0;
    int correct_dev = 0;
    char lettres_dev[MAX_TRIES];

    printf("Devinez le mot !\n");

    while (nbr_tries < MAX_TRIES && correct_dev < mot_long) {
        printf("Il vous reste : %d vies\n", MAX_TRIES - nbr_tries);
        printHangman(nbr_tries);
        printf("%s\n", mot_dev);

        char guess;
        printf("Choisissez une lettre: ");
        scanf(" %c", &guess);

        // Vérification si la lettre a déjà été devinée
        int already_guessed = 0;
        for (int i = 0; i < nbr_tries; i++) {
            if (lettres_dev[i] == guess) {
                already_guessed = 1;
                break;
            }
        }

        if (already_guessed) {
            printf("Vous avez deja devine cette lettre!\n");
        } else {
            int found = 0;
            for (int i = 0; i < mot_long; i++) {
                if (mot_select[i] == guess) {
                    mot_dev[i] = guess;
                    found = 1;
                    correct_dev++;
                }
            }

            if (found) {
                printf("Bonne devinette!\n");
            } else {
                printf("Mauvaise devinette!\n");
                nbr_tries++;
            }

            lettres_dev[nbr_tries - 1] = guess;
        }
    }

    if (correct_dev == mot_long) {
        printf("%s\n", mot_select);
        if (two_players) {
            printf("Bien joue Joueur 2!\n");
        } else {
            printf("Bien joue Joueur 1!\n");
        }
    } else {
        printf("Le mot etait : %s\n", mot_select);
        printf("Vous etes pendu !\n");
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("      |\n");
        printf("=========\n");
    }

    return 0;
}