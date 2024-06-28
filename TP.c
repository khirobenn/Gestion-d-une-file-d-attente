/*
    Ecole nationale Supérieure d'Informatique

    TP1 ALSDD  : Gestion des files d'attentes  |   PROF : BOUDI Abderrahmane

    Réalisé par : BENMEZIANE Khireddine & KHARROUB Ouail | Niveau : 1CP | Groupe : 01 | Section : A   

    Année scolaire : 2022/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "BIBLIO\LLCTP.h"
#include "BIBLIO\conio2.h"
#include "BIBLIO\bib.h"

/*--------------------------PROGRAMME PRINCIPAL------------------------------*/

int main()
{
    ptr queue = NULL; // Utilisée comme queue pour insérer les clients par ordre des numéros de tickets.
    ptr *guichet , *queuetick; /* 'guichet' c'est pour créer un tableau dynamique des têtes des guichets ,
                                'queutick' pour les queues des guichets pour insérer les clients rapidement sans parcourir les listes 
                                                à chaque fois. */
    int tick=1; // Variable utilisée pour numéro de ticket qui commence par 1 et s'incrémente à chaque insertion d'un nouveau client.
    int en=0; // Cette variable est utilisée comme boolean , pour ne pas effectuer d'autre opération avant d'ajouter un client au moins (avec l'ajout d'un client elle s'incrémente à 1).
    int nbrguichets; // Utilisée pour le nombre de guichets.
    int option; // Utilisée pour le choix du Menu Principal.
    char guich; // Lettre du guichet qui traîtra le client.
    char c;
    int i=0; // Utilisée dans les boucle 'for' .
    int op; // Utilisée dans le MenuB. l
    int display; // Variable pour les cordonnées.

    affichage(&display);
    att(display);
    gotoxy(11,display+1);
    textcolor(4);
    printf("Remarque : Les guichets sont des lettres majuscules ( A , B , .. ) c'est selon le nombre choisi.\n");
    do{
        gotoxy(34,display+3);
        textcolor(15);
        ShowConsoleCursor(true);
        printf("Veuillez saisir le nombre de guichets disponible : ");
        scanf("%d",&nbrguichets);
        if(nbrguichets >26 || nbrguichets < 1)
        {
            clrscr();
            affichage(&display);
            textcolor(4);
            gotoxy(11,display+1);
            printf("Remarque : Les guichets sont des lettres majuscules ( A , B , .. ) c'est selon le nombre choisi.\n");
            gotoxy(39,display + 5);
            printf("Veuillez saisir un nombre entre 1 et 26 !");
        }
    }while(nbrguichets >26 || nbrguichets < 1);

    clrscr();
    contor();

    guichet = malloc(sizeof(ptr)*(nbrguichets+1));
    queuetick = malloc(sizeof(ptr)*nbrguichets);

    for(i=0;i<nbrguichets;i++)
    {
        guichet[i]=NULL;
        queuetick[i]=NULL;
    }
    guichet[nbrguichets] = NULL;

    menuPr:
    menuPrincipal(&option);

    if(option == 1 || option == 5)
        {
            en =1;
        }

    while(en!=1)    {   
        clrscr();
        contor();
        gotoxy(26,20);
        textcolor(4);
        printf("Veuillez ajouter des clients avant d'effectuer d'autre op%crations!",130);
        textcolor(15);
        menuPrincipal(&option);
        if(option ==1 || option ==5)
        {
            en =1;
        }
    }

    switch(option)
    {    
        case 1 :
            ajoutClient(nbrguichets , guichet , queuetick, &tick , &queue);
            goto menuPr;

        /*-----------------------------*/
        case 2:
            clrscr();
            contor();
            ShowConsoleCursor(true);
            etiq: 
            gotoxy(46,15);
            printf("Veuillez choisir un guichet : ");
            scanf(" %c",&guich);
            c=guich;
            guich -= 65;
            if(guich >= nbrguichets || guich < 0)
            {
                clrscr();
                contor();
                textcolor(4);
                gotoxy(40,17);
                printf("Veuillez saisir une lettre entre A et %c.",nbrguichets+64);
                textcolor(15);
                goto etiq;
            }
            clrscr();
            contor();
            menuB(&guichet[guich],&op,guichet,&guichet[nbrguichets],c,&en);
            clrscr();
            contor();
            goto menuPr;



        /*-----------------------------*/

        case 3:
            clrscr();
            contor();
            afficheliste(guichet[nbrguichets]);
            goto menuPr;
    
        /*-----------------------------*/

        case 4:
            clrscr();
            contor();
            menuD(guichet[nbrguichets],&tick,queuetick,guichet,nbrguichets);
            clrscr();
            contor();
            goto menuPr;

        /*-----------------------------*/

        default : 
            quit:
            LibLLC(guichet[nbrguichets]);
            free(guichet);
            free(queuetick);
            exit(1);
    }   
    return 0; 
}

/*-------------------------------- FIN -----------------------------------------*/