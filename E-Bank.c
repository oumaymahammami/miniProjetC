#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool estAlphabetique(const char *chaine) {
    size_t longueur = strlen(chaine);
    for (size_t i = 0; i < longueur; ++i) {
        if (!isalpha(chaine[i])) {
            return false;
        }
    }
    return true;
}
struct tm saisirDate() {
    struct tm date_entree;

    printf("Entrez la date (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &date_entree.tm_mday, &date_entree.tm_mon, &date_entree.tm_year);
    date_entree.tm_mon -= 1;
    date_entree.tm_year -= 1900;

    return date_entree;
}
typedef struct Compte {
    char Num_Compte[19];
    char type_Compte[10];
    float solde;
    char id_client[9];
    struct tm date_ouverture ;
    struct tm date_fin_validite ;
    struct Compte *next ;
} Compte;

typedef struct ListeComptes {
    Compte *premier; 
} ListeComptes;

void ajouterCompte(ListeComptes *liste, Compte *nouveauCompte) {
    if (liste->premier == NULL) {
        liste->premier = nouveauCompte;
    } else {
        Compte *actuel = liste->premier;
        while (actuel->next != NULL) {
            actuel = actuel->next;
        }
        actuel->next = nouveauCompte;
    }
}

Compte* creerCompte() {
    Compte *nouveauCompte = malloc(sizeof(Compte));

    if (nouveauCompte == NULL) {
        printf("Erreur lors de l'allocation mémoire pour le compte.\n");
        return NULL;
    }
        int valid = 0;
    do {
        printf("Entrez le numéro de compte (18 chiffres) : ");
        scanf("%s", nouveauCompte->Num_Compte);

        if (strlen(nouveauCompte->Num_Compte) == 18) {
            valid = 1;
        } else {
            printf("Le numéro de compte doit contenir exactement 18 chiffres. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);
    valid=0;
    do{

    printf("Entrez le type de compte : ");
    scanf("%s", nouveauCompte->type_Compte);
    if (strcmp(nouveauCompte->type_Compte, "courant") == 0 || strcmp(nouveauCompte->type_Compte, "épargne") == 0 || strcmp(nouveauCompte->type_Compte, "jeune") == 0 || strcmp(nouveauCompte->type_Compte, "professionnel") == 0) {
            valid = 1;
        } else {
            printf("Type de compte invalide. Veuillez saisir à nouveau.\n");
        }
    } 
    while (!valid);
     valid = 0;
    do {
        printf("Entrez le solde du compte : ");
        scanf("%f", &nouveauCompte->solde);

        if (nouveauCompte->solde > 0) {
            valid = 1;
        } else {
            printf("Le solde doit être positif. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);

       valid = 0;

    do {
        printf("Entrez l'identifiant du client (8 chiffres) : ");
        scanf("%s", nouveauCompte->id_client);

        if (strlen(nouveauCompte->id_client) == 8) {
            valid = 1;
        } else {
            printf("L'identifiant du client doit contenir exactement 8 chiffres. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);
    do {
        printf("Entrez la date d'ouverture du compte (jj/mm/aaaa) : ");
        nouveauCompte->date_ouverture = saisirDate();

        if (nouveauCompte->date_ouverture.tm_mday >= 1 && nouveauCompte->date_ouverture.tm_mday <= 31 &&
            nouveauCompte->date_ouverture.tm_mon >= 0 && nouveauCompte->date_ouverture.tm_mon <= 11 &&
            nouveauCompte->date_ouverture.tm_year >= 123 && nouveauCompte->date_ouverture.tm_year <= 150) {
            valid = 1;
        } else {
            printf("Format de date invalide. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);

    nouveauCompte->next = NULL;

    return nouveauCompte;
}

void afficherListeComptes(ListeComptes *liste) {
    Compte *actuel = liste->premier;

    if (actuel == NULL) {
        printf("La liste de comptes est vide.\n");
        return;
    }

    printf("Liste des comptes :\n");

    while (actuel != NULL) {
        printf("\nInformations du compte :\n");
        printf("Numéro de compte : %s\n", actuel->Num_Compte);
        printf("Type de compte : %s\n", actuel->type_Compte);
        printf("Solde du compte : %.2f\n", actuel->solde);
        printf("Identifiant du client : %s\n", actuel->id_client);
        printf("Date d'ouverture du compte : %d/%02d/%04d\n", actuel->date_ouverture.tm_mday, actuel->date_ouverture.tm_mon + 1, actuel->date_ouverture.tm_year + 1900);

        actuel = actuel->next;
    }
}

void modifierCompte(Compte *listeComptes, char numCompte[19]) {
    Compte *actuel = listeComptes;

    while (actuel != NULL) {
        if (strcmp(actuel->Num_Compte, numCompte) == 0) {
            printf("Quelles informations souhaitez-vous modifier pour le compte %s ?\n", actuel->Num_Compte);
            printf("1. Numéro de compte\n");
            printf("2. Type de compte\n");
            printf("3. Solde\n");
            printf("4. Identifiant du client\n");
            printf("5. Date d'ouverture du compte\n");
            printf("6. Date de fin de validite du compte\n");
            printf("7. Quitter\n");

            int choix;
            printf("Entrez votre choix : ");
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    printf("Entrez le nouveau numéro de compte : ");
                    scanf("%s", actuel->Num_Compte);
                    break;
                case 2:
                    printf("Entrez le nouveau type de compte : ");
                    scanf("%s", actuel->type_Compte);
                    break;
                case 3:
                    printf("Entrez le nouveau solde du compte : ");
                    scanf("%f", &actuel->solde);
                    break;
                case 4:
                    printf("Entrez le nouvel identifiant du client : ");
                    scanf("%s", actuel->id_client);
                    break;
                case 5:
                    printf("Entrez la nouvelle date d'ouverture du compte (jj/mm/aaaa) : ");
                    actuel->date_ouverture = saisirDate(); 
                    break;
                case 6:
                    printf("Entrez la nouvelle date de fin de validite du compte (jj/mm/aaaa) : ");
                    actuel->date_fin_validite = saisirDate();
                    break;
                case 7:
                    return;
                default:
                    printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
            }
            return;
        }
        actuel = actuel->next;
    }

    printf("Le compte avec le numéro %s n'existe pas.\n", numCompte);
}

void supprimerCompte(ListeComptes *liste, char numCompteASupprimer[19]) {
    Compte *actuel = liste->premier;
    Compte *precedent = NULL;

    while (actuel != NULL && strcmp(actuel->Num_Compte, numCompteASupprimer) != 0) {
        precedent = actuel;
        actuel = actuel->next;
    }

    if (actuel == NULL) {
        printf("Le compte avec le numéro %s n'existe pas.\n", numCompteASupprimer);
        return;
    }

    if (precedent == NULL) {
        liste->premier = actuel->next;
    } else {
        precedent->next = actuel->next;
    }

    free(actuel);
    printf("Le compte avec le numéro %s a été supprimé avec succès.\n", numCompteASupprimer);
}



void depot(ListeComptes *liste, char numCompte[19], float montant) {
    Compte *actuel = liste->premier;
    while (actuel != NULL) {
        if (strcmp(actuel->Num_Compte, numCompte) == 0) {
            printf("\nInformations du compte avant le dépôt :\n");
            printf("Numéro de compte : %s\n", actuel->Num_Compte);
            printf("Solde précédent : %.2f\n", actuel->solde);
            actuel->solde += montant;

            printf("Montant déposé : %.2f\n", montant);
            printf("Nouveau solde : %.2f\n", actuel->solde);

            return;
        }
        actuel = actuel->next;
    }

    printf("Le compte avec le numéro %s n'existe pas.\n", numCompte);
}

void retrait(ListeComptes *liste, char numCompte[19], float montant) {
    Compte *actuel = liste->premier;
    while (actuel != NULL) {
        if (strcmp(actuel->Num_Compte, numCompte) == 0) {
            printf("\nInformations du compte avant le retrait :\n");
            printf("Numéro de compte : %s\n", actuel->Num_Compte);
            printf("Solde précédent : %.2f\n", actuel->solde);
            if (actuel->solde >= montant) {
                actuel->solde -= montant; 
                printf("Montant retiré : %.2f\n", montant);
                printf("Nouveau solde : %.2f\n", actuel->solde);
            } else {
                printf("Solde insuffisant pour effectuer le retrait.\n");
            }

            return;
        }
        actuel = actuel->next;
    }

    printf("Le compte avec le numéro %s n'existe pas.\n", numCompte);
}

void virement(ListeComptes *liste, char numCompteSrc[19], char numCompteDest[19], float montant) {
    Compte *src = NULL;
    Compte *dest = NULL;
    Compte *actuel = liste->premier;
    while (actuel != NULL) {
        if (strcmp(actuel->Num_Compte, numCompteSrc) == 0) {
            src = actuel;
        } else if (strcmp(actuel->Num_Compte, numCompteDest) == 0) {
            dest = actuel;
        }

        actuel = actuel->next;
    }

    if (src == NULL || dest == NULL) {
        printf("Un ou les deux comptes spécifiés n'existent pas.\n");
        return;
    }

    printf("\nInformations du compte source avant le virement :\n");
    printf("Numéro de compte : %s\n", src->Num_Compte);
    printf("Solde avant virement : %.2f\n", src->solde);
    if (src->solde >= montant) {
        src->solde -= montant;
        dest->solde += montant;

        printf("\nMontant virement : %.2f\n", montant);
        printf("Nouveau solde du compte source : %.2f\n", src->solde);
        printf("Nouveau solde du compte destination : %.2f\n", dest->solde);
    } else {
        printf("Solde insuffisant pour effectuer le virement.\n");
    }
}


typedef struct Client {
    char nom[30];
    char prenom[20];
    struct tm date_naissance;
    char adresse[100];
    char email[50];
    char code_postale[6];
    char ville[50];
    char telephone[9];
    struct Client *next; 
} Client;

typedef struct ListeClients {
    Client *premier; 
} ListeClients;

void ajouterClient(ListeClients *liste, Client *nouveauClient) {
    if (liste->premier == NULL) {
        liste->premier = nouveauClient;
    } else {
        Client *actuel = liste->premier;
        while (actuel->next != NULL) {
            actuel = actuel->next;
        }
        actuel->next = nouveauClient;
    }
}

void afficherListeClients(ListeClients *liste) {
    Client *actuel = liste->premier;

    if (actuel == NULL) {
        printf("La liste de clients est vide.\n");
        return;
    }

    printf("Liste des clients :\n");

    while (actuel != NULL) {
        printf("\nInformations du client :\n");
        printf("Nom : %s\n", actuel->nom);
        printf("Prénom : %s\n", actuel->prenom);
        printf("Date de naissance : %d/%02d/%04d\n", actuel->date_naissance.tm_mday, actuel->date_naissance.tm_mon + 1, actuel->date_naissance.tm_year + 1900);
        printf("Adresse : %s\n", actuel->adresse);
        printf("E-mail : %s\n", actuel->email);
        printf("Code postal : %s\n", actuel->code_postale);
        printf("Ville : %s\n", actuel->ville);
        printf("Téléphone : %s\n", actuel->telephone);

        actuel = actuel->next;
    }
}


Client* creerClient() {
    Client *nouveauClient = malloc(sizeof(Client));

    if (nouveauClient == NULL) {
        printf("Erreur lors de l'allocation mémoire pour le client.\n");
        return NULL;
    }

     do {
        printf("Entrez le nom du client : ");
        scanf("%s", nouveauClient->nom);

        if (!estAlphabetique(nouveauClient->nom)) {
            printf("Le nom doit contenir uniquement des lettres. Veuillez saisir à nouveau.\n");
        }
    } while (!estAlphabetique(nouveauClient->nom));
    
    
     do {
        printf("Entrez le prenom du client : ");
        scanf("%s", nouveauClient->prenom);

        if (!estAlphabetique(nouveauClient->prenom)) {
            printf("Le prenom doit contenir uniquement des lettres. Veuillez saisir à nouveau.\n");
        }
    } while (!estAlphabetique(nouveauClient->prenom));
    

    int jour, mois, annee;
    int valid = 0;

    do {
        printf("Entrez la date de naissance du client (jj/mm/aaaa) : ");
        scanf("%d/%d/%d", &jour, &mois, &annee);

        if ((jour >= 1 && jour <= 31) && (mois >= 1 && mois <= 12) && (annee >= 1900 && annee <= 2023)) {
            valid = 1;
        } else {
            printf("Date de naissance invalide. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);

    nouveauClient->date_naissance.tm_mday = jour;
    nouveauClient->date_naissance.tm_mon = mois - 1;
    nouveauClient->date_naissance.tm_year = annee - 1900;


    printf("Entrez l'adresse du client : ");
    scanf("%s", nouveauClient->adresse);

    printf("Entrez l'e-mail du client : ");
    scanf("%s", nouveauClient->email);
    
     valid = 0;
    do {
        printf("Entrez le code postal du client (5 chiffres) : ");
        scanf("%s",nouveauClient->code_postale);
        if (strlen(nouveauClient->code_postale) == 5 && sscanf(nouveauClient->code_postale, "%d", &valid) == 1) {
            valid = 1;
        } else {
            printf("Code postal invalide. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);
    strcpy(nouveauClient->code_postale, nouveauClient->code_postale);
    
    
    do {
        printf("Entrez le nom de ville : ");
        scanf("%s", nouveauClient->ville);

        if (!estAlphabetique(nouveauClient->ville)) {
            printf("Le nom de ville doit contenir uniquement des lettres. Veuillez saisir à nouveau.\n");
        }
    } while (!estAlphabetique(nouveauClient->ville));
    
    
    valid = 0;
    do {
        printf("Entrez le numéro de téléphone du client (8 chiffres) : ");
        scanf("%8s", nouveauClient->telephone);
        if (strlen(nouveauClient->telephone) == 8 && sscanf(nouveauClient->telephone, "%d", &valid) == 1) {
            valid = 1;
        } else {
            printf("Numéro de téléphone invalide. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);
    strcpy(nouveauClient->telephone, nouveauClient->telephone);

    return nouveauClient;
}


typedef struct Abonnement {
    char type[20]; 
    float frais_mensuels; 
    char benefits[200]; 
    struct Abonnement *next; 
} Abonnement;

typedef struct ListeAbonnements {
    Abonnement *premier; 
} ListeAbonnements;

void ajouterAbonnement(ListeAbonnements *liste, Abonnement *nouvelAbonnement) {
    if (liste->premier == NULL) {
        liste->premier = nouvelAbonnement;
    } else {
        Abonnement *actuel = liste->premier;
        while (actuel->next != NULL) {
            actuel = actuel->next;
        }
        actuel->next = nouvelAbonnement;
    }
}

Abonnement* creerAbonnement() {
    Abonnement *nouvelAbonnement = malloc(sizeof(Abonnement));

    if (nouvelAbonnement == NULL) {
        printf("Erreur lors de l'allocation mémoire pour l'abonnement.\n");
        return NULL;
    }

    printf("Entrez le type d'abonnement (Premium, Standard, etc.) : ");
    scanf("%s", nouvelAbonnement->type);

    printf("Entrez les frais mensuels de l'abonnement : ");
    scanf("%f", &nouvelAbonnement->frais_mensuels);

    printf("Entrez les avantages/bénéfices de l'abonnement : ");
    scanf("%s", nouvelAbonnement->benefits);

    nouvelAbonnement->next = NULL;

    return nouvelAbonnement;
}

void afficherListeAbonnements(ListeAbonnements *liste) {
    Abonnement *actuel = liste->premier;

    if (actuel == NULL) {
        printf("La liste d'abonnements est vide.\n");
        return;
    }

    printf("Liste des abonnements :\n");

    while (actuel != NULL) {
        printf("\nType d'abonnement : %s\n", actuel->type);
        printf("Frais mensuels : %.2f\n", actuel->frais_mensuels);
        printf("Avantages : %s\n", actuel->benefits);

        actuel = actuel->next;
    }
}
 typedef struct Operation {
    int operation_id;
    char Num_Compte2[19];
    struct tm operation_date;
    struct tm operation_time;
    char operation_libelle[10];
    struct ListeComptes *listeComptes;
    struct Operation *next;
} Operation;

bool verifierCompteExistence(Compte *listeComptes, char Num_Compte2[19]) {
    Compte *actuel = listeComptes;

    while (actuel != NULL) {
        if (strcmp(actuel->Num_Compte, Num_Compte2) == 0) {
            return true; 
        }
        actuel = actuel->next;
    }

    return false;
} 
Operation* creerOperation(ListeComptes *listeComptes) {
    Operation *nouvelleOperation = malloc(sizeof(Operation));

    if (nouvelleOperation == NULL) {
        printf("Erreur lors de l'allocation mémoire pour l'opération.\n");
        return NULL;
    }

    int valid = 0;

    do {
        printf("Entrez l'identifiant de l'opération (8 chiffres) : ");
        scanf("%d", &nouvelleOperation->operation_id);

        if (nouvelleOperation->operation_id >= 10000000 && nouvelleOperation->operation_id <= 99999999) {
            valid = 1;
        } else {
            printf("L'identifiant de l'opération doit comporter exactement 8 chiffres. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);

        printf("Entrez le numéro de compte associé à l'opération (18 chiffres) : ");
        scanf("%s", nouvelleOperation->Num_Compte2);
    valid = 0;
    int jour, mois, annee;

    do {
        printf("Entrez la date de l'opération (jj/mm/aaaa) : ");
        scanf("%d/%d/%d", &jour, &mois, &annee);

        if ((jour >= 1 && jour <= 31) && (mois >= 1 && mois <= 12) && (annee >= 2023 && annee <= 2050)) {
            valid = 1;
        } else {
            printf("Date de l'opération invalide. Assurez-vous que le jour est entre 1 et 31, le mois entre 1 et 12, et l'année entre 2023 et 2050. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);

    nouvelleOperation->operation_date.tm_mday = jour;
    nouvelleOperation->operation_date.tm_mon = mois - 1;
    nouvelleOperation->operation_date.tm_year = annee - 1900;

    valid = 0;
    int heures, minutes, secondes;

    do {
        printf("Entrez l'heure de l'opération (hh:mm:ss) : ");
        scanf("%d:%d:%d", &heures, &minutes, &secondes);

        if ((heures >= 0 && heures <= 23) && (minutes >= 0 && minutes <= 59) && (secondes >= 0 && secondes <= 59)) {
            valid = 1;
        } else {
            printf("Heure de l'opération invalide. Assurez-vous que les heures sont entre 00 et 23, les minutes entre 00 et 59, et les secondes entre 00 et 59. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);

    nouvelleOperation->operation_time.tm_hour = heures;
    nouvelleOperation->operation_time.tm_min = minutes;
    nouvelleOperation->operation_time.tm_sec = secondes;

     valid = 0;
    char libelle[100];

    do {
        printf("Entrez le libellé de l'opération (depot, retrait, virement) : ");
        scanf("%s", libelle);

        if (strcmp(libelle, "depot") == 0 || strcmp(libelle, "retrait") == 0 || strcmp(libelle, "virement") == 0) {
            valid = 1;
        } else {
            printf("Libellé de l'opération invalide. Le libellé doit être 'depot', 'retrait' ou 'virement'. Veuillez saisir à nouveau.\n");
        }
    } while (!valid);

    strcpy(nouvelleOperation->operation_libelle, libelle);
    
    
 if (strcmp(libelle, "depot") == 0) {
        char numCompteADeposer[19];
        float montantADeposer;

        printf("\nEntrez le numéro de compte sur lequel vous voulez effectuer le dépôt : ");
        scanf("%s", numCompteADeposer);

        printf("Entrez le montant à déposer : ");
        scanf("%f", &montantADeposer);
        ListeComptes listeComptes; 
        depot(&listeComptes, numCompteADeposer, montantADeposer);
    }
    
    else if (strcmp(libelle, "retrait") == 0) {
        char numCompteARetirer[19];
        float montantARetirer;

        printf("\nEntrez le numéro de compte sur lequel vous voulez effectuer le retrait : ");
        scanf("%s", numCompteARetirer);

        printf("Entrez le montant à retirer : ");
        scanf("%f", &montantARetirer);

        retrait(listeComptes, numCompteARetirer, montantARetirer);
    }
    else if (strcmp(libelle, "virement") == 0) {
        char numCompteSrc[19], numCompteDest[19];
        float montant;

        printf("Entrez le numéro de compte source pour le virement : ");
        scanf("%s", numCompteSrc);

        printf("Entrez le numéro de compte destination pour le virement : ");
        scanf("%s", numCompteDest);

        printf("Entrez le montant à virer : ");
        scanf("%f", &montant);

        virement(listeComptes, numCompteSrc, numCompteDest, montant);
    }

    

    nouvelleOperation->next = NULL;

    return nouvelleOperation;
}

float echangeDevises(float montant, const char* deviseOrigine, const char* deviseDestination) {
    float taux_EUR_TND = 3.3; 
    float taux_USD_TND = 2.9; 

    if (strcmp(deviseOrigine, "EUR") == 0) {
        if (strcmp(deviseDestination, "TND") == 0) {
            return montant * taux_EUR_TND;
        }
    } else if (strcmp(deviseOrigine, "USD") == 0) {
        if (strcmp(deviseDestination, "TND") == 0) {
            return montant * taux_USD_TND;
        }
    } else if (strcmp(deviseOrigine, "TND") == 0) {
        if (strcmp(deviseDestination, "EUR") == 0) {
            return montant / taux_EUR_TND;
        } else if (strcmp(deviseDestination, "USD") == 0) {
            return montant / taux_USD_TND;
        }
    }

    printf("Impossible d'effectuer cette conversion.\n");
    return 0.0;
}


    int main() {
        
        ListeComptes listeComptes;
    listeComptes.premier = NULL;
        
    Compte *nouveauCompte = creerCompte();
    if (nouveauCompte != NULL) {
        ajouterCompte(&listeComptes, nouveauCompte);
        
        Compte *nouveauCompte2 = creerCompte();
    if (nouveauCompte2 != NULL) {
        ajouterCompte(&listeComptes, nouveauCompte2);
    }
    }
   afficherListeComptes(&listeComptes);
   

   ListeClients listeClients; 
    listeClients.premier = NULL;

  Client *nouveauClient = creerClient();

    if (nouveauClient != NULL) {
        ajouterClient(&listeClients, nouveauClient);
    }

    afficherListeClients(&listeClients);
    Client *nouveauClient2 = creerClient();

    if (nouveauClient2 != NULL) {
        ajouterClient(&listeClients, nouveauClient2);
    }

    afficherListeClients(&listeClients);
    
    Operation *nouvelleOperation = creerOperation(&listeComptes);
        
        char numCompteADeposer[19];
    float montantADeposer;

    printf("\nEntrez le numéro de compte sur lequel vous voulez effectuer le dépôt : ");
    scanf("%s", numCompteADeposer);

    printf("Entrez le montant à déposer : ");
    scanf("%f", &montantADeposer);
    depot(&listeComptes, numCompteADeposer, montantADeposer);
    
    float montantARetirer;
char numCompteARetirer[19];

printf("\nEntrez le numéro de compte sur lequel vous voulez effectuer le retrait : ");
scanf("%s", numCompteARetirer);

printf("Entrez le montant à retirer : ");
scanf("%f", &montantARetirer);

retrait(&listeComptes, numCompteARetirer, montantARetirer);

char numCompteSource[19];
char numCompteDestination[19];
float montantAVirer;

printf("\nEntrez le numéro de compte source pour le virement : ");
scanf("%s", numCompteSource);

printf("Entrez le numéro de compte destination pour le virement : ");
scanf("%s", numCompteDestination);

printf("Entrez le montant à virer : ");
scanf("%f", &montantAVirer);

virement(&listeComptes, numCompteSource, numCompteDestination, montantAVirer);

    
     char numeroCompteAModifier[19];
    printf("Entrez le numéro de compte que vous souhaitez modifier : ");
    scanf("%s", numeroCompteAModifier);

char numeroCompteASupprimer[19];
printf("Entrez le numéro de compte que vous souhaitez supprimer : ");
scanf("%s", numeroCompteASupprimer);

supprimerCompte(&listeComptes, numeroCompteASupprimer);

float montantEchange;
char deviseOrigine[4];
char deviseDestination[4];

printf("Entrez le montant à échanger : ");
scanf("%f", &montantEchange);

printf("Entrez la devise d'origine (EUR, USD, ou TND) : ");
scanf("%s", deviseOrigine);

printf("Entrez la devise de destination (EUR, USD, ou TND) : ");
scanf("%s", deviseDestination);

float resultat = echangeDevises(montantEchange, deviseOrigine, deviseDestination);
printf("Le montant échangé est de : %.2f %s\n", resultat, deviseDestination);

ListeAbonnements listeAbonnements;
    listeAbonnements.premier = NULL;

    Abonnement *nouvelAbonnement = creerAbonnement();
    if (nouvelAbonnement != NULL) {
        ajouterAbonnement(&listeAbonnements, nouvelAbonnement);
    }

    afficherListeAbonnements(&listeAbonnements);

    return 0;
} 