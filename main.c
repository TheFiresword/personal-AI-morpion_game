#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define BONUS1 10
#define BONUS2 30
#define BONUS3 120

typedef struct
{
    int ligne; int colonne;
}position;



typedef char echiquier[3][3]; // Etant un tableau il est aussi un pointeur



int fonction_gagner(echiquier f_echiquier,char symboleJ,char symboleia);
void afficheGrille(echiquier f_echiquier);
void videurBuffer();
char symboleJoueur();
int evalue_adv(echiquier f_echiquier, char symbole);
void deplacementJoueur(echiquier  f_echiquier,char symbole);
int fonctionGagner(echiquier f_echiquier,char symbole);
int* calcul_prof1(echiquier  f_echiquier,char symbole_IA);
char symboleIA(char symboleJ);
int grilleremplie(echiquier f_echiquier);
void annulerDeplacement(echiquier f_echiquier, position f_position);
void initialisateur(echiquier f_echiquier);
void calcul_prof2(echiquier f_echiquier,char symbole_IA);



void afficheGrille(echiquier f_echiquier)// Affiche la grille
{
    int i=0;
    int j=0;
    char piece;

   for(j=0;j<3;j++)
   {
    printf("\t");
    printf("%d\t",j+1);
    for(i=0;i<4;i++)
    {
       printf("|");

       if(f_echiquier[j][i]!='\0' && i<3)
       {
           piece=(f_echiquier)[j][i];
           if(piece=='X')
           {
               printf("X");
           }
           else if(piece=='O')
           {
               printf("O");
           }
       }
       printf("\t");
    }
    printf("\n");

    printf("\t\t");
    for(i=0;i<3;i++)
    {
        printf("--------");
    }
    printf("\n");
   }


   printf("\t\t");
   for(i=1;i<4;i++)
   {
       printf("    %d\t",i);
   }
   printf("\n");
}

void videurBuffer()// Vide le buffer
{
     int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }

}

 char symboleJoueur()// Prend le symbole du joueur
 {
    char symbole;
     do
     {
     printf("Cher joueur, veuillez choisir votre symbole: 'X' ou 'O'\n");
      symbole=getchar();
      videurBuffer();
     }while(symbole!='X' && symbole!='O');

     return symbole;
 }




 int evalue_adv(echiquier f_echiquier, char symbole)//Positif si l'oppose du symbole gagne
{
    int i=0,j=0;
    int somme=0;
    int compteurligne[2]={0};
    int compteurcolon[2]={0};
    int compteurDiP[2]={0};
    int compteurDiS[2]={0};

    char opp_symbole;
    opp_symbole=symboleIA(symbole);


     // +10 si on a un symbole oppose seul sur une ligne une colonne ou une diagonale
     //+30 si on a 2 qui sont seuls
     //+100 si ils gagnent
        for(i=0;i<3;i++)
      {

        if(f_echiquier[i][j]==symbole)
            {
               compteurligne[0]++;
            }
        if(f_echiquier[i][j+1]==symbole)
        {
            compteurligne[0]++;
        }
        if(f_echiquier[i][j+2]==symbole)
        {
            compteurligne[0]++;
        }

        if(f_echiquier[i][j]==opp_symbole)
            {
               compteurligne[1]++;
            }

            if(f_echiquier[i][j+1]==opp_symbole)
            {
                compteurligne[1]++;
            }
             if(f_echiquier[i][j+2]==opp_symbole)
            {
                compteurligne[1]++;
            }



             if(compteurligne[0]==0 && compteurligne[1]>=1)
            {

                if(compteurligne[1]==2)
                {
                    somme+=BONUS2;
                }
                 else if(compteurligne[1]==3)
                {
                   somme+=BONUS3;
                }
                else
                    somme+=BONUS1;
            }
            else if(compteurligne[1]==0 && compteurligne[0]>=1)
            {
               if(compteurligne[0]==2)
                {
                    somme-=BONUS2;
                }
                else if(compteurligne[0]==3)
                {
                   somme-=BONUS3;
                }
                else
                    somme-=BONUS1;
            }

            compteurligne[0]=0; compteurligne[1]=0;
      }

        i=0;
        for(j=0;j<3;j++)
        {
           if(f_echiquier[i][j]==symbole)
            {
               compteurcolon[0]++;
            }

            if(f_echiquier[i+1][j]==symbole)
            {
                compteurcolon[0]++;
            }
            if(f_echiquier[i+2][j]==symbole)
            {
                compteurcolon[0]++;
            }


           if(f_echiquier[i][j]==opp_symbole)
            {
               compteurcolon[1]++;
            }

            if(f_echiquier[i+1][j]==opp_symbole)
            {
                compteurcolon[1]++;
            }

            if(f_echiquier[i+2][j]==opp_symbole)
            {
                compteurcolon[1]++;
            }


            if(compteurcolon[0]==0 && compteurcolon[1]>=1)
            {

                if(compteurcolon[1]==2)
                {
                    somme+=BONUS2;
                }
                else if(compteurcolon[1]==3)
                {
                    somme+=BONUS3;
                }

                else
                    somme+=BONUS1;
            }
            else if(compteurcolon[0]>=1 && compteurcolon[1]==0)
            {
               if(compteurcolon[0]==2)
                {
                    somme-=BONUS2;
                }
                if(compteurcolon[0]==3)
                {
                    somme-=BONUS3;
                }
                else
                    somme-=BONUS1;
            }
            compteurcolon[0]=0;compteurcolon[1]=0;
        }
        i=0;j=0;

        //Sur les diagonales
        for(i=0;i<3;i++)
        {
            if(f_echiquier[i][i]==symbole)
            {
               compteurDiP[0]++;
            }
            if(f_echiquier[i][i]==opp_symbole)
            {
                compteurDiP[1]++;
            }
        }
        if(compteurDiP[0]==0 && compteurDiP[1]>=1)
        {
            if(compteurDiP[1]==2)
            {
                somme+=BONUS2;
            }
            if(compteurDiP[1]==3)
                {
                    somme+=BONUS3;
                }
            else
                somme+=BONUS1;
        }
        else if(compteurDiP[1]==0 && compteurDiP[0]>=1)
        {
            if(compteurDiP[0]==2)
                {
                    somme-=BONUS2;
                }
                if(compteurDiP[0]==3)
                {
                    somme-=BONUS3;
                }
                else
                    somme-=BONUS1;
        }


        for(j=0;j<3;j++)
        {
         if(f_echiquier[j][2-j]==symbole)
            {
               compteurDiS[0]++;
            }
            if(f_echiquier[j][2-j]==opp_symbole)
            {
                compteurDiS[1]++;
            }


        }

        if(compteurDiS[0]==0 && compteurDiS[1]>=1)
        {
            if(compteurDiS[1]==2)
            {
                somme+=BONUS2;
            }
            else if(compteurDiS[1]==3)
            {
                somme+=BONUS3;
            }
            else
                somme+=BONUS1;
        }
        else if(compteurDiS[1]==0 && compteurDiS[0]>=1)
        {
            if(compteurDiS[0]==2)
                {
                    somme-=BONUS2;
                }
                if(compteurDiS[0]==3)
            {
                somme-=BONUS3;
            }
                else
                    somme-=BONUS1;
        }



   return somme;   //Si la somme est n�gative, l'IA perd, sinon il est entrain de gagner

}








 void deplacementJoueur(echiquier  f_echiquier,char symbole)// Prend une position valide, et remplit l'echiquier
 {
     position f_position;
     // On s'assure que la position existe et qu'elle est vide
    do
    {

            do
            {
             printf("Veuillez entrer le numero de la ligne comprise entre 1 et 3\n");
             scanf("%d",&f_position.ligne);
            }while(f_position.ligne<1 || f_position.ligne>3);


             do
            {
             printf("Veuillez entrer le numero de la colonne comprise entre 1 et 3\n");
             scanf("%d",&f_position.colonne);
            }while(f_position.colonne<1 || f_position.colonne>3);


            if(f_echiquier[f_position.ligne-1][f_position.colonne-1]!='\0')
            {
                printf("Cette case est deja remplie\n");
            }


    }while(f_echiquier[f_position.ligne-1][f_position.colonne-1]!='\0');
    f_echiquier[f_position.ligne-1][f_position.colonne-1]=symbole;

 }

 int fonctionGagner(echiquier f_echiquier,char symbole)
{
    int i=0,j=0;
    for(i=0;i<3;i++)
    {
            if(f_echiquier[i][j]==f_echiquier[i][j+1] && f_echiquier[i][j]==f_echiquier[i][j+2] && f_echiquier[i][j]==symbole )
                return 1;
    }
    i=0;
    for(j=0;j<3;j++)
    {
        if(f_echiquier[i][j]==f_echiquier[i+1][j] && f_echiquier[i][j]==f_echiquier[i+2][j] && f_echiquier[i][j]==symbole)
        return 1;
    }

    if(f_echiquier[0][0]==f_echiquier[1][1] && f_echiquier[0][0]==f_echiquier[2][2] && f_echiquier[0][0]==symbole)
        return 1;
    if(f_echiquier[0][2]==f_echiquier[1][1] && f_echiquier[0][2]==f_echiquier[2][0] && f_echiquier[0][2]==symbole)
       {
         return 1;
       }

        return 0;
}


int* calcul_prof1(echiquier  f_echiquier,char symbole_IA)// Cette fonction n'est pas utilisee directement , mais par calcul_prof2
{

   int valeurs[3][3];
   int a=0,b=0;
   for(a=0;a<3;a++)
   {
       for(b=0;b<3;b++)
       {
           valeurs[a][b]=10000;
       }
   }


   int mini=0;
   int tmp1=0,tmp2=0;

   int c=0,d=0;


       //L'IA est en train de perdre MESURE DEFENSIVE

        for(c=0;c<3;c++)//On cherche les cases vides et on les remplit
        {
            for(d=0;d<3;d++)
             {
                if(f_echiquier[c][d]=='\0')
                {
                f_echiquier[c][d]=symbole_IA;
                valeurs[c][d]= evalue_adv(f_echiquier,symbole_IA);
                f_echiquier[c][d]='\0';
                }

             }

        }
                 //On d�termine le minimum des evaluations et on d�termine lecouple c,d correspondant
            mini=1000;//Car les evaluatiions seront toujours plus petites
            for(c=0;c<3;c++)
            {
                for(d=0;d<3;d++)
                {
                 if(valeurs[c][d]<mini)
                 {
                    mini=valeurs[c][d];
                    tmp1=c;tmp2=d;
                 }

                }
            }
//Puis on remplit la case meilleur choix
    f_echiquier[tmp1][tmp2]=symbole_IA;

    //MODIFICATION
  int *choix=malloc(sizeof(int)*2);
  choix[0]=tmp1; choix[1]=tmp2;
  return choix;
}


void calcul_prof2(echiquier f_echiquier,char symbole_IA)// Y a une combinaison pour laquelle elle ne fonctionne pas
{
    int i=0,j=0,a=0,b=0;
    int mini=0;
    int tmp1=0,tmp2=0;
    position f_position;
    int valeurs[3][3]={1000,1000,1000,1000,1000,1000,1000,1000,1000};
    int *choix=NULL;
    char symbolej=symboleIA(symbole_IA);

 if(grilleremplie(f_echiquier)<7)
 {
  for(i=0;i<3;i++)// Pour chaque coup possible
    {
        for(j=0;j<3;j++)
        {
            if(f_echiquier[i][j]=='\0')
            {
                f_echiquier[i][j]=symbole_IA;// On joue le coup
                choix=calcul_prof1(f_echiquier,symbolej);// On simule le meilleur mouvement DEFENSIF du joueur
                valeurs[i][j]=evalue_adv(f_echiquier,symbole_IA);//On evalue le plateau
                f_position.ligne=choix[0];
                f_position.colonne=choix[1];
                annulerDeplacement(f_echiquier,f_position);// On annule le mouvement simule du joueur
                f_echiquier[i][j]='\0';// On annule le coup
            }
        }
    }
    mini=1000;
    for(a=0;a<3;a++)// On determine le coup qui entrainera le minimum de gain pour le joueur sur une profondeur de 2
    {
        for(b=0;b<3;b++)
        {
           if(valeurs[a][b]<mini)
           {
               mini=valeurs[a][b];
               tmp1=a;tmp2=b;
           }
        }
    }
    f_echiquier[tmp1][tmp2]=symbole_IA;// On joue ce coup
 }
 else
 {
      choix=calcul_prof1(f_echiquier,symbole_IA);
      f_echiquier[choix[0]][choix[1]]=symbole_IA;
 }


}




void annulerDeplacement(echiquier f_echiquier, position f_position)
{
    f_echiquier[f_position.ligne][f_position.colonne]='\0';
}

char symboleIA(char symboleJ)
{
    if(symboleJ=='X')
        return 'O';
    else
        return 'X';
}

 void initialisateur(echiquier f_echiquier)// Initialise l'échiquier
{
    int i=0,j=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            f_echiquier[i][j]='\0';
        }
    }
}

int grilleremplie(echiquier f_echiquier)
{
    int i=0,j;
    int compteur=0;
     for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(f_echiquier[i][j]=='\0')
             compteur++;

        }
    }


    return compteur;

}










int main()
{

    int controller1=0;
    int controller2=0;

    char symbole;
    char symbole_IA;

    int nul=1;

    echiquier monEchiquier;
    int continuer=0;
    do
        {
    symbole=symboleJoueur();
    symbole_IA=symboleIA(symbole);
    initialisateur(monEchiquier);
    afficheGrille(monEchiquier);


    while(controller1!=1 && controller2!=1 && nul!=0)
    {
    deplacementJoueur(monEchiquier,symbole);
    controller1=fonctionGagner(monEchiquier,symbole);

    afficheGrille(monEchiquier);
    if(controller1==1)
     {
         break;
     }
     nul=grilleremplie(monEchiquier);
     if(nul==0)
     {
         break;
     }

    printf("\n\n");

    calcul_prof2(monEchiquier,symbole_IA);
    Sleep(2000);
    afficheGrille(monEchiquier);
    controller2= fonctionGagner(monEchiquier,symbole_IA);
    }
    if(controller1==1)
    {
         printf("Bravo, vous avez gagne\n");
    }
    if(controller2==1)
    {
        printf("L'AI a gagne\n");
    }
    if(grilleremplie(monEchiquier)==0)
    {
        printf("Partie nulle\n");
    }
    printf("Voulez vous faire une nouvelle partie noobbbb?\n0-Non\t1-Oui\n");
    scanf("%d",&continuer);


    nul=1;
    controller1=0;
    controller2=0;
        }while(continuer!=0);


    return EXIT_SUCCESS;
}
