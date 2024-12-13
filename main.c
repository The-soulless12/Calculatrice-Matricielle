#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#include "biblio.c"

int main()
{
    int maxl,maxc,choix=0;
    bool menuprincipal=false,menurep1=false,again=false,menurep2=false;

    maillon* tete=NULL;
    maillon* tete2=NULL;
    maillon* tetesauv=NULL;

    maillonlig* tete3=NULL;
    maillonlig* tete4=NULL;
    maillonlig* tetesauv2=NULL;
    do
    { //Début de la boucle
    menuprincipal=false;
    choix=0;
    while (choix>3 || choix<1)
    {
        printf("\n\n\n\n\n");
        printf("                          LES MATRICES CREUSES\n\n\n");
        printf("    Choisissez le mode de representation de votre matrice !\n\n");
        printf("    1. Une liste d'element vus comme vecteur.\n");
        printf("    2. Une liste de listes.\n");
        printf("    3. Plus d'informations.\n\n");
        printf("    Je choisis :");
        scanf("%d",&choix);
        if (choix>3 || choix<1)
        {
            system("cls");
        }
    }
    system("cls");
    switch (choix)
    {
    case 1:
        { //début case 01 du principal
            choix=0;
            printf("\n\n\n\n\n");
            printf("                          LES MATRICES CREUSES : REPRESENTATION N 01\n\n");
            printf("Bonjour, et si on creait une matrice ?\n");
            LectMatrice(&tete,&maxl,&maxc);
            system("cls");
            do
            {
                menurep1=false;
                choix=0;
                while (choix>9 || choix<1)
                {
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01\n\n");
                    printf("    Que voulez vous faire maintenant ?\n\n");
                    printf("    1. Afficher votre matrice.\n");
                    printf("    2. Extraire une sous matrice.\n");
                    printf("    3. Diviser votre matrice en sous-blocs de taille egale.\n");
                    printf("    4. Additionner votre matrice a une ou plusieurs autres matrices.\n");
                    printf("    5. Multiplier votre matrice par un vecteur ou une autre matrice.\n");
                    printf("    6. Afficher la transposee de votre matrice.\n");
                    printf("    7. Effectuer l'une de ces operations logiques : NON, ET, OU & OU exclusif.\n");
                    printf("    8. Modifier votre liste.\n");
                    printf("    9. Revenir au menu principal.\n\n");
                    printf("    Je choisis : ");
                    scanf("%d",&choix);
                    if (choix>9 || choix<1)
                    {
                        system("cls");
                    }
                }
                system("cls");
                switch (choix)
                {
                case 1:
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - AFFICHAGE -\n\n");
                    AFFICHE1(&tete,&maxl,&maxc);
                    choix=0;
                    break;
                case 2:
                    choix=0;
                    EXTRAIRE1(&tete,&maxl,&maxc);
                    break;
                case 3:
                    choix=0;
                    DIVISION1(&tete,&maxl,&maxc);
                    break;
                case 4:
                    tetesauv=tete; //afin de pouvoir garder la tete originale pour de futures opérations
                    do //Cette boucle me permettra d'additionner plusieurs matrices tout en gardant la matrice de sortie du précedent calcul
                    {
                    again=false;
                    choix=0;
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - ADDITION -\n\n");
                    ADDITION1(&tetesauv,&tete2,&maxl,&maxc);
                    while ((choix>2) || (choix<1))
                    {
                        printf("\n    Voulez vous additionner cette matrice resultante a une autre matrice ?\n");
                        printf("    1. Oui, je veux additionner encore.\n");
                        printf("    2. Non, je veux m'arreter la et retourner au menu precedent.\n\n");
                        printf("    Je choisis :");
                        scanf("%d",&choix);
                        if ((choix>2) || (choix<1))
                        {
                            printf("    Erreur, veuillez retaper votre demande.\n");
                        }
                    }
                    if (choix==1)
                    {
                        again=true;
                        tetesauv=tete2;
                        system("cls");
                    }
                    else
                    {
                        choix=10;
                    }
                    }
                    while (again==true);
                    break;
                case 5:
                    choix=0;
                    MULTIPLICATION1(&tete,&maxl,&maxc);
                    break;
                case 6:
                    choix=0;
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - TRANSPOSEE -\n\n");
                    TRANSPOSEE1(&tete,&maxl,&maxc);
                    break;
                case 7:
                    choix=0;
                        while(choix>5 || choix<1)
                        {
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - LES OPERATIONS LOGIQUES -\n\n");
                            printf("    Que voulez vous faire maintenant ?\n\n");
                            printf("    1. L'operation NON.\n");
                            printf("    2. L'operation ET.\n");
                            printf("    3. L'operation OU.\n");
                            printf("    4. L'operation OU exclusif.\n");
                            printf("    5. Revenir au menu precedent.\n\n");
                            printf("    Je choisis : ");
                            scanf("%d",&choix);
                            if (choix>5 || choix<1)
                            {
                                system("cls");
                            }
                        }
                        system("cls");
                        switch (choix)
                        {
                        case 1:
                            choix=0;
                            NONLOGIQUE1(&tete,&maxl,&maxc);
                            break;
                        case 2:
                            choix=0;
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - ET LOGIQUE -\n\n");
                            ETLOGIQUE1(&tete,&maxl,&maxc);
                            break;
                        case 3:
                            choix=0;
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - OU LOGIQUE -\n\n");
                            OULOGIQUE1(&tete,&maxl,&maxc);
                            break;
                        case 4:
                            choix=0;
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - OU EXCLUSIF -\n\n");
                            OUXLOGIQUE1(&tete,&maxl,&maxc);
                            break;
                        case 5:
                            choix=0;
                            menurep1=true;
                            break;
                        }
                    break;
                case 8:
                    do
                    {
                    again=false;
                    choix=0;
                    system("cls");
                    MODIFICATION1(&tete,&maxl,&maxc);
                    while ((choix>2) || (choix<1))
                    {
                        printf("\n    Voulez vous modifier encore votre matrice ?\n");
                        printf("    1. Oui, je veux encore la modifier.\n");
                        printf("    2. Non, je veux m'arreter la et retourner au menu precedent.\n\n");
                        printf("    Je choisis :");
                        scanf("%d",&choix);
                        if ((choix>2) || (choix<1))
                        {
                            printf("    Erreur, veuillez retaper votre demande.\n");
                        }
                    }
                    if (choix==1)
                    {
                        again=true;
                    }
                    else
                    {
                        choix=10;
                    }
                    }
                    while (again==true);
                    break;
                case 9:
                    menuprincipal=true;
                    menurep1=false;
                    break;
                }
                if ((choix!=9) && (menurep1!=true))
                {
                    while (choix!=10)
                    {
                        printf("\nPour revenir au menu precedent, tapez 10.\n");
                        printf("Je choisis : ");
                        scanf("%d",&choix);
                        if (choix!=10)
                        {
                            printf("Erreur, veuillez retaper votre demande.\n");
                        }
                    }
                    if (choix==10)
                    {
                        menurep1=true;
                        choix=0;
                        system("cls");
                    }
                }
            }
            while (menurep1==true);
        } //fin case 01 du principal
        break;
    case 2:
        { //début case 02 du principal
            choix=0;
            printf("\n\n\n\n\n");
            printf("                          LES MATRICES CREUSES : REPRESENTATION N 02\n\n");
            printf("Bonjour, et si on creait une matrice ?\n");
            LECTMATRICE2(&tete3,&maxl,&maxc);
            system("cls");
            do
            {
                menurep2=false;
                choix=0;
                while (choix>9 || choix<1)
                {
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02\n\n");
                    printf("    Que voulez vous faire maintenant ?\n\n");
                    printf("    1. Afficher votre matrice.\n");
                    printf("    2. Extraire une sous matrice.\n");
                    printf("    3. Diviser votre matrice en sous-blocs de taille egale.\n");
                    printf("    4. Additionner votre matrice a une ou plusieurs autres matrices.\n");
                    printf("    5. Multiplier votre matrice par un vecteur ou une autre matrice.\n");
                    printf("    6. Afficher la transposee de votre matrice.\n");
                    printf("    7. Effectuer l'une de ces operations logiques : NON, ET, OU & OU exclusif.\n");
                    printf("    8. Modifier votre liste.\n");
                    printf("    9. Revenir au menu principal.\n\n");
                    printf("    Je choisis : ");
                    scanf("%d",&choix);
                    if (choix>9 || choix<1)
                    {
                        system("cls");
                    }
                }
                system("cls");
                switch (choix)
                {
                case 1:
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - AFFICHAGE -\n\n");
                    AFFICHE2(&tete3,&maxl,&maxc);
                    choix=0;
                    break;
                case 2:
                    choix=0;
                    EXTRAIRE2(&tete3,&maxl,&maxc);
                    break;
                case 3:
                    choix=0;
                    DIVISION2(&tete3,&maxl,&maxc);
                    break;
                case 4:
                    tetesauv2=tete3;
                    do //Cette boucle me permettra d'additionner plusieurs matrices tout en gardant la matrice de sortie du précedent calcul
                    {
                    again=false;
                    choix=0;
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - ADDITION -\n\n");
                    ADDITION2(&tetesauv2,&tete4,&maxl,&maxc);
                    while ((choix>2) || (choix<1))
                    {
                        printf("\n    Voulez vous additionner cette matrice resultante a une autre matrice ?\n");
                        printf("    1. Oui, je veux additionner encore.\n");
                        printf("    2. Non, je veux m'arreter la et retourner au menu precedent.\n\n");
                        printf("    Je choisis :");
                        scanf("%d",&choix);
                        if ((choix>2) || (choix<1))
                        {
                            printf("    Erreur, veuillez retaper votre demande.\n");
                        }
                    }
                    if (choix==1)
                    {
                        again=true;
                        tetesauv2=tete4;
                        system("cls");
                    }
                    else
                    {
                        choix=10;
                    }
                    }
                    while (again==true);
                    break;
                case 5:
                    choix=0;
                    MULTIPLICATION2(&tete3,&maxl,&maxc);
                    break;
                case 6:
                    choix=0;
                    printf("\n\n\n\n\n");
                    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - TRANSPOSEE -\n\n");
                    TRANSPOSEE2(&tete3,&maxl,&maxc);
                    break;
                case 7:
                    choix=0;
                        while(choix>5 || choix<1)
                        {
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - LES OPERATIONS LOGIQUES -\n\n");
                            printf("    Que voulez vous faire maintenant ?\n\n");
                            printf("    1. L'operation NON.\n");
                            printf("    2. L'operation ET.\n");
                            printf("    3. L'operation OU.\n");
                            printf("    4. L'operation OU exclusif.\n");
                            printf("    5. Revenir au menu precedent.\n\n");
                            printf("    Je choisis : ");
                            scanf("%d",&choix);
                            if (choix>5 || choix<1)
                            {
                                system("cls");
                            }
                        }
                        system("cls");
                        switch (choix)
                        {
                        case 1:
                            choix=0;
                            NONLOGIQUE2(&tete3,&maxl,&maxc);
                            break;
                        case 2:
                            choix=0;
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - ET LOGIQUE -\n\n");
                            ETLOGIQUE2(&tete3,&maxl,&maxc);
                            break;
                        case 3:
                            choix=0;
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - OU LOGIQUE -\n\n");
                            OULOGIQUE2(&tete3,&maxl,&maxc);
                            break;
                        case 4:
                            choix=0;
                            printf("\n\n\n\n\n");
                            printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - OU EXCLUSIF -\n\n");
                            OUXLOGIQUE2(&tete3,&maxl,&maxc);
                            break;
                        case 5:
                            choix=0;
                            menurep2=true;
                            break;
                        }
                    break;
                case 8:
                    do
                    {
                    again=false;
                    choix=0;
                    system("cls");
                    MODIFICATION2(&tete3,&maxl,&maxc);
                    while ((choix>2) || (choix<1))
                    {
                        printf("\n    Voulez vous modifier encore votre matrice ?\n");
                        printf("    1. Oui, je veux encore la modifier.\n");
                        printf("    2. Non, je veux m'arreter la et retourner au menu precedent.\n\n");
                        printf("    Je choisis :");
                        scanf("%d",&choix);
                        if ((choix>2) || (choix<1))
                        {
                            printf("    Erreur, veuillez retaper votre demande.\n");
                        }
                    }
                    if (choix==1)
                    {
                        again=true;
                    }
                    else
                    {
                        choix=10;
                    }
                    }
                    while (again==true);
                    break;
                case 9:
                    menuprincipal=true;
                    menurep2=false;
                    break;
                }
                if ((choix!=9) && (menurep2!=true))
                {
                    while (choix!=10)
                    {
                        printf("\nPour revenir au menu precedent, tapez 10.\n");
                        printf("Je choisis : ");
                        scanf("%d",&choix);
                        if (choix!=10)
                        {
                            printf("Erreur, veuillez retaper votre demande.\n");
                        }
                    }
                    if (choix==10)
                    {
                        menurep2=true;
                        choix=0;
                        system("cls");
                    }
                }
            }
            while (menurep2==true);
        } //fin case 02 du principal
        break;
    case 3:
        choix=0;
        while (choix!=6)
        {
            printf("\n\n\n\n\n");
            printf("                          LES MATRICES CREUSES\n\n\n");
            printf("    1. Qu'est ce qu'une matrice creuse ?\n");
            printf("    Une matrice creuse est une matrice qui a pour propriete de contenir un nombre important de valeurs nulles.\n\n");
            printf("    2. Les listes lineaires chainees nous permettent d'optimiser de l'espace memoire.\n    D'ailleurs, c'est la raison pour laquelle, vos matrices seront representees sous forme de listes !\n\n");
            printf("    3. Une liste d'element vus comme vecteur :\n");
            printf("    Vos donnees seront stockees dans une liste comprenant les elements vus comme vecteur.\n");
            printf("    La structure utilisee definit uniquement la ligne et la colonne de la valeur non nulle enregistree.\n\n");
            printf("    4. Une liste de listes :\n");
            printf("    Les donnees seront stockees dans une liste de listes ou chaque liste represente une ligne de la matrice.\n");
            printf("    Seuls les elements non nuls sont stockes.\n");
            printf("    Une ligne entierement nulle est representee par un pointeur NIL.\n");
            printf("    L'enregistrement contient seulement le numero de la colonne.\n\n");
            printf("    5. Tant que vous ne quittez pas le menu d'une representation, la tete de votre liste sera sauvergardee.\n\n");
            printf("    6. Pour revenir au menu principal, tapez 6.\n\n    Je choisis : ");
            scanf("%d",&choix);
            system("cls");
        }
        break;
    }
    if (choix==6)
    {
        menuprincipal=true;
    }
    } //fin de la boucle
    while (menuprincipal==true);
    return 0;
}
