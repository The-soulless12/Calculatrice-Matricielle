#include "biblio.h"
#include <stdio.h>
#include <stdlib.h>

/***************************************************************/                                     /**Structure maillon*/
int lig(maillon* m)
{
    return m->lig;
}

int col(maillon* m)
{
    return m->col;
}

int val(maillon* m)
{
    return m->val;
}

maillon* suivant(maillon* m)
{
    return m->suivant;
}

/***************************************************************/

void aff_val(maillon* m, int valeur)
 {
     m->val=valeur;
 }

void aff_lig(maillon* m, int ligne)
{
     m->lig=ligne;
}

void aff_col(maillon* m, int colonne)
{
     m->col=colonne;
}

void aff_suivant(maillon* p, maillon* q)
{
     p->suivant=q;
}

/***************************************************************/

maillon* ajoutermaillon(maillon** tete,maillon** q)
{
    maillon* p=NULL;
    p=(maillon*)malloc(sizeof(maillon));
    aff_suivant(p,NULL);
    if (*tete == NULL)
    {
       *tete = p;
    }
    else
    {
        aff_suivant(*q,p);
    }
    *q=p;
    return p;
}

void Rechlig(maillon** tete,int* valeur,maillon** ptr,maillon** precedent,bool* existe)
{
    maillon* p=*tete;
    *ptr=NULL;
    *existe=false;
    while ((p!=NULL) && (lig(p)!=*valeur))
    {
        *precedent=p;
        p=suivant(p);
    }
    if (p!=NULL)
    {
        *existe=true;
        *ptr=p;
    }
}

void Rechval(maillon** tete,int* valeur,maillon** ptr,maillon** precedent,bool* existe)
{
    maillon* p=*tete;
    *ptr=NULL;
    *existe=false;
    while ((p!=NULL) && (val(p)!=*valeur))
    {
        *precedent=p;
        p=suivant(p);
    }
    if (p!=NULL)
    {
        *existe=true;
        *ptr=p;
    }
}

void Rechcol(maillon** tete,int* valeur,maillon** ptr,maillon** precedent,bool* existe)
{
    maillon* p=*tete;
    *ptr=NULL;
    *existe=false;
    while ((p!=NULL) && (col(p)!=*valeur))
    {
        *precedent=p;
        p=suivant(p);
    }
    if (p!=NULL)
    {
        *existe=true;
        *ptr=p;
    }
}

void Rechmaillon(maillon** tete,maillon** ptr,maillon** precedent,int* ligne,int* colonne,bool* existe)
{
    bool B=true;
    maillon* p=*tete;
    *ptr=NULL;
    *precedent=NULL;
    *existe=false;
    while ((p!=NULL) && (lig(p)!=*ligne))
    {
        *precedent=p;
        p=suivant(p);
    }
    while (((p!=NULL) && (lig(p)==*ligne)) && B)
    {
        if (col(p)>*colonne) //c'est que le maillon n'existe pas et que sa position a été depassé
        {
            B=false; //pour sortir de la boucle
        }
        else
        {
            if (col(p)<*colonne) //c'est que nous n'avons pas encore atteint ce maillon
            {
                B=true;
                *precedent=p;
                p=suivant(p);
                *ptr=p;
            }
            else
            {
                if (col(p)==*colonne) //c'est que nous l'avons retrouvé
                {
                    B=false; //pour sortir de la boucle
                }
            }
        }
    }
    if ((p!=NULL) && (col(p)==*colonne) && (lig(p)==*ligne))
    {
        *existe=true;
        *ptr=p;
    }
}

void Supppos(maillon** tete,maillon** position,maillon** precedent)
{
    maillon* r=NULL;
    if (*position==*tete)
    {
        *tete=suivant(*position);
        aff_suivant(*position,NULL);
        free(*position);
    }
    else
    {
        aff_suivant(*precedent,suivant(*position));
        free(*position);
    }
}

void Suppval(maillon** tete,int* valeur)
{
    bool existe=false;
    maillon* p=NULL;
    maillon* r=NULL;;
    Rechval(tete,valeur,&p,&r,&existe);
    if (existe==true)
    {
        if (p==*tete)
        {
            *tete=suivant(p);
            free(p);
        }
        else
        {
            aff_suivant(r,suivant(p));
            free(p);
        }
    }
}

void Inserer(maillon** tete,maillon** position,maillon** precedent,int* ligne,int* colonne,int* valeur) //Insere entre precedent et position
{
    maillon* r=NULL;
    if (*tete==NULL)
    {
        r=(maillon*)malloc(sizeof(maillon));
        *tete=r;
        aff_suivant(*tete,NULL);
        aff_lig(*tete,*ligne);
        aff_col(*tete,*colonne);
        aff_val(*tete,*valeur);
    }
    else
    {
    if (*position==*tete) //precedent==NULL il faut une nouvelle tete
    {
        r=(maillon*)malloc(sizeof(maillon)); //la nouvelle tete
        r=*tete;
        aff_suivant(r,*position);
        aff_lig(r,*ligne);
        aff_col(r,*colonne);
        aff_val(r,*valeur);
    }
    else
    {
        if ((*position==NULL) && (*precedent!=NULL)) //precedent est la queue de la liste
        {
            r=(maillon*)malloc(sizeof(maillon));
            aff_suivant(*precedent,r);
            aff_suivant(r,NULL);
            aff_lig(r,*ligne);
            aff_col(r,*colonne);
            aff_val(r,*valeur);
        }
        else
        {
            if ((*position==NULL) && (*precedent==NULL))
            {
                r=(maillon*)malloc(sizeof(maillon));
                aff_suivant(r,*tete);
                *tete=r;
                aff_lig(r,*ligne);
                aff_col(r,*colonne);
                aff_val(r,*valeur);
            }
            else //au milieu de la chaine
            {
                r=(maillon*)malloc(sizeof(maillon));
                aff_suivant(*precedent,r);
                aff_suivant(r,*position);
                aff_lig(r,*ligne);
                aff_col(r,*colonne);
                aff_val(r,*valeur);
            }
        }
    }
    }
}

/***************************************************************/                                     /**Representation 01*/

void LectMatrice(maillon** tete,int* maxl,int* maxc)
{
    int i,j,valeur;
    maillon* p=NULL;
    maillon* q=NULL;
    *tete=NULL;
    do
    {
        printf("Entrez le nombre de lignes de votre matrice :");
        scanf("%d",maxl);
        if (*maxl<1)
        {
            printf("    Erreur, veuillez retaper votre nombre.\n");
        }
    }
    while (*maxl<1);
    do
    {
        printf("Entrez le nombre de colonnes de votre matrice :");
        scanf("%d",maxc);
        if (*maxc<1)
        {
            printf("    Erreur, veuillez retaper votre nombre.\n");
        }
    }
    while (*maxc<1);
    for (i=0;i<*maxl;i++)
    {
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&valeur);
            if (valeur !=0)    //Afin de stocker que les valeurs non nulles
            {
                p=ajoutermaillon(tete,&q);
                aff_val(p,valeur);
                aff_lig(p,i);
                aff_col(p,j);
            }
        }
    }
}

/***************************************************************/

void AfficheMatrice(maillon** tete,int* begl,int* begc,int* maxl,int* maxc)
{
    int i,j;
    maillon* p=*tete;
    for (i=*begl;i<*maxl;i++)
    {
        for (j=*begc;j<*maxc;j++)
        {
            if (p==NULL) //Le cas d'une matrice entiérement nulle
            {
                printf("0 |");
            }
            else
            {
                if ((i==lig(p)) && (j==col(p)))
                {
                    printf("%d |",val(p)); //Affichage des valeurs stockés dans le champ val du maillon
                    p=suivant(p);
                }
                else
                {
                    printf("0 |"); //Affichage des 0 non stockés
                }
            }
        }
        printf("\n");
    }
}

/***************************************************************/

void Extraire(maillon** tete,maillon** tete2,int* maxl,int* maxc,int* a,int* b,int* c,int* d)
{
    maillon* p=*tete;
    maillon* q=NULL;
    maillon* p2=NULL;
    *tete2=NULL;
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - EXTRACTION -\n\n");
    printf("Note : Veuillez entrer des indices positifs sachant que l'indice 0 existe.\n");
    do
    {
       printf("Entrez l'indice de la ligne de la premiere case :");
       scanf("%d",a);
       if ((-1>*a) || (*a>*maxl-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((-1>*a) || (*a>*maxl-1)); //a ne doit pas déborder des dimensions de la matrice
    do
    {
       printf("Entrez l'indice de la colonne de la premiere case :");
       scanf("%d",b);
       if ((-1>*b) || (*b>*maxc-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((-1>*b) || (*b>*maxc-1)); //b ne doit pas déborder des dimensions de la matrice
    do
    {
       printf("Entrez l'indice de la ligne de la derniere case :");
       scanf("%d",c);
       if ((*c<*a) || (*c>*maxl-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((*c<*a) || (*c>*maxl-1));  //On vérifie que la dernière case se trouve bien après la première case et ne déborde pas
    do
    {
       printf("Entrez l'indice de la colonne de la derniere case :");
       scanf("%d",d);
       if ((*d<*b) || (*d>*maxc-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((*d<*b) || (*d>*maxc-1)); //On vérifie que la dernière case se trouve bien après la première case et ne déborde pas
    while(p!=NULL)
    {
        if ((((*a-1)<lig(p))&&(lig(p)<(*c+1)))&&(((*b-1)<col(p))&&(col(p)<(*d+1))))
        {
            p2=ajoutermaillon(tete2,&q);  //Création de la sous liste
            aff_val(p2,val(p));
            aff_lig(p2,lig(p));
            aff_col(p2,col(p));
        }
        p=suivant(p); //Nous passerons au maillon suivant dans tous les cas, que la condition soit vérifiée ou pas afin d'éviter une boucle infinie
    }
}

/***************************************************************/

void Addition(maillon** tete,maillon** tete2,maillon** tete3)
{
    maillon* p=*tete;
    maillon* q=*tete2;
    maillon* w=NULL;
    maillon* y=NULL;
    *tete3=NULL;
    if ((p==NULL) && (q==NULL)) //Les cas spéciaux
    {
        *tete3=NULL;
    }
    else
    {
        if ((p==NULL) && (q!=NULL))
        {
            *tete3=q;
        }
        else
        {
            if ((p!=NULL) && (q==NULL))
            {
                *tete3=p;
            }
        }
    }
    while ((p!=NULL) && (q!=NULL))
    {
        if ((lig(p)<lig(q)) || ((lig(p)==lig(q)) && (col(p)<col(q))))  //La case que pointe q se situe en dessous de celle que p pointe ou à droite de cette dernière
            {
                w=ajoutermaillon(tete3,&y);
                aff_val(w,val(p));
                aff_lig(w,lig(p));
                aff_col(w,col(p));
                p=suivant(p);
            }
            else
            {
                if ((lig(p)>lig(q)) || ((lig(p)==lig(q)) && (col(p)>col(q)))) //La case que pointe p se situe en dessous de celle que q pointe ou à droite de cette dernière
                {
                    w=ajoutermaillon(tete3,&y);
                    aff_val(w,val(q));
                    aff_lig(w,lig(q));
                    aff_col(w,col(q));
                    q=suivant(q);
                }
                else
                {
                    if  ((lig(p)==lig(q)) && (col(p)==col(q))) //Le cas de l'addition
                    {
                        if (val(q)+val(p)!=0)
                        {
                            w=ajoutermaillon(tete3,&y);
                            aff_val(w,val(q)+val(p));
                            aff_lig(w,lig(q));
                            aff_col(w,col(q));
                        }
                        p=suivant(p);
                        q=suivant(q);
                    }
                }
            }
        if ((p==NULL) && (q!=NULL))
        {
            aff_suivant(w,q);
        }
        else
        {
            if ((p!=NULL) && (q==NULL))
            {
                aff_suivant(w,p);
            }
        }
    }
}

/***************************************************************/

void NonLogique(maillon** tete,maillon** tete2,int* maxl,int* maxc)
{
    maillon* p=*tete;
    maillon* q=NULL;
    maillon* y=NULL;
    *tete2=NULL;
    int i,j;
    for (i=0;i<*maxl;i++)
    {
        for (j=0;j<*maxc;j++)
        {
            if (p==NULL)    //C'est pour traiter le cas ou la boucle n'atteint pas la fin mais que le p est déjà à NIL
            {
                q=ajoutermaillon(tete2,&y);
                aff_val(q,1);
                aff_lig(q,i);
                aff_col(q,j);
            }
            else
            {
                if ((lig(p) == i) && (col(p) == j)) //C'est que c'est une case à valeur non nulle, nous n'avons pas besoin d'elle
                {
                    p=suivant(p);
                }
                else
                {
                    q=ajoutermaillon(tete2,&y); //Je ne crée des maillons que pour les valeurs nulles qui n'avaient pas de maillons dans la liste originale
                    aff_val(q,1);
                    aff_lig(q,i);
                    aff_col(q,j);
                }
            }
        }
    }
}

/***************************************************************/

void EtLogique(maillon** tete,maillon** tete2,maillon** tete3)
{
    maillon* p=*tete;
    maillon* q=*tete2;
    maillon* y=NULL;
    maillon* w=NULL;
    *tete3=NULL;
    if ((p==NULL) || (q==NULL))
    {
        *tete3=NULL; //Pour avoir un 1 logique, il faudrait qu'il y ait des valeurs non nulles de part et d'autres et si les ptr sont à Nil c'est qu'il n'y a que des 0 dans ces matrices
    }
    while ((p!=NULL) && (q!=NULL))
    {
        if ((lig(p)<lig(q)) || ((lig(p)==lig(q)) && (col(p)<col(q))))  //La case que pointe q se situe en dessous de celle que p pointe ou à droite de cette dernière
            {
                p=suivant(p);
            }
            else
            {
                if ((lig(p)>lig(q)) || ((lig(p)==lig(q)) && (col(p)>col(q)))) //La case que pointe p se situe en dessous de celle que q pointe ou à droite de cette dernière
                {
                    q=suivant(q);
                }
                else
                {
                    if  ((lig(p)==lig(q)) && (col(p)==col(q))) //Le seul cas qui nous permet de créer un maillon contenant un 1 logique
                    {
                        w=ajoutermaillon(tete3,&y);
                        aff_val(w,1);
                        aff_lig(w,lig(q));
                        aff_col(w,col(q));
                        p=suivant(p);
                        q=suivant(q);
                    }
                }
            }
        if ((p==NULL) && (q!=NULL))
        {
            q=NULL;
        }
        else
        {
            if ((p!=NULL) && (q==NULL))
            {
                p=NULL;
            }
        }
    }
}

/***************************************************************/

void OuLogique(maillon** tete,maillon** tete2,maillon** tete3)
{
    maillon* p=*tete;
    maillon* q=*tete2;
    maillon* y=NULL;
    maillon* w=NULL;
    *tete3=NULL;
     if ((p==NULL) && (q==NULL))
    {
        *tete3=NULL; //Le cas ou nous ne pouvons pas avoir de 1 logique (que des 0)
    }
    else
    {
         if ((p==NULL) && (q!=NULL))
        {
            p=q;
        }
        else
        {
            if ((p!=NULL) && (q==NULL))
            {
                q=p;
            }
        }
    }
    while ((p!=NULL) && (q!=NULL))
    {
        w=ajoutermaillon(tete3,&y);
        aff_val(w,1);
        if ((lig(p)<lig(q)) || ((lig(p)==lig(q)) && (col(p)<col(q))))  //La case que pointe q se situe en dessous de celle que p pointe ou à droite de cette dernière
            {
                aff_lig(w,lig(p));
                aff_col(w,col(p));
                p=suivant(p);
            }
            else
            {
                if ((lig(p)>lig(q)) || ((lig(p)==lig(q)) && (col(p)>col(q)))) //La case que pointe p se situe en dessous de celle que q pointe ou à droite de cette dernière
                {
                    aff_lig(w,lig(q));
                    aff_col(w,col(q));
                    q=suivant(q);
                }
                else
                {
                    if  ((lig(p)==lig(q)) && (col(p)==col(q)))
                    {
                        aff_lig(w,lig(q));
                        aff_col(w,col(q));
                        p=suivant(p);
                        q=suivant(q);
                    }
                }
            }
        if ((p==NULL) && (q!=NULL))
        {
            p=q;
        }
        else
        {
            if ((p!=NULL) && (q==NULL))
            {
                q=p;
            }
        }
    }
}

/***************************************************************/

void OuxLogique(maillon** tete,maillon** tete2,maillon** tete3)
{
    maillon* p=*tete;
    maillon* q=*tete2;
    maillon* y=NULL;
    maillon* w=NULL;
    /*Contrairement au Ou logique, si l'un des pointeurs p ou q est égal à NIL en plein parcourt,nous ne pouvons pas pointer
  ce dernier vers le pointeur restant car cela impacterait sur le cas 0 XOR 1 qui donnera 0 au lieu de 1 s'il reste des maillons.
    Alors, nous allons créer un maillon z qui aura pour valeurs de champs col et lig des valeurs qui pousseront le second
  pointeur à pointer vers z et donc, sortir de la grande boucle*/
    maillon* z=NULL;
    z=(maillon*)malloc(sizeof(maillon));
    aff_suivant(z,NULL);
    aff_lig(z,9999999999999999);
    aff_col(z,9999999999999999);    //Création du maillon vide
    *tete3=NULL;
     if ((p==NULL) && (q==NULL))
    {
        *tete3=NULL;
    }
    else
    {
         if ((p==NULL) && (q!=NULL))
        {
            p=q;
        }
        else
        {
            if ((p!=NULL) && (q==NULL))
            {
                q=p;
            }
        }
    }
    while ((p!=NULL) && (q!=NULL)&&((p!=z)||(q!=z)))
    {
        if ((lig(p)<lig(q)) || ((lig(p)==lig(q)) && (col(p)<col(q))))  //La case que pointe q se situe en dessous de celle que p pointe ou à droite de cette dernière
            {
                w=ajoutermaillon(tete3,&y);
                aff_val(w,1);
                aff_lig(w,lig(p));
                aff_col(w,col(p));
                p=suivant(p);
            }
            else
            {
                if ((lig(p)>lig(q)) || ((lig(p)==lig(q)) && (col(p)>col(q)))) //La case que pointe p se situe en dessous de celle que q pointe ou à droite de cette dernière
                {
                    w=ajoutermaillon(tete3,&y);
                    aff_val(w,1);
                    aff_lig(w,lig(q));
                    aff_col(w,col(q));
                    q=suivant(q);
                }
                else
                {
                    if  ((lig(p)==lig(q)) && (col(p)==col(q)))
                    {
                        p=suivant(p);
                        q=suivant(q);
                    }
                }
            }
        if ((p==NULL) && (q!=NULL))
        {
            p=z;
        }
        else
        {
            if ((p!=NULL) && (q==NULL))
            {
                q=z;
            }
        }
    }
}

/***************************************************************/

void Transposee(maillon** tete,maillon** tete2,int* maxc)
{
    int i;
    bool* existe=false;
    *tete2=NULL;
    maillon* p=*tete;
    maillon* tete3=NULL;
    maillon* q=NULL;
    maillon* y=NULL;
    maillon* z=NULL;
    maillon* a=NULL;
    maillon* t=NULL;
    while (p!=NULL) //j'effectue une copie de la liste en inversant les indices
    {
        q=ajoutermaillon(&tete3,&y);
        aff_val(q,val(p));
        aff_col(q,lig(p));
        aff_lig(q,col(p));
        p=suivant(p);
    }
    p=tete3;
    for (i=0;i<*maxc;i++) //Je réordonne les maillons
    {
        do
        {
            Rechlig(&tete3,&i,&z,&t,&existe);
            if (existe==true)
            {
                a=ajoutermaillon(tete2,&y);
                aff_val(a,val(z));
                aff_col(a,col(z));
                aff_lig(a,lig(z));
                aff_lig(z,-1); //on met -1 car cet indice n'existe pas et afin de ne plus retomber sur ce maillon étant donné que la recherche me donne le premier maillon vérifiant la condition donné
            }
        }
        while (existe==true);
    }
}

/***************************************************************/

void Multiplication(maillon** tete,maillon** tete2,maillon** tete3,int* maxl,int* maxc,int*a)
{
    int i,j,h,valeur,valeur2=0,somme=0,choix=0;
    maillon* r=NULL;
    maillon* y=NULL;
    maillon* k=NULL;
    maillon* t=NULL;
    valeur=0;
    *a=0;
    bool existe;
    maillon* newtete=NULL; //C'est la tete de la transposée de la 2nd matrice
    *tete2=NULL;
    *tete3=NULL;
    /*Afin de multiplier nos matrices, ces dernières doivent être compatibles et c'est la raison pour laquelle,
    la liste de la seconde matrice sera créee dans ce module tout en respectant la régle (en fixant le nombre de lignes*/
    while ((choix>2) || (choix<1))
    {
        printf("\n\n\n\n\n");
        printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - MULTIPLICATION -\n\n");
        printf("    Que voulez vous faire ?\n\n");
        printf("    1. Multiplier votre matrice par un vecteur.\n");
        printf("    2. Multiplier votre matrice par une autre matrice.\n\n");
        printf("    Je choisis :");
        scanf("%d",&choix);
        if ((choix>2) || (choix<1))
        {
            system("cls");
        }
    }
    if (choix==1)
    {
        *a=1;
        printf("\nVotre matrice et votre vecteur doivent etre compatibles alors le nombre de lignes de votre vecteur est fixe a : %d\n",*maxc);
    }
    else
    {
       printf("\nPour que les 2 matrices soient compatibles, le nombre de lignes de votre seconde matrice sera fixe a : %d\n",*maxc);
       printf("Entrez le nombre de colonnes de votre seconde matrice :");
       scanf("%d",a);
    }
    for (i=0;i<*maxc;i++)
    {
        for (j=0;j<*a;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&valeur);
            if (valeur !=0)    //Afin de stocker que les valeurs non nulles
            {
                r=ajoutermaillon(tete2,&y);
                aff_val(r,valeur);
                aff_lig(r,i);
                aff_col(r,j);
            }
        }
    }
    //Le produit
    Transposee(tete2,&newtete,&a); //Afin d'éviter de parcourir la 2nd liste plusieurs fois, on trie cette dernière en effectuant la transposée
    maillon* p=*tete;
    maillon* q=newtete;
    for (i=0;i<*maxl;i++)
    {
        q=newtete;
        for (j=0;j<*a;j++)
        {
            for (h=0;h<*maxc;h++)
            {
                if (p==NULL)  //Liste 01
                {
                    valeur=0;
                }
                else
                {
                    if ((lig(p)==i) && (col(p)==h))
                    {
                        valeur=val(p);
                        p=suivant(p);
                    }
                    else
                    {
                        valeur=0;
                    }
                }
                if (q==NULL)  //Liste 02
                {
                    valeur2=0;
                }
                else
                {
                    if ((lig(q)==j) && (col(q)==h))
                    {
                        valeur2=val(q);
                        q=suivant(q);
                    }
                    else
                    {
                        valeur2=0;
                    }
                }
                somme=somme+valeur*valeur2;
            }
            if (somme!=0)
            {
                r=ajoutermaillon(tete3,&y); //création de la liste finale
                aff_val(r,somme);
                aff_lig(r,i);
                aff_col(r,j);
            }
            somme=0;
            if ((q!=NULL) && (p!=*tete)) //pour éviter les parcours de recherche dans le cas ou p n'a pas bougé (ex : ligne 0 de la matrice vide)
            {
                Rechlig(tete,&i,&k,&t,&existe); // car p doit revenir au début de sa ligne
                if (existe==true)
                {
                    p=k;
                }
            }
        }
    }
}

/***************************************************************/

void DIVISION1(maillon** tete,int* maxl,int* maxc)
{
    int a,b,nb=0; // nb est le nombre de sous blocs
    bool trouve=false;
    maillon* p=*tete;
    maillon* q=NULL;
    maillon* r=NULL;
    maillon* tete2=NULL;
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - DIVISION -\n\n");
    do
    {
        do
        {
           printf("Entrez le nombre de lignes des sous blocs voulus :");
           scanf("%d",&a);
           if ((a<0) || (a>*maxl+1))
           {
               printf("             Erreur, veuillez retaper votre indice !\n");
           }
        }
        while ((a<0) || (a>*maxl+1));
        do
        {
           printf("Entrez le nombre de colonnes des sous blocs voulus :");
           scanf("%d",&b);
           if ((b<0) || (b>*maxl+1))
           {
               printf("             Erreur, veuillez retaper votre indice !\n");
           }
        }
        while ((b<0) || (b>*maxl+1));
        if ((*maxl%a!=0)&&(*maxc%b!=0))
        {
            printf("\nNous ne pouvons malheureusement pas diviser votre matrice en sous blocs de %d lignes et %d colonnes.\nVeuillez entrer de nouvelles dimensions !\n",a,b);
        }
    }
    while ((*maxl%a!=0)&&(*maxc%b!=0));
    //La division
    /*Cette boucle ci dessous consiste à lire les indices des sous blocs un par un
    Exemple : Pour une matrice 4 fois 4 que l'on veut diviser en sous blocs de 2 fois 2 on a
    00/01 | 02/03
    10/11 | 12/13
    -------------
    20/21 | 22/23
    30/31 | 32/33 est notre matrice représentée par des couples (i,j) notre boucle va établir cette séquence : 00 01 10 11 | 02 03 12 13 | 20 21 30 31 | 22 23 32 33
    la lecture se fera sous blocs par sous blocs du haut vers le bas et de la gauche vers la droite*/
    int i=0,j=0,c=0,d=0,e=a,f=b;
    if (p!=NULL)
    {
    do
    {
        do
        {
            for (i=c;i<e;i++)
            {
               for (j=d;j<f;j++)
               {
                   while ((p!=NULL) && (trouve==false))
                   {
                       if ((lig(p)==i) && (col(p)==j))
                       {
                           r=ajoutermaillon(&tete2,&q);
                           aff_val(r,val(p));
                           aff_lig(r,i);
                           aff_col(r,j);
                           trouve=true;
                       }
                       p=suivant(p);
                   }
                   p=*tete;
                   trouve=false;
               }
            }
            d=f;
            f=f+b;
        }
        while (d!=*maxc);
        f=b;
        d=0;
        c=e;
        e=e+a;
    }
    while (c!=*maxl); //a la fin de cette boucle on obtient une liste de maillons ordonnés selon leur bloc et il ne nous reste plus qu'à les afficher !
    }
    //l'affichage
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - DIVISION -\n\n");
    i=0;
    j=0;
    c=0;
    d=0;
    e=a;
    f=b;
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    AfficheMatrice(tete,&c,&d,maxl,maxc);
    printf("\nVoici vos sous-blocs :\n");
    nb=((*maxc)*(*maxl))/((a)*(b));//Calcul du nombre de sous blocs
    int cpt=1;
    p=tete2;
    if (p==NULL) //Le cas d'une matrice nulle
    {
        printf("0 |");
    }
    else //on réutilise la boucle séquentielle créée précédement
    {
        do
        {
            do
            {
                printf("Sous bloc n %d :\n",cpt);
                for (i=c;i<e;i++)
                {
                   for (j=d;j<f;j++)
                   {
                       if (p==NULL)
                       {
                           printf("0 |");
                       }
                       else
                       {
                           if ((i==lig(p)) && (j==col(p)))
                           {
                               printf("%d |",val(p)); //Affichage des valeurs stockés dans le champ val du maillon
                               p=suivant(p);
                           }
                           else
                           {
                           printf("0 |"); //Affichage des 0 non stockés
                           }
                        }
                   }
                   printf("\n");
                }
                printf("\n");
                d=f;
                f=f+b;
                cpt++;
            }
            while (d!=*maxc);
            f=b;
            d=0;
            c=e;
            e=e+a;
        }
        while (c!=*maxl);
    }
    /*Note : nous avons donc trié les sous blocs dans la même liste et si nous désirons retrouver la tête du nieme sous blocs, il suffit simplement de parcourir la liste et de s'arreter à la (n-1)ieme incohérence entre les indices lignes :
    Exemple : Pour une matrice 4 fois 4 que l'on veut diviser en sous blocs de 2 fois 2 on a
    00/01 | 02/03
    10/11 | 12/13
    -------------
    20/21 | 22/23
    30/31 | 32/33 les maillons sont triés de la sorte : 00 01 10 (11 | 02) 03 12 (13 | 20) 21 30 (31 | 22) 23 32 33 et si l'on veut chercher la tete du 3eme sous blocs on a :
    - entre (11 | 02) il y a une incohérence au niveau des indices
    - entre  (13 | 20) et (31 | 22) aussi
    la (n-1)ieme incohérence est celle du (13 | 20) alors le sous bloc 3 commence à partir du maillon (2,0)*/
}

/***************************************************************/                                     /**Interaction avec l'utilisateur*/

void AFFICHE1(maillon** tete,int* maxl,int* maxc)
{
    int begl=0,begc=0;
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void EXTRAIRE1(maillon** tete,int* maxl,int* maxc)
{
    int a,b,c,d,begl=0,begc=0;
    maillon* tete2;
    Extraire(tete,&tete2,maxl,maxc,&a,&b,&c,&d);
    c=c+1;
    d=d+1;
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - EXTRACTION -\n\n");
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\n");
    printf("Et voici votre sous matrice composee de %d lignes et %d colonnes :\n",c-a,d-b);
    AfficheMatrice(&tete2,&a,&b,&c,&d);
}

/***************************************************************/

void ADDITION1(maillon** tete,maillon** tete2,int* maxl,int* maxc)
{
    int begl=0,begc=0,i,j,valeur;
    maillon* tete3=NULL;
    maillon* p=NULL;
    maillon* q=NULL;
    printf("Etant donne que nous ne pouvons additionner que des matrices de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&valeur);
            if (valeur !=0)    //Afin de stocker que les valeurs non nulles
            {
                p=ajoutermaillon(&tete3,&q);
                aff_val(p,valeur);
                aff_lig(p,i);
                aff_col(p,j);
            }
        }
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - ADDITION -\n\n");
    Addition(tete,&tete3,tete2);
    printf("La matrice A :\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\nLa matrice B :\n");
    AfficheMatrice(&tete3,&begl,&begc,maxl,maxc);
    printf("\nA + B =\n");
    AfficheMatrice(tete2,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void NONLOGIQUE1(maillon** tete,int* maxl,int* maxc)
{
    int begl=0,begc=0;
    maillon* tete2=NULL;
    NonLogique(tete,&tete2,maxl,maxc);
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - NON LOGIQUE -\n\n");
    printf("Voici votre matrice :\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\nEt en appliquant le NON logique, on obtient :\n");
    AfficheMatrice(&tete2,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void ETLOGIQUE1(maillon** tete,int* maxl,int* maxc)
{
    int i,j,valeur,begl=0,begc=0;
    maillon* p=NULL;
    maillon* q=NULL;
    maillon* tete2=NULL;
    maillon* tete3=NULL;
    printf("Afin d'effectuer cette operation logique, vos matrices doivent etre de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&valeur);
            if (valeur !=0)    //Afin de stocker que les valeurs non nulles
            {
                p=ajoutermaillon(&tete2,&q);
                aff_val(p,valeur);
                aff_lig(p,i);
                aff_col(p,j);
            }
        }
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - ET LOGIQUE -\n\n");
    EtLogique(tete,&tete2,&tete3);
    printf("La matrice A :\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\nLa matrice B : \n");
    AfficheMatrice(&tete2,&begl,&begc,maxl,maxc);
    printf("\nA ET B =\n");
    AfficheMatrice(&tete3,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void OULOGIQUE1(maillon** tete,int* maxl,int* maxc)
{
    int i,j,valeur,begl=0,begc=0;
    maillon* p=NULL;
    maillon* q=NULL;
    maillon* tete2=NULL;
    maillon* tete3=NULL;
    printf("Afin d'effectuer cette operation logique, vos matrices doivent etre de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&valeur);
            if (valeur !=0)    //Afin de stocker que les valeurs non nulles
            {
                p=ajoutermaillon(&tete2,&q);
                aff_val(p,valeur);
                aff_lig(p,i);
                aff_col(p,j);
            }
        }
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - OU LOGIQUE -\n\n");
    OuLogique(tete,&tete2,&tete3);
    printf("La matrice A :\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\nLa matrice B :\n");
    AfficheMatrice(&tete2,&begl,&begc,maxl,maxc);
    printf("\nA OU B =\n");
    AfficheMatrice(&tete3,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void OUXLOGIQUE1(maillon** tete,int* maxl,int* maxc)
{
    int i,j,valeur,begl=0,begc=0;
    maillon* p=NULL;
    maillon* q=NULL;
    maillon* tete2=NULL;
    maillon* tete3=NULL;
    printf("Afin d'effectuer cette operation logique, vos matrices doivent etre de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&valeur);
            if (valeur !=0)    //Afin de stocker que les valeurs non nulles
            {
                p=ajoutermaillon(&tete2,&q);
                aff_val(p,valeur);
                aff_lig(p,i);
                aff_col(p,j);
            }
        }
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - OU EXCLUSIF -\n\n");
    OuxLogique(tete,&tete2,&tete3);
    printf("La matrice A :\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("La matrice B :\n");
    AfficheMatrice(&tete2,&begl,&begc,maxl,maxc);
    printf("\nA OUX B =\n");
    AfficheMatrice(&tete3,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void TRANSPOSEE1(maillon** tete,int* maxl,int* maxc)
{
    maillon* tete2=NULL;
    int begl=0,begc=0;
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    Transposee(tete,&tete2,maxc);
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\nEt voici la transposee de votre matrice est :\n");
    AfficheMatrice(&tete2,&begl,&begc,maxc,maxl);
}

/***************************************************************/

void MULTIPLICATION1(maillon** tete,int* maxl,int* maxc)
{
    int a=0,begl=0,begc=0;
    maillon* tete2=NULL;
    maillon* tete3=NULL;
    Multiplication(tete,&tete2,&tete3,maxl,maxc,&a);
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - MULTIPLICATION -\n\n");
    printf("La matrice A :\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    if (a==1)
    {
        printf("\nLe vecteur B :\n");
    }
    else
    {
        printf("\nLa matrice B :\n");
    }
    AfficheMatrice(&tete2,&begl,&begc,maxc,&a);
    printf("\nA x B =\n");
    AfficheMatrice(&tete3,&begl,&begc,maxl,&a);
}

/***************************************************************/

void MODIFICATION1(maillon** tete,int* maxl,int* maxc)
{
    int a=0,b=0,begl=0,begc=0,valeur=0;
    bool existe=false;
    maillon* p=NULL;
    maillon* q=NULL;
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - MODIFICATION -\n\n");
    printf("Oops, suite a une erreur de saisie ou un oubli, vous desirez changer les valeurs de votre matrice.\n");
    printf("Rappel des valeurs entrees:\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\n");
    do
    {
        a=0;
        printf("Entrez la ligne de la case erronee :");
        scanf("%d",&a);
        if (a>*maxl || a<0)
        {
            printf("    Erreur, veuillez entrer de nouveau votre indice.\n");
        }
    }
    while (a>*maxl || a<0);
    do
    {
        b=0;
        printf("Entrez la colonne de la case erronee :");
        scanf("%d",&b);
        if (b>*maxc || b<0)
        {
            printf("    Erreur, veuillez entrer de nouveau votre indice.\n");
        }
    }
    while (b>*maxc || b<0);
    printf("Entrez maintenant la valeur qui sera inseree a la case [%d,%d] de votre matrice :",a,b);
    scanf("%d",&valeur);
    //Les modifications peuvent etre faites soient par une suppression de maillon, une insertion de maillon ou une simple affectation au champs val
    Rechmaillon(tete,&p,&q,&a,&b,&existe);
    if (valeur==0) //0 devient 0 ou bien valeur devient 0 (cas de la suppression car on ne stocke pas les valeurs nulles)
    {
        if (existe==true) //Le maillon existait et donc il avait une valeur non nulle, il faut maintenant le supprimer !
        {
            Supppos(tete,&p,&q);
        }
        //Si existe==false c'est que le maillon de base contenait une valeur nulle et donc, il n'avait pas été crée au tout début, on ne fait rien
    }
    else // 0 devient valeur ou valeur devient valeur (insertion de maillon ou juste une affectation)
    {
        if (existe==true) //le maillon existe déjà alors nous ne ferons qu'une simple affectation
        {
            aff_val(p,valeur);
        }
        else //Le maillon n'existe pas, nous devons l'inserer dans cette liste
        {
            Inserer(tete,&p,&q,&a,&b,&valeur);
        }
    }
}

/***************************************************************/                                     /**Structure maillonlig & mailloncol */
int colonne(mailloncol* m)
{
    return m->colonne;
}

int valeur (mailloncol* m)
{
    return m->valeur;
}

mailloncol* next (mailloncol* m)
{
    return m->next;
}

int ligne (maillonlig* m)
{
    return m->ligne;
}

maillonlig* prochain (maillonlig* m)
{
    return m->prochain;
}

mailloncol* bas (maillonlig* m)
{
    return m->bas;
}

/***************************************************************/

void aff_colonne(mailloncol* m,int colonne)
{
    m->colonne=colonne;
}

void aff_valeur(mailloncol* m,int valeur)
{
    m->valeur=valeur;
}

void aff_next(mailloncol* p,mailloncol* q)
{
    p->next=q;
}

void aff_ligne(maillonlig* m,int ligne)
{
    m->ligne=ligne;
}

void aff_prochain(maillonlig* p,maillonlig* q)
{
    p->prochain=q;
}

void aff_bas(maillonlig* p,mailloncol* q)
{
    p->bas=q;
}

/***************************************************************/

mailloncol* ajoutermailloncol(mailloncol** tete,mailloncol** q)
{
    mailloncol* p=NULL;
    p=(mailloncol*)malloc(sizeof(mailloncol));
    aff_next(p,NULL);
    if (*tete == NULL)
    {
       *tete = p;
    }
    else
    {
        aff_next(*q,p);
    }
    *q=p;
    return p;
}

maillonlig* ajoutermaillonlig(maillonlig** tete,maillonlig** q)
{
    maillonlig* p=NULL;
    p=(maillonlig*)malloc(sizeof(maillonlig));
    aff_prochain(p,NULL);
    aff_bas(p,NULL);
    if (*tete == NULL)
    {
       *tete = p;
    }
    else
    {
        aff_prochain(*q,p);
    }
    *q=p;
    return p;
}

void Rechligne(maillonlig** tete,int* lig,maillonlig** ptr,maillonlig** precedent,bool* existe)
{
    maillonlig* p=*tete;
    *ptr=NULL;
    *existe=false;
    while ((p!=NULL) && (ligne(p)!=*lig))
    {
        *precedent=p;
        p=prochain(p);
    }
    if (p!=NULL)
    {
        *existe=true;
        *ptr=p;
    }
}

void Rechvaleur(mailloncol** tete,int* val,mailloncol** ptr,mailloncol** precedent,bool* existe)
{
    mailloncol* p=*tete;
    *ptr=NULL;
    *existe=false;
    while ((p!=NULL) && (valeur(p)!=*val))
    {
        *precedent=p;
        p=next(p);
    }
    if (p!=NULL)
    {
        *existe=true;
        *ptr=p;
    }
}

void Rechcolonne(mailloncol** tete,int* col,mailloncol** ptr,mailloncol** precedent,bool* existe)
{
    mailloncol* p=*tete;
    *ptr=NULL;
    *existe=false;
    while ((p!=NULL) && (colonne(p)!=*col))
    {
        *precedent=p;
        p=next(p);
    }
    if (p!=NULL)
    {
        *existe=true;
        *ptr=p;
    }
}

/***************************************************************/                                     /**Structure sousbloc*/

int bloc(sousbloc* m)
{
    return m->bloc;
}

maillonlig* down(sousbloc* m)
{
    return m->down;
}

sousbloc* after(sousbloc* m)
{
    return m->after;
}

/***************************************************************/

void aff_bloc(sousbloc* m,int bloc)
{
    m->bloc=bloc;
}

void aff_after(sousbloc* p,sousbloc* q)
{
    p->after=q;
}

void aff_down(sousbloc* p,maillonlig* q)
{
    p->down=q;
}

/***************************************************************/

sousbloc* ajoutersousbloc(sousbloc** tete,sousbloc** q)
{
    sousbloc* p=NULL;
    p=(sousbloc*)malloc(sizeof(sousbloc));
    aff_after(p,NULL);
    aff_down(p,NULL);
    if (*tete == NULL)
    {
       *tete = p;
    }
    else
    {
        aff_after(*q,p);
    }
    *q=p;
    return p;
}

/***************************************************************/                                     /**Representation 02*/

void LECTMATRICE2(maillonlig** tete,int* maxl,int* maxc)
{
    int i=0,j=0,val=0;
    maillonlig* p=NULL;
    maillonlig* q=NULL;
    mailloncol* w=NULL;
    mailloncol* r=NULL;
    mailloncol* s=NULL; //tete des listes du bas
    *tete=NULL;
    do
    {
        printf("Entrez le nombre de lignes de votre matrice :");
        scanf("%d",maxl);
        if (*maxl<1)
        {
            printf("    Erreur, veuillez retaper votre nombre.\n");
        }
    }
    while (*maxl<1);
    do
    {
        printf("Entrez le nombre de colonnes de votre matrice :");
        scanf("%d",maxc);
        if (*maxc<1)
        {
            printf("    Erreur, veuillez retaper votre nombre.\n");
        }
    }
    while (*maxc<1);
    for (i=0;i<*maxl;i++)
    {
        p=ajoutermaillonlig(tete,&q); //Pour ne créer qu'un maillon par ligne i
        aff_ligne(p,i);
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&val);
            if (val!=0) //Nous ne stockons que les valeurs non nulles afin d'optimiser de l'espace mémoire
            {
                w=ajoutermailloncol(&s,&r);
                if (bas(p)==NULL)
                {
                    aff_bas(p,w); //chainage entre structure qui ne se fait qu'une fois par ligne
                }
                aff_colonne(w,j);
                aff_valeur(w,val);
            }
        }
        s=NULL; //pour créer une nouvelle sous liste de maillon colonne
    }
}

/***************************************************************/

void AfficheMatrice2(maillonlig** tete,int* begl,int* begc,int* maxl,int* maxc)
{
    int i,j;
    maillonlig* p=*tete;
    mailloncol* q=bas(p);
    for (i=*begl;i<*maxl;i++)
    {
        for (j=*begc;j<*maxc;j++)
        {
            if (q==NULL) //Le cas d'une matrice entiérement nulle
            {
                printf("0 |");
            }
            else
            {
                if (j==colonne(q))
                {
                    printf("%d |",valeur(q)); //Pour afficher les valeurs stockées
                    q=next(q);
                }
                else
                {
                    printf("0 |"); //si le maillon n'existe pas c'est que c'est un 0 non stocké
                }
            }
        }
        printf("\n");
        p=prochain(p);
        q=NULL;
        if (p!=NULL)
        {
            q=bas(p);
        }
    }
}

/***************************************************************/

void NonLogique2(maillonlig** tete,maillonlig** tete2,int* maxl,int* maxc)
{
    int i=0,j=0;
    maillonlig* p=*tete;
    mailloncol* q=bas(p);
    *tete2=NULL;
    maillonlig* p2=NULL;
    maillonlig* r=NULL; //simple queue
    mailloncol* q2=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL; //c'est une queue
    for (i=0;i<*maxl;i++)
    {
        p2=ajoutermaillonlig(tete2,&r); //Pour ne créer qu'un maillon par ligne i
        q2=NULL; //pour créer une nouvelle sous liste à chaque fois
        aff_ligne(p2,i);
        q=bas(p);
        for (j=0;j<*maxc;j++)
        {
            if ((q==NULL) || (colonne(q)!=j))
            {
                w=ajoutermailloncol(&q2,&s);
                if (bas(p2)==NULL)
                {
                    aff_bas(p2,w);
                }
                aff_colonne(w,j);
                aff_valeur(w,1);
            }
            else
            {
                if (colonne(q)==j)
                {
                    q=next(q);
                }
            }
        }
        p=prochain(p);
    }
}

/***************************************************************/

void Extraire2(maillonlig** tete,maillonlig** tete2,int* maxl,int* maxc,int* a,int* b,int* c,int* d)
{
    int numero;
    bool existe=false;
    maillonlig* p=*tete;
    maillonlig* z=NULL;
    mailloncol* q=bas(p);
    *tete2=NULL;
    maillonlig* p2=NULL;
    maillonlig* r=NULL; //simple queue
    mailloncol* q2=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL; //c'est une queue
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - EXTRACTION -\n\n");
    printf("Note : Veuillez entrer des indices positifs sachant que l'indice 0 existe.\n");
    do
    {
       printf("Entrez l'indice de la ligne de la premiere case :");
       scanf("%d",a);
       if ((-1>*a) || (*a>*maxl-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((-1>*a) || (*a>*maxl-1)); //a ne doit pas déborder des dimensions de la matrice
    do
    {
       printf("Entrez l'indice de la colonne de la premiere case :");
       scanf("%d",b);
       if ((-1>*b) || (*b>*maxc-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((-1>*b) || (*b>*maxc-1)); //b ne doit pas déborder des dimensions de la matrice
    do
    {
       printf("Entrez l'indice de la ligne de la derniere case :");
       scanf("%d",c);
       if ((*c<*a) || (*c>*maxl-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((*c<*a) || (*c>*maxl-1));  //On vérifie que la dernière case se trouve bien après la première case et ne déborde pas
    do
    {
       printf("Entrez l'indice de la colonne de la derniere case :");
       scanf("%d",d);
       if ((*d<*b) || (*d>*maxc-1))
       {
           printf("             Erreur, veuillez retaper votre indice !\n");
       }
    }
    while ((*d<*b) || (*d>*maxc-1)); //On vérifie que la dernière case se trouve bien après la première case et ne déborde pas
    p2=ajoutermaillonlig(tete2,&r); //création de la nouvelle liste
    numero=*a;
    if(a!=0)
    {
        p=NULL;
        Rechligne(tete,a,&p,&z,&existe);
        q=bas(p);
    }
    aff_ligne(p2,numero);
    while(p!=NULL)
    {
        if (((*a-1)<ligne(p))&&(ligne(p)<(*c+1)))
        {
            while(q!=NULL)
            {
                if (((*b-1)<colonne(q))&&(colonne(q)<(*d+1)))
                {
                    w=ajoutermailloncol(&q2,&s);
                    if (bas(p2)==NULL)
                    {
                        aff_bas(p2,w);
                    }
                    aff_colonne(w,colonne(q));
                    aff_valeur(w,valeur(q));
                }
                q=next(q);
            }
        }
        p=prochain(p);
        q=NULL;
        if (p!=NULL)
        {
            q=bas(p);
            p2=ajoutermaillonlig(tete2,&r);
            numero++;
            aff_ligne(p2,numero);
        }
    }
}

/***************************************************************/

void OuLogique2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3)
{
    maillonlig* p=*tete;
    mailloncol* q=bas(p);
    maillonlig* p2=*tete2;
    mailloncol* q2=bas(p2);
    *tete3=NULL;
    maillonlig* p3=*tete3;
    maillonlig* r=NULL; //simple queue
    mailloncol* q3=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL; //c'est une queue
    //Fin des déclarations
    while ((p!=NULL) && (p2!=NULL))
    {
        q2=bas(p2);
        q=bas(p);
        p3=ajoutermaillonlig(tete3,&r);
        aff_ligne(p3,ligne(p2)); //Que l'on prenne p2 ou p c'est pareil vu que même si une ligne est entierement nulle, le maillonlig existera en pointant du bas le NULL
        q3=NULL; //afin de créer une nouvelle sous chaine pour chaque ligne
        while ((q!=NULL) || (q2!=NULL))
        {
            w=ajoutermailloncol(&q3,&s);
            if (bas(p3)==NULL)
            {
                aff_bas(p3,w); //Pour chainer avec la ligne
            }
            aff_valeur(w,1);

            if ((q==NULL) && (q2!=NULL))
            {
                aff_colonne(w,colonne(q2));
                q2=next(q2);
            }
            else
            {
                if ((q!=NULL) && (q2==NULL))
                {
                    aff_colonne(w,colonne(q));
                    q=next(q);
                }
                else
                {
                    if (colonne(q)>colonne(q2))
                    {
                        aff_colonne(w,colonne(q2));
                        q2=next(q2);
                    }
                    else
                    {
                        if (colonne(q)<colonne(q2))
                        {
                            aff_colonne(w,colonne(q));
                            q=next(q);
                        }
                        else
                        {
                            if (colonne(q)==colonne(q2))
                            {
                                aff_colonne(w,colonne(q));
                                q=next(q);
                                q2=next(q2);
                            }
                        }
                    }
                }
            }
        }
        p=prochain(p);
        p2=prochain(p2);
    }
}

/***************************************************************/

void EtLogique2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3)
{
    maillonlig* p=*tete;
    mailloncol* q=bas(p);
    maillonlig* p2=*tete2;
    mailloncol* q2=bas(p2);
    *tete3=NULL;
    maillonlig* p3=*tete3;
    maillonlig* r=NULL; //simple queue
    mailloncol* q3=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL; //c'est une queue
    //Fin des déclarations
    while ((p!=NULL) && (p2!=NULL))
    {
        q2=bas(p2);
        q=bas(p);
        p3=ajoutermaillonlig(tete3,&r);
        aff_ligne(p3,ligne(p2)); //Que l'on prenne p2 ou p c'est pareil vu que même si une ligne est entierement nulle, le maillonlig existera en pointant du bas le NULL
        q3=NULL; //afin de créer une nouvelle sous chaine pour chaque ligne
        while ((q!=NULL) && (q2!=NULL))
        {
            if (colonne(q)>colonne(q2))
            {
                q2=next(q2);
            }
            else
            {
                if (colonne(q)<colonne(q2))
                {
                    q=next(q);
                }
                else
                {
                    if (colonne(q)==colonne(q2))
                    {
                        w=ajoutermailloncol(&q3,&s);
                        if (bas(p3)==NULL)
                        {
                            aff_bas(p3,w); //Pour chainer avec la ligne
                        }
                        aff_valeur(w,1);
                        aff_colonne(w,colonne(q));
                        q=next(q);
                        q2=next(q2);
                    }
                }
            }
        }
        p=prochain(p);
        p2=prochain(p2);
    }
}

/***************************************************************/

void OuxLogique2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3)
{
    maillonlig* p=*tete;
    mailloncol* q=bas(p);
    maillonlig* p2=*tete2;
    mailloncol* q2=bas(p2);
    *tete3=NULL;
    maillonlig* p3=*tete3;
    maillonlig* r=NULL; //simple queue
    mailloncol* q3=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL; //c'est une queue
    //Fin des déclarations
    while ((p!=NULL) && (p2!=NULL))
    {
        q2=bas(p2);
        q=bas(p);
        p3=ajoutermaillonlig(tete3,&r);
        aff_ligne(p3,ligne(p2)); //Que l'on prenne p2 ou p c'est pareil vu que même si une ligne est entierement nulle, le maillonlig existera en pointant du bas le NULL
        q3=NULL; //afin de créer une nouvelle sous chaine pour chaque ligne
        while ((q!=NULL) || (q2!=NULL)) //cas du 0 XOR 0 retiré ainsi
        {
            if ((q==NULL) && (q2!=NULL))
            {
                w=ajoutermailloncol(&q3,&s);
                if (bas(p3)==NULL)
                {
                    aff_bas(p3,w); //Pour chainer avec la ligne
                }
                aff_valeur(w,1);
                aff_colonne(w,colonne(q2));
                q2=next(q2);
            }
            else
            {
                if ((q!=NULL) && (q2==NULL))
                {
                    w=ajoutermailloncol(&q3,&s);
                    if (bas(p3)==NULL)
                    {
                        aff_bas(p3,w); //Pour chainer avec la ligne
                    }
                    aff_valeur(w,1);
                    aff_colonne(w,colonne(q));
                    q=next(q);
                }
                else
                {
                    if (colonne(q)>colonne(q2))
                    {
                        w=ajoutermailloncol(&q3,&s);
                        if (bas(p3)==NULL)
                        {
                            aff_bas(p3,w); //Pour chainer avec la ligne
                        }
                        aff_valeur(w,1);
                        aff_colonne(w,colonne(q2));
                        q2=next(q2);
                    }
                    else
                    {
                        if (colonne(q)<colonne(q2))
                        {
                            w=ajoutermailloncol(&q3,&s);
                            if (bas(p3)==NULL)
                            {
                                aff_bas(p3,w); //Pour chainer avec la ligne
                            }
                            aff_valeur(w,1);
                            aff_colonne(w,colonne(q));
                            q=next(q);
                        }
                        else
                        {
                            if (colonne(q)==colonne(q2)) //cas du 1 XOR 1 retiré ainsi
                            {
                                q=next(q);
                                q2=next(q2);
                            }
                        }
                    }
                }
            }
        }
        p=prochain(p);
        p2=prochain(p2);
    }
}

/***************************************************************/

void Addition2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3)
{
    maillonlig* p=*tete;
    mailloncol* q=bas(p);
    maillonlig* p2=*tete2;
    mailloncol* q2=bas(p2);
    *tete3=NULL;
    maillonlig* p3=*tete3;
    maillonlig* r=NULL; //simple queue
    mailloncol* q3=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL; //c'est une queue
    //Fin des déclarations
    while ((p!=NULL) && (p2!=NULL))
    {
        q2=bas(p2);
        q=bas(p);
        p3=ajoutermaillonlig(tete3,&r);
        aff_ligne(p3,ligne(p2)); //Que l'on prenne p2 ou p c'est pareil vu que même si une ligne est entierement nulle, le maillonlig existera en pointant du bas le NULL
        q3=NULL; //afin de créer une nouvelle sous chaine pour chaque ligne
        while ((q!=NULL) || (q2!=NULL))
        {
            if ((q==NULL) && (q2!=NULL))
            {
                w=ajoutermailloncol(&q3,&s);
                if (bas(p3)==NULL)
                {
                    aff_bas(p3,w); //Pour chainer avec la ligne
                }
                aff_valeur(w,valeur(q2));
                aff_colonne(w,colonne(q2));
                q2=next(q2);
            }
            else
            {
                if ((q!=NULL) && (q2==NULL))
                {
                    w=ajoutermailloncol(&q3,&s);
                    if (bas(p3)==NULL)
                    {
                        aff_bas(p3,w); //Pour chainer avec la ligne
                    }
                    aff_valeur(w,valeur(q));
                    aff_colonne(w,colonne(q));
                    q=next(q);
                }
                else
                {
                    if (colonne(q)>colonne(q2))
                    {
                        w=ajoutermailloncol(&q3,&s);
                        if (bas(p3)==NULL)
                        {
                            aff_bas(p3,w); //Pour chainer avec la ligne
                        }
                        aff_valeur(w,valeur(q2));
                        aff_colonne(w,colonne(q2));
                        q2=next(q2);
                    }
                    else
                    {
                        if (colonne(q)<colonne(q2))
                        {
                            w=ajoutermailloncol(&q3,&s);
                            if (bas(p3)==NULL)
                            {
                                aff_bas(p3,w); //Pour chainer avec la ligne
                            }
                            aff_valeur(w,valeur(q));
                            aff_colonne(w,colonne(q));
                            q=next(q);
                        }
                        else
                        {
                            if (colonne(q)==colonne(q2))
                            {
                                if (valeur(q2)+valeur(q)!=0)
                                {
                                    w=ajoutermailloncol(&q3,&s);
                                    if (bas(p3)==NULL)
                                    {
                                        aff_bas(p3,w); //Pour chainer avec la ligne
                                    }
                                aff_valeur(w,valeur(q2)+valeur(q));
                                aff_colonne(w,colonne(q)); // q ou q2 c'est pareil c'est les mêmes
                                }
                                q=next(q);
                                q2=next(q2);
                            }
                        }
                    }
                }
            }
        }
        p=prochain(p);
        p2=prochain(p2);
    }
}

/***************************************************************/

void Transposee2(maillonlig** tete,maillonlig** tete2,int* maxc)
{
    int i=0,j=0;
    bool existe=false;

    maillonlig* p=*tete;
    maillonlig* k=NULL; //maillon précédent des recherches
    mailloncol* q=bas(p);

    *tete2=NULL;
    maillonlig* p2=NULL;
    maillonlig* r=NULL; //simple queue
    mailloncol* q2=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL; //c'est une queue
    //fin des déclarations de variables
    for (i=0;i<*maxc;i++) //on prend le nombre de colonnes de la matrice principale
    {
        p2=ajoutermaillonlig(tete2,&r); //Création des maillons lignes de la transposée avec des lignes vides (NULL)
        aff_ligne(p2,i);
    }
    //Maintenant, nous allons simplement créer les maillons de la transposée tout en inversant les indices
    while (p!=NULL)
    {
        q=bas(p);
        while (q!=NULL)
        {
            j=colonne(q);
            Rechligne(tete2,&j,&p2,&k,&existe); //On va à la bonne ligne d'abord, k ne sert à rien dans cette solution et existe non plus étant donné que nous sommes sur que la valeur existe car elle a été ajouté juste en haut
            w=ajoutermailloncol(&q2,&s);
            if (bas(p2)==NULL)
            {
                aff_bas(p2,w); //Pour chainer avec la ligne si ce n'est pas encore fait
            }
            else //vu que nous ne créeons pas la liste dans l'ordre, la tête est mise à NULL à chaque fin de boucle et donc, si le bas(p)!=NULL,nous devrons chainer w au dernier maillon ajouter
            {
                k=bas(p2); //pointeur k réutilisé pour retrouver le dernier maillon ajouter
                while(next(k)!=NULL)
                {
                 k=next(k);
                }
                aff_bas(k,w); //k pointe vers le dernier maillon ajouté à cette ligne
            }
            aff_valeur(w,valeur(q));
            aff_colonne(w,ligne(p));
            q=next(q);
            q2=NULL; //la tete est mise à NULL de nouveau car nous ne créeons pas notre liste dans l'ordre
        }
        p=prochain(p);
    }

}

/***************************************************************/

void Multiplication2(maillonlig** tete,maillonlig** tete2,maillonlig** tete3,int* maxl,int* maxc,int*a)
{
    int choix=0,val=0,i=0,j=0,somme=0,compteur=0;

    maillonlig* p=*tete;
    mailloncol* q=bas(p);

    *tete2=NULL;
    maillonlig* p2=NULL;
    maillonlig* r2=NULL; //simple queue
    mailloncol* q2=NULL;
    mailloncol* w2=NULL;
    mailloncol* s2=NULL; //c'est une queue

    maillonlig* newtete=NULL; //ça sera la tête de la transposée
    *tete3=NULL; //tete de la matrice résultante
    maillonlig* p3=NULL;
    maillonlig* r3=NULL; //simple queue
    mailloncol* q3=NULL;
    mailloncol* w3=NULL;
    mailloncol* s3=NULL; //c'est une queue

    /*Afin de multiplier nos matrices, ces dernières doivent être compatibles et c'est la raison pour laquelle,
    la liste de la seconde matrice sera créee dans ce module tout en respectant la régle (en fixant le nombre de lignes*/
    while ((choix>2) || (choix<1))
    {
        printf("\n\n\n\n\n");
        printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - MULTIPLICATION -\n\n");
        printf("    Que voulez vous faire ?\n\n");
        printf("    1. Multiplier votre matrice par un vecteur.\n");
        printf("    2. Multiplier votre matrice par une autre matrice.\n\n");
        printf("    Je choisis : ");
        scanf("%d",&choix);
        if ((choix>2) || (choix<1))
        {
            system("cls");
        }
    }
    if (choix==1)
    {
        *a=1;
        printf("\nVotre matrice et votre vecteur doivent etre compatibles alors le nombre de lignes de votre vecteur est fixe a : %d\n",*maxc);
    }
    else
    {
       printf("\nPour que les 2 matrices soient compatibles, le nombre de lignes de votre seconde matrice sera fixe a : %d\n",*maxc);
       printf("Entrez le nombre de colonnes de votre seconde matrice :");
       scanf("%d",a);
    }
    for (i=0;i<*maxc;i++)
    {
        p2=ajoutermaillonlig(tete2,&q2);
        aff_ligne(p2,i);
        for (j=0;j<*a;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&val);
            if (val!=0)
            {
                w2=ajoutermailloncol(&s2,&r2);
                if (bas(p2)==NULL)
                {
                    aff_bas(p2,w2);
                }
                aff_colonne(w2,j);
                aff_valeur(w2,val);
            }
        }
        s2=NULL; //pour créer une nouvelle sous liste de maillon colonne
    }
    Transposee2(tete2,&newtete,a); //Afin d'éviter de parcourir la 2nd liste plusieurs fois, on trie cette dernière en effectuant la transposée
    //Le produit :
    while (p!=NULL)
    {
        p3=ajoutermaillonlig(tete3,&r3); //création du maillon de la ligne
        aff_ligne(p3,ligne(p));
        q3=NULL; //on initialise la tête des maillons colonnes
        compteur=0;
        p2=newtete;
        while (p2!=NULL)
        {
            q=bas(p);
            q2=bas(p2);
            somme=0;
            while ((q!=NULL) && (q2!=NULL))
            {//
                if (colonne(q)<colonne(q2))
                {
                    q=next(q);
                }
                else
                {
                    if (colonne(q)>colonne(q2))
                    {
                        q2=next(q2);
                    }
                    else
                    {
                        if (colonne(q)==colonne(q2))
                        {
                            somme=somme+valeur(q2)*valeur(q);
                            q2=next(q2);
                            q=next(q);
                        }
                    }
                }
            }//
            if (somme!=0)
            {
                w3=ajoutermailloncol(&q3,&s3);
                if (bas(p3)==NULL)
                {
                    aff_bas(p3,w3);
                }
                aff_colonne(w3,compteur);
                aff_valeur(w3,somme);
            }
            compteur++;
            p2=prochain(p2);
        }
        p=prochain(p);
    }
}

/***************************************************************/

void MODIFICATION2(maillonlig** tete,int* maxl,int* maxc)
{
    int a=0,b=0,begl=0,begc=0,valeur=0;
    bool existe=false;

    maillon* p=NULL;
    maillon* q=NULL;

    //Fin des déclarations de variables
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - MODIFICATION -\n\n");
    printf("Oops, suite a une erreur de saisie ou un oubli, vous desirez changer les valeurs de votre matrice.\n");
    printf("Rappel des valeurs entrees:\n");
    AfficheMatrice(tete,&begl,&begc,maxl,maxc);
    printf("\n");
    do
    {
        a=0;
        printf("Entrez la ligne de la case erronee :");
        scanf("%d",&a);
        if (a>*maxl || a<0)
        {
            printf("    Erreur, veuillez entrer de nouveau votre indice.\n");
        }
    }
    while (a>*maxl || a<0);
    do
    {
        b=0;
        printf("Entrez la colonne de la case erronee :");
        scanf("%d",&b);
        if (b>*maxc || b<0)
        {
            printf("    Erreur, veuillez entrer de nouveau votre indice.\n");
        }
    }
    while (b>*maxc || b<0);
    printf("Entrez maintenant la valeur qui sera inseree a la case [%d,%d] de votre matrice :",a,b);
    scanf("%d",&valeur);
    //Les modifications peuvent etre faites soient par une suppression de maillon, une insertion de maillon ou une simple affectation au champs val
    //Recherche
    if (valeur==0) //0 devient 0 ou bien valeur devient 0 (cas de la suppression car on ne stocke pas les valeurs nulles)
    {
        if (existe==true) //Le maillon existait et donc il avait une valeur non nulle, il faut maintenant le supprimer !
        {
            /////////////
        }
        //Si existe==false c'est que le maillon de base contenait une valeur nulle et donc, il n'avait pas été crée au tout début, on ne fait rien
    }
    else // 0 devient valeur ou valeur devient valeur (insertion de maillon ou juste une affectation)
    {
        if (existe==true) //le maillon existe déjà alors nous ne ferons qu'une simple affectation
        {
            ///////////////
        }
        else //Le maillon n'existe pas, nous devons l'inserer dans cette liste
        {
            //////////
        }
    }
}

/***************************************************************/

void DIVISION2(maillonlig** tete,int* maxl,int* maxc)
{
    int i=0,j=0,k=0,a=0,b=0,nb=0,begl=0,begc=0;
    maillonlig* p=*tete;
    mailloncol* q=bas(p);

    sousbloc* sb=NULL; //La tete de la grande liste
    sousbloc* psb=NULL;
    sousbloc* qsb=NULL; //c'est une queue

    maillonlig* tete2=NULL;
    maillonlig* p2=NULL;
    maillonlig* r2=NULL; //c'est une queue

    mailloncol* q2=NULL;
    mailloncol* w2=NULL;
    mailloncol* s2=NULL; //c'est une queue
    mailloncol* k2=NULL;

    //Fin des déclarations de variables
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - DIVISION -\n\n");
    do
    {
        do
        {
           printf("Entrez le nombre de lignes des sous blocs voulus :");
           scanf("%d",&a);
           if ((a<0) || (a>*maxl+1))
           {
               printf("             Erreur, veuillez retaper votre indice !\n");
           }
        }
        while ((a<0) || (a>*maxl+1));
        do
        {
           printf("Entrez le nombre de colonnes des sous blocs voulus :");
           scanf("%d",&b);
           if ((b<0) || (b>*maxl+1))
           {
               printf("             Erreur, veuillez retaper votre indice !\n");
           }
        }
        while ((b<0) || (b>*maxl+1));
        if ((*maxl%a!=0)&&(*maxc%b!=0))
        {
            printf("\nNous ne pouvons malheureusement pas diviser votre matrice en sous blocs de %d lignes et %d colonnes.\nVeuillez entrer de nouvelles dimensions !\n",a,b);
        }
    }
    while ((*maxl%a!=0)&&(*maxc%b!=0));
    //La division en sous blocs de tailles égales sera faite à l'aide de la structure sous blocs qui nous aidera ranger les sous blocs créés
    nb=((*maxc)*(*maxl))/((a)*(b)); //Calcul du nombre de sous blocs
    //Nous allons maintenant préparer le corps de la liste de listes de listes (blocs - lignes - colonnes) qui va contenir notre solution
    for (j=1;j<nb+1;j++)
    {
        psb=ajoutersousbloc(&sb,&qsb);
        aff_bloc(psb,j); //Numéro du bloc (le comptage des blocs se fait de gauche à droite et du haut vers le bas)
        tete2=NULL;
        for (i=0;i<a;i++) //On munit chaque sous blocs du nombre de maillon lignes demandés
        {
            p2=ajoutermaillonlig(&tete2,&r2);
            if (down(psb)==NULL)
            {
                aff_down(psb,p2);
            }
            aff_ligne(p2,i);
        }
    }
    /* Il est à noter que les indices attribués aux maillons sousblocs sont facultatifs étant donné que pour accéder à un maillon de cette structure, nous ne ferons qu'un simple petit parcours*/
    /*Maintenant que le corps de la liste est prêt, nous allons compléter cette liste avec les bon maillons colonnes et ce, en ne parcourant la liste principale qu'une seule fois à l'aide de cette
     boucle séquentielle qui affecte à chaque case (i,j) de la matrice, le numéro de blocs dans lequel doit figurer cette case. (et dans l'ordre bien évidemment !)
     On a : Pour une ligne de la matrice, il y a ((*maxc)/b) blocs (b étant le nombre de colonnes des sous matrices) et dans chaque sous blocs, il y a b colonnes.
     Un bloc est aussi constitué de a lignes.*/
    int c=0,d=a,e=1,f=((*maxc)/b),g=0,h=b,save=0,test=0;
    do
    {
        save=c; //Elle ne permettra de changer de maillonligne
        for (i=c;i<d;i++) //les lignes
        {
            g=0;
            h=b;
            if (save!=i) //Boucle pour sauter de ligne
            {
                p=prochain(p);
                if (p!=NULL)
                {
                    q=bas(p);
                }
                save++;
            }
            for (k=e;k<f+1;k++) //les sous blocs
            {
                for (j=g;j<h;j++) //les colonnes
                {
                    if (q!=NULL)
                    {
                    if (colonne(q)==j)
                    {
                        //Dans ce cas là, on se dirige vers le bon sous bloc, la bonne ligne et on y insére le maillon tout en vérifiant que les valeurs de colonnes sont justes
                        psb=sb; //On se dirige vers la tête de la grande structure
                        while (k!=bloc(psb)) //On cherche le bon bloc
                        {
                            psb=after(psb);
                        }
                        p2=down(psb);
                        test=i; //réduction de l'indice d'abord si nécessaire
                        while ((test>a) || (test==a)) //On corrige les valeurs des colonnes pour qu'elles correspondent au mini blocs
                        {
                            test=test-a;
                        }
                        while (test!=ligne(p2)) //On cherche la bonne ligne
                        {
                            p2=prochain(p2);
                        }
                        w2=ajoutermailloncol(&q2,&s2);
                        if (bas(p2)==NULL) //On effectue le bon chainage
                        {
                            aff_bas(p2,w2);
                        }
                        else //On cherche le dernier maillon ajouté dans cette ligne
                        {
                            k2=bas(p2);
                            while (next(k2)!=NULL)
                            {
                                k2=next(k2);
                            }
                            aff_bas(k2,w2);
                        }
                        test=colonne(q);
                        while ((test>b) || (test==b)) //On corrige les valeurs des colonnes pour qu'elles correspondent au mini blocs
                        {
                            test=test-b;
                        }
                        //Et enfin, on affecte
                        aff_colonne(w2,test);
                        aff_valeur(w2,valeur(q));
                        q=next(q);
                        q2=NULL; //Vu que dans une même ligne, nous altérons entre 1 et ((*maxc)/b) blocs alors on réinistialise la tête à chaque fois
                    }
                    }
                }
                g=h;
                h=h+b;
            }
        }
    p=prochain(p);
    if (p!=NULL)
    {
        q=bas(p);
    }
    c=d;
    d=d+a;
    e=f+1;
    f=((*maxc)/b)+f;
    }
    while (c!=*maxl);
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 01 - DIVISION -\n\n");
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\nVoici vos sous-blocs :\n");
    psb=sb; //On retourne à la tête
    for (i=1;i<nb+1;i++)
    {
        p2=down(psb);
        printf("Sous bloc n %d :\n",i);
        AfficheMatrice2(&p2,&begl,&begc,&a,&b);
        psb=after(psb);
        printf("\n");
    }
}

/***************************************************************/                                     /**Interaction avec l'utilisateur*/

void AFFICHE2(maillonlig** tete,int* maxl,int* maxc)
{
    int begl=0,begc=0;
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void EXTRAIRE2(maillonlig** tete,int* maxl,int* maxc)
{
    int a,b,c,d,begl=0,begc=0;
    maillonlig* tete2;
    Extraire2(tete,&tete2,maxl,maxc,&a,&b,&c,&d);
    c=c+1;
    d=d+1;
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - EXTRACTION -\n\n");
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\n");
    printf("Et voici votre sous matrice composee de %d lignes et %d colonnes :\n",c-a,d-b);
    AfficheMatrice2(&tete2,&a,&b,&c,&d);
}

/***************************************************************/

void NONLOGIQUE2(maillonlig** tete,int* maxl,int* maxc)
{
    int begl=0,begc=0;
    maillonlig* tete2=NULL;
    NonLogique2(tete,&tete2,maxl,maxc);
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - NON LOGIQUE -\n\n");
    printf("Voici votre matrice :\n");
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\nEt en appliquant le NON logique, on obtient :\n");
    AfficheMatrice2(&tete2,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void OULOGIQUE2(maillonlig** tete,int* maxl,int* maxc)
{
    int i,j,val,begl=0,begc=0;
    maillonlig* p2=NULL;
    maillonlig* q2=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL;
    mailloncol* r=NULL;
    maillonlig* tete2=NULL;
    maillonlig* tete3=NULL;
    printf("Afin d'effectuer cette operation logique, vos matrices doivent etre de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        p2=ajoutermaillonlig(&tete2,&q2); //Pour ne créer qu'un maillon par ligne i
        aff_ligne(p2,i);
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&val);
            if (val!=0) //Nous ne stockons que les valeurs non nulles afin d'optimiser de l'espace mémoire
            {
                w=ajoutermailloncol(&s,&r);
                if (bas(p2)==NULL)
                {
                    aff_bas(p2,w); //chainage entre structure qui ne se fait qu'une fois par ligne
                }
                aff_colonne(w,j);
                aff_valeur(w,val);
            }
        }
        s=NULL; //pour créer une nouvelle sous liste de maillon colonne
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - OU LOGIQUE -\n\n");
    OuLogique2(tete,&tete2,&tete3);
    printf("La matrice A :\n");
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\nLa matrice B :\n");
    AfficheMatrice2(&tete2,&begl,&begc,maxl,maxc);
    printf("\nA OU B =\n");
    AfficheMatrice2(&tete3,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void ETLOGIQUE2(maillonlig** tete,int* maxl,int* maxc)
{
    int i,j,val,begl=0,begc=0;
    maillonlig* p2=NULL;
    maillonlig* q2=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL;
    mailloncol* r=NULL;
    maillonlig* tete2=NULL;
    maillonlig* tete3=NULL;
    printf("Afin d'effectuer cette operation logique, vos matrices doivent etre de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        p2=ajoutermaillonlig(&tete2,&q2); //Pour ne créer qu'un maillon par ligne i
        aff_ligne(p2,i);
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&val);
            if (val!=0) //Nous ne stockons que les valeurs non nulles afin d'optimiser de l'espace mémoire
            {
                w=ajoutermailloncol(&s,&r);
                if (bas(p2)==NULL)
                {
                    aff_bas(p2,w); //chainage entre structure qui ne se fait qu'une fois par ligne
                }
                aff_colonne(w,j);
                aff_valeur(w,val);
            }
        }
        s=NULL; //pour créer une nouvelle sous liste de maillon colonne
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - ET LOGIQUE -\n\n");
    EtLogique2(tete,&tete2,&tete3);
    printf("La matrice A :\n");
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\nLa matrice B :\n");
    AfficheMatrice2(&tete2,&begl,&begc,maxl,maxc);
    printf("\nA ET B =\n");
    AfficheMatrice2(&tete3,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void OUXLOGIQUE2(maillonlig** tete,int* maxl,int* maxc)
{
    int i,j,val,begl=0,begc=0;
    maillonlig* p2=NULL;
    maillonlig* q2=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL;
    mailloncol* r=NULL;
    maillonlig* tete2=NULL;
    maillonlig* tete3=NULL;
    printf("Afin d'effectuer cette operation logique, vos matrices doivent etre de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        p2=ajoutermaillonlig(&tete2,&q2); //Pour ne créer qu'un maillon par ligne i
        aff_ligne(p2,i);
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&val);
            if (val!=0) //Nous ne stockons que les valeurs non nulles afin d'optimiser de l'espace mémoire
            {
                w=(&s,&r);
                if (bas(p2)==NULL)
                {
                    aff_bas(p2,w); //chainage entre structure qui ne se fait qu'une fois par ligne
                }
                aff_colonne(w,j);
                aff_valeur(w,val);
            }
        }
        s=NULL; //pour créer une nouvelle sous liste de maillon colonne
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - OU EXCLUSIF -\n\n");
    OuxLogique2(tete,&tete2,&tete3);
    printf("La matrice A :\n");
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\nLa matrice B :\n");
    AfficheMatrice2(&tete2,&begl,&begc,maxl,maxc);
    printf("\nA OUX B =\n");
    AfficheMatrice2(&tete3,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void ADDITION2(maillonlig** tete,maillonlig** tete2,int* maxl,int* maxc)
{
    int i,j,val,begl=0,begc=0;
    maillonlig* p2=NULL;
    maillonlig* q2=NULL;
    mailloncol* w=NULL;
    mailloncol* s=NULL;
    mailloncol* r=NULL;
    *tete2=NULL;
    maillonlig* tete3=NULL;
    printf("Afin d'effectuer cette operation logique, vos matrices doivent etre de tailles egales :\n");
    printf("Le nombre de lignes de votre 2nd matrice sera %d.\n",*maxl);
    printf("Le nombre de colonnes de votre 2nd matrice sera %d.\n",*maxc);
    for (i=0;i<*maxl;i++)
    {
        p2=ajoutermaillonlig(&tete3,&q2); //Pour ne créer qu'un maillon par ligne i
        aff_ligne(p2,i);
        for (j=0;j<*maxc;j++)
        {
            printf("T[%d,%d]=",i,j);
            scanf("%d",&val);
            if (val!=0) //Nous ne stockons que les valeurs non nulles afin d'optimiser de l'espace mémoire
            {
                w=ajoutermailloncol(&s,&r);
                if (bas(p2)==NULL)
                {
                    aff_bas(p2,w); //chainage entre structure qui ne se fait qu'une fois par ligne
                }
                aff_colonne(w,j);
                aff_valeur(w,val);
            }
        }
        s=NULL; //pour créer une nouvelle sous liste de maillon colonne
    }
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - OU EXCLUSIF -\n\n");
    Addition2(tete,&tete3,tete2);
    printf("La matrice A :\n");
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\nLa matrice B :\n");
    AfficheMatrice2(&tete3,&begl,&begc,maxl,maxc);
    printf("\nA + B =\n");
    AfficheMatrice2(tete2,&begl,&begc,maxl,maxc);
}

/***************************************************************/

void TRANSPOSEE2(maillonlig** tete,int* maxl,int* maxc)
{
    maillonlig* tete2=NULL;
    int begl=0,begc=0;
    printf("Voici votre matrice composee de %d lignes et %d colonnes :\n",*maxl,*maxc);
    Transposee2(tete,&tete2,maxc);
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    printf("\nEt voici la transposee de votre matrice est :\n");
    AfficheMatrice2(&tete2,&begl,&begc,maxc,maxl);
}

/***************************************************************/

void MULTIPLICATION2(maillonlig** tete,int* maxl,int* maxc)
{
    int a=0,begl=0,begc=0;
    maillonlig* tete2=NULL;
    maillonlig* tete3=NULL;
    Multiplication2(tete,&tete2,&tete3,maxl,maxc,&a);
    system("cls");
    printf("\n\n\n\n\n");
    printf("                          LES MATRICES CREUSES : REPRESENTATION N 02 - MULTIPLICATION -\n\n");
    printf("La matrice A :\n");
    AfficheMatrice2(tete,&begl,&begc,maxl,maxc);
    if (a==1)
    {
        printf("\nLe vecteur B :\n");
    }
    else
    {
        printf("\nLa matrice B :\n");
    }
    AfficheMatrice2(&tete2,&begl,&begc,maxc,&a);
    printf("\nA x B =\n");
    AfficheMatrice2(&tete3,&begl,&begc,maxl,&a);
}
