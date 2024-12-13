#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

                                    /**Mes types & structures */
typedef int bool;
#define true 1
#define false 0

typedef struct maillon maillon;
struct maillon //Notre maillon est composé de 4 champs : valeur, ligne, colonne et l'adresse du suivant
{
    int lig;
    int col;
    int val;
    maillon* suivant;
};

typedef struct mailloncol mailloncol;
struct mailloncol //Ces maillons contiennent le numéro de la colonne et la valeur non nulle des maillons ainsi que l'adresse du prochain maillon de la même ligne
{
    int colonne;
    int valeur;
    mailloncol* next;
};

typedef struct maillonlig maillonlig;
struct maillonlig //Ces maillons contiennent le numéro de la ligne, l'adresse de la prochaine ligne et pointe vers les maillons qui contiennent les valeurs non nulles de cette ligne en question
{
    int ligne;
    maillonlig* prochain;
    mailloncol* bas;
};

/*Schéma de cette structure : En horizontal : la liste de ligne et en vertical : la liste des valeurs et colonnes

    [ligne | bas | prochain ] ----> [ligne | bas | prochain ] ----> [ligne | bas | prochain ] ----> [ligne | bas | prochain ]
              |                               |                               |                               |
[colonne | valeur | next ]      [colonne | valeur | next ]                   NULL               [colonne | valeur | next ]
                     |                               |                                                               |
[colonne | valeur | next ]      [colonne | valeur | next ]                                      [colonne | valeur | next ]      */

typedef struct sousbloc sousbloc; //Cette structure nous sera utile afin de ranger les sous blocs lors de la division des matrices représentées en liste de listes
struct sousbloc //Ces maillons contiennent le numéro du bloc, l'adresse du prochain bloc et pointe vers la tête maillonlig du sous bloc en question
{
    int bloc;
    sousbloc* after;
    maillonlig* down;
};

/*Schéma de cette structure :
    [bloc | down | after ] ----> [bloc | down | after ] ----> [bloc | down | after ]
              |

    [ligne | bas | prochain ] ----> [ligne | bas | prochain ] ----> [ligne | bas | prochain ]
              |                               |                               |
[colonne | valeur | next ]      [colonne | valeur | next ]                   NULL
                     |                               |
[colonne | valeur | next ]      [colonne | valeur | next ]      */

                                    /**Mes fonctions & procédures*/
/**Structure Maillon*/
//Fonctions et procédures pour retourner les informations contenues dans les champs des maillons (structure maillon)
int lig(maillon* m);
int col(maillon* m);
int val(maillon* m);
maillon* suivant(maillon* m);

//Fonctions et procédures pour affecter des valeurs aux champs du maillon (structure maillon)
void aff_lig(maillon* m,int ligne);
void aff_col(maillon* m,int colonne);
void aff_val(maillon* m,int valeur);
void aff_suivant(maillon* p, maillon* q);

//Fonctions et procédures liées à la structure maillon
maillon* ajoutermaillon(maillon** tete,maillon** q);
void Rechlig(maillon** tete,int* valeur,maillon** ptr,maillon** precedent,bool* existe); //Module de recherche par champ (lig)
void Rechval(maillon** tete,int* valeur,maillon** ptr,maillon** precedent,bool* existe); //Module de recherche par champ (val)
void Rechcol(maillon** tete,int* valeur,maillon** ptr,maillon** precedent,bool* existe); //Module de recherche par champ (col)
void Suppval(maillon** tete,int* valeur); //Module de suppression selon le champ (val)
void Supppos(maillon** tete,maillon** position,maillon** precedent); //Module de suppression selon une position
void Rechmaillon(maillon** tete,maillon** ptr,maillon** precedent,int* ligne,int* colonne,bool* existe); //Module de recherche de maillon selon leur ligne et colonne
void Inserer(maillon** tete,maillon** position,maillon** precedent,int* ligne,int* colonne,int* valeur); //Insere un maillon entre le maillon pointé par le ptr precedent et le ptr position

/**Structure Mailloncol & Maillonlig*/
//Fonctions et procédures pour retourner les informations contenues dans les champs des maillons de ces deux structures
int colonne(mailloncol* m);
int valeur(mailloncol* m);
mailloncol* next(mailloncol* m);
int ligne(maillonlig* m);
maillonlig* prochain(maillonlig* m);
mailloncol* bas(maillonlig* m);

//Fonctions et procédures pour affecter des valeurs aux champs des maillon de ces deux structures
void aff_colonne(mailloncol* m,int colonne);
void aff_valeur(mailloncol* m,int valeur);
void aff_next(mailloncol* p,mailloncol* q);
void aff_ligne(maillonlig* m,int ligne);
void aff_prochain(maillonlig* p,maillonlig* q);
void aff_bas(maillonlig* p,mailloncol* q);

//Fonctions et procédures liées à la structure maillon
mailloncol* ajoutermailloncol(mailloncol** tete,mailloncol** q);
maillonlig* ajoutermaillonlig(maillonlig** tete,maillonlig** q);
void Rechligne(maillonlig** tete,int* lig,maillonlig** ptr,maillonlig** precedent,bool* existe); //Module de recherche par champ (ligne)
void Rechvaleur(mailloncol** tete,int* val,mailloncol** ptr,mailloncol** precedent,bool* existe); //Module de recherche par champ (valeur)
void Rechcolonne(mailloncol** tete,int* col,mailloncol** ptr,mailloncol** precedent,bool* existe); //Module de recherche par champ (colonne)

/**Structure sousbloc*/
//Fonctions et procédures pour retourner les informations contenues dans les champs des maillons de ces deux structures
int bloc(sousbloc* m);
maillonlig* down(sousbloc* m);
sousbloc* after(sousbloc* m);

//Fonctions et procédures pour affecter des valeurs aux champs des maillon de ces deux structures
void aff_bloc(sousbloc* m,int bloc);
void aff_after(sousbloc* p,sousbloc* q);
void aff_down(sousbloc* p,maillonlig* q);

//Fonctions et procédures liées à la structure maillon
sousbloc* ajoutersousbloc(sousbloc** tete,sousbloc** q);

                                    /**Première représentation*/
void LectMatrice(maillon** tete,int* maxl,int* maxc); //Lit et crée une liste contenant que les valeurs non nulles d'une matrice creuse
void AfficheMatrice(maillon** tete,int* begl,int* begc,int* maxl,int* maxc); //affiche le contenu d'une matrice creuse
void Extraire(maillon** tete,maillon** tete2,int* maxl,int* maxc,int* a,int* b,int* c,int* d); //Extrait une sous matrice
void Addition(maillon** tete,maillon** tete2,maillon** tete3); //Fait la somme de deux matrices
void NonLogique(maillon** tete,maillon** tete2,int* maxl,int* maxc); //Applique le non logique sur une matrice
void EtLogique(maillon** tete,maillon** tete2,maillon** tete3); //Effectue un et logique entre deux matrices
void OuLogique(maillon** tete,maillon** tete2,maillon** tete3); //Effectue un ou logique entre deux matrices
void OuxLogique(maillon** tete,maillon** tete2,maillon** tete3); //Effectue un ou exclusif entre deux matrices
void Transposee(maillon** tete,maillon** tete2,int* maxc); //Donne la transposée d'une matrice
void Multiplication(maillon** tete,maillon** tete2,maillon** tete3,int* maxl,int* maxc,int*a); //Effectue la multiplication de deux matrices
void DIVISION1(maillon** tete,int* maxl,int* maxc); //Divise une matrice en sous blocs de tailles égales + interaction
void MODIFICATION1(maillon** tete,int* maxl,int* maxc); //Modifie les valeurs d'une matrice donnée + interaction

//Fonction et procédures des messages d'interactions avec l'utilisateur
void AFFICHE1(maillon** tete,int* maxl,int* maxc);
void EXTRAIRE1(maillon** tete,int* maxl,int* maxc);
void ADDITION1(maillon** tete,maillon** tete2,int* maxl,int* maxc);
void NONLOGIQUE1(maillon** tete,int* maxl,int* maxc);
void ETLOGIQUE1(maillon** tete,int* maxl,int* maxc);
void OULOGIQUE1(maillon** tete,int* maxl,int* maxc);
void OUXLOGIQUE1(maillon** tete,int* maxl,int* maxc);
void TRANSPOSEE1(maillon** tete,int* maxl,int* maxc);
void MULTIPLICATION1(maillon** tete,int* maxl,int* maxc);

                                    /**Deuxième représentation*/
void LECTMATRICE2(maillonlig** tete,int* maxl,int* maxc); //Stocke les données d'une matrice dans une structure de liste de listes
void AfficheMatrice2(maillonlig** tete,int* begl,int* begc,int* maxl,int* maxc); //Affiche une matrice representée sous forme de liste de listes
void NonLogique2(maillonlig** tete,maillonlig** tete2,int* maxl,int* maxc); //Applique le non logique sur une matrice /
void Extraire2(maillonlig** tete,maillonlig** tete2,int* maxl,int* maxc,int* a,int* b,int* c,int* d); //Extrait une sous matrice
void OuLogique2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3); //Effectue un ou logique entre deux matrices
void EtLogique2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3); //Effectue un et logique entre deux matrices
void OuxLogique2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3); //Effectue un ou exclusif entre deux matrices
void Addition2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3); //Fait la somme de deux matrices représentées en liste de listes
void Transposee2(maillonlig** tete,maillonlig** tete2,int* maxc);
void Multiplication2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3,int* maxl,int* maxc,int*a); //Effectue la multiplication de 2 matrices représentée en liste de listes
void MODIFICATION2(maillonlig** tete,int* maxl,int* maxc);

//Fonction et procédures des messages d'interactions avec l'utilisateur
void AFFICHE2(maillonlig** tete,int* maxl,int* maxc);
void NONLOGIQUE2(maillonlig** tete,int* maxl,int* maxc);
void EXTRAIRE2(maillonlig** tete,int* maxl,int* maxc); //Contient juste les affichages
void OULOGIQUE2(maillonlig** tete,int* maxl,int* maxc);
void ETLOGIQUE2(maillonlig** tete,int* maxl,int* maxc);
void OUXLOGIQUE2(maillonlig** tete,int* maxl,int* maxc);
void ADDITION2(maillonlig** tete,maillonlig** tete2,int* maxl,int* maxc);
void TRANSPOSEE2(maillonlig** tete,int* maxl,int* maxc);
void MULTIPLICATION2(maillonlig** tete,int* maxl,int* maxc);

#endif // BIBLIO_H_INCLUDED
