#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define HAUT    'i'
#define BAS     'k'
#define GAUCHE  'j'
#define DROITE  'l'
#define POSER   'p' 
#define RETIRER 'r' 
#define QUITTER 'q' 
#define TAILLE   100
char flag;    /*X ou O,joueur */ 
char key;     /*i,j,l,k,p,r,q  le clavier */
int n;        /*la taille du tableau */
int m=1;      /*le mode du jeu */
char buffer[2];

struct pile     
{
	char val[TAILLE];
	int sommet;
};
typedef struct pile* pile;

/*
@require rien 
@assigns p, malloc un m¨¦moire de taille du (struct pile) 
@ensures cree un pile  
*/ 
pile createPile()
{
	pile p;
	p=(pile)malloc(sizeof(struct pile));
	p->sommet = -1;
	return p;
}
/*
@require p non null 
@assigns rien 
@ensures ajouter un ¨¦l¨¦ment dans ce pile 
*/ 
void push(char c,pile *p)
{
	if((*p)->sommet >=TAILLE)
			printf("vous pouvez pas poser un jeton ici");
	else
	{
	(*p)->sommet = (*p)->sommet+1;
	(*p)->val[(*p)->sommet]=c;
	}	
}
/*
@require p non null 
@assigns rien 
@ensures retirer un ¨¦l¨¦ment   
*/ 
char pop(pile *p)
{
	char c=(*p)->val[(*p)->sommet];
	(*p)->sommet = (*p)->sommet-1;
	return c;
}
/*
@require p non null 
@assigns rien 
@ensures affiche le pile (les jetons) 
*/ 
void affichePile(pile p)
{
	int tmp=p->sommet;
	printf("le contenu de la pile sur la case sélectionnée:('.'est le fond)   ");
	while(p->sommet >=0)
	{
		printf("%c ",p->val[p->sommet]);
		p->sommet =p->sommet-1;                  
	}
	p->sommet=tmp;
	printf("\n");
}


/*
@require rien 
@assigns t,malloc les m¨¦moires pour les pile 
@ensures cree un tableau ,t[i][j] contient un pointeur vers un pile 
*/ 
pile ** createTableau()
{
	int i,j;
	pile** t=(pile **)calloc(n*3,sizeof(pile*)) ;
	for(i=0;i<n*3;i++)
	{
		t[i]=(pile *)calloc(n*3,sizeof(pile)); 
	}
	for(i=0;i<3*n;i++)
	{
		for(j=0;j<n*3;j++)
		{
			t[i][j]=createPile();
			push(' ',&t[i][j]);              /*chaque case est initialis¨¦par espace */ 
		}
	}
	return t;
}
/*
@require t non null
@assigns rien
@ensures affiche ce tableau(les sommet du chaque pile,vu dessous ) 
*/
void affiche(pile **t)
{
	int i,j;
		for(i=0;i<3*n;i++)
	{
		for(j=0;j<n*3;j++)
		{
			printf("%c",t[i][j]->val[t[i][j]->sommet]);           /*imprimer le sommet du pile*/
		}
		printf("\n");                     
	}
	for(i=0;i<3*n;i++)
		printf("-");                                     /*imprimer ---- au dessous du tableau indiquant la taille du tableau */
	printf("\n");
}
/*
@require rien
@assigns rien 
@ensures alter le joueur
*/ 
void alterJoueur()
{
    if(flag=='O')
        flag='X' ;
    else 
        flag='O';
}  
 
 
 /*
@require n*3>=x>=0,n*3>=y>=0,char **t non null
@assigns rien
@ensures affiche le tableau apr¨¨s  le joueur  choisi une case*/
void choisi (int x,int y,pile **t,char flag)
{
	push('+',&t[x+1][y]);
	push('+',&t[x-1][y]);
	push('+',&t[x][y-1]);
	push('+',&t[x][y+1]);                                 /*ajouter les '+' autour la case s¨¦lectionn¨¦ */
	system("clear");
	affiche(t);
	printf("c'est tour de --%c--,Quel est votre choix ?\n ",flag);	
	printf("\n");
	affichePile(t[x][y]);
	pop(&t[x+1][y]);
	pop(&t[x-1][y]);
	pop(&t[x][y+1]);															
	pop(&t[x][y-1]);										/*supprimer les '+' avant le joueur choisit une prochaine case*/
}
/*
@require t non null,n*3>=x>=0,n*3>=y>=0,
@assigns rien
@ensures estimer est-ce que ce joueur a gagne(2D,vu dessous )
*/ 
void gagner(pile **t,int x,int y)
{
	int i,cnt=0,j;
	for(i=1;i<3*n;i=i+3)                          /*horizontal*/
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
			if(t[x][i]->val[t[x][i]->sommet]==t[x][y]->val[t[x][y]->sommet])
				cnt++;
			else
				break;
		}
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;
	for(i=1;i<3*n;i=i+3)                          /*verticale*/
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
		if(t[i][y]->val[t[i][y]->sommet]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
		else
			break;
		}
	}
	if(cnt==n)		
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;
	for(i=1;i<3*n;i=i+3)                               /*diagonale augmenter */
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
		if(t[i][i]->val[t[i][i]->sommet]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
		}
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;
	for(i=3*n-2,j=1;j<3*n;i=i-3,j=j+3)                       /*diagonale descendre */
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
		if(t[i][j]->val[t[i][j]->sommet]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
		}
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
}

 /*
@require n>=x>=0,n>=y>=0,char **t non null
@assigns rien
@ensures ajouter les ¨¦toiles autour de jeton et affiche le tableau chaque fois d'effondrer
*/
void etoile (int x,int y,pile **t)
{
	push('*',&t[x+1][y]);
	push('*',&t[x+1][y+1]);
	push('*',&t[x+1][y-1]);
	push('*',&t[x-1][y]);
	push('*',&t[x-1][y+1]);
	push('*',&t[x-1][y-1]);
	push('*',&t[x][y-1]);
	push('*',&t[x][y+1]);
}
 /*
@require n>=x>=0,n>=y>=0,char **t non null
@assigns rien
@ensures supprimer les ¨¦toiles autour de jeton et affiche le tableau chaque fois d'effondrer
*/
void deletoile (int x,int y,pile **t)
{
	pop(&t[x+1][y]);
	pop(&t[x-1][y]);
	pop(&t[x][y-1]);
	pop(&t[x][y+1]);
	pop(&t[x+1][y+1]);
	pop(&t[x-1][y+1]);
	pop(&t[x+1][y-1]);
	pop(&t[x-1][y-1]);
}
/*
@require t non null 
@assigns  tableau g,contenant des coordonn¨¦es des cases qui s'effondrent  
@ensures   ¨¤ chaque changement de tour, chacune des piles du plateau a une probabilit¨¦ de s'effrondrer partiellement
*/ 
int * seisme (pile **t)
{
	int *g=malloc(n*n*2*sizeof(int));        /*contenant des coordonn¨¦es des cases qui s'effondrent  */
	int l=1;
	int i,j,b,h,c,k;
	double a,tmp;
	srand(time(NULL));
	for(i=1;i<3*n;)
	{
		for(j=1;j<n*3;)
		{
			
				h=t[i][j]->sommet-1;            /*h: la hauteur du pile */   
				a=0.0-((double)h/(2*n));         /*a: -h/2n*/
				tmp=pow(2.0,a);                  /*tmp:  2^(-h/2n)*/
				tmp=1.0-tmp;				    /*tmp: 1-2^(-h/2n)*/
				tmp=tmp*10000.0;
				c=rand()%10001;                 /*La probabilit¨¦ qu'une pile s'effondre est fonction de sa hauteur h et de la largeur n du plateau selon la formule : 1 - 2-h/(2n)*/
				if(c<=tmp)
				{
					g[l]=i;
					g[l+1]=j;
					l=l+2;
					etoile(i,j,t);
					b=rand()%h+1;     /*le nombre de jeton ¨¤ retirer est un nombre al¨¦atoire compris entre 1 et h*/
					for(k=0;k<b;k++)
					{
						pop(&t[i][j]);
					}
				}
			j=j+3;
		}
		i=i+3;
	}
	g[0]=l-1;
	return g;
}
/*
@require t non null,n*3>=x>=0,n*3>=y>=0,
@assigns rien
@ensures estimer est-ce que ce joueur a gagne(3D )
*/ 
void gagner3D(pile **t,int x,int y)
{
	int k,cnt;
	int i,j;
	if(t[x][y]->sommet>=n+1)  /*si la hauteur du pile sup¨¦rieur ou ¨¦gale n*/
	{
		cnt=0;
		for(k=2;k<(t[x][y]->sommet);k++)/*parcourir tout les jeton dans un pile (t[x][y]->val[0]==' ',t[x][y]->val[1]=='.',donc k commence ¨¤2)*/
		{
			if(t[x][y]->val[k]==t[x][y]->val[t[x][y]->sommet])
				cnt++;
			if(t[x][y]->val[k+1]!=t[x][y]->val[t[x][y]->sommet])/*si dans ce pile, il y a un jeton qui n'est pas flag, cnt=0*/
				cnt=0;			
		}
		if(t[x][y]->val[t[x][y]->sommet]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
		if(cnt>=n)                /*cnt>=n,flag a gagn¨¦ */                                   
			printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	} 
/****************************************************************************************************************************************************
*		une ligne, une colonne ou une diagonale sur un m¨ºme niveau ;  ressemble avec fonction gagne(pile **t,int x,int y),mais sur un m¨ºme niveau *
*****************************************************************************************************************************************************
*/
		for(i=1;i<3*n;i=i+3)                          /*niveau--------horizontal*/
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
			if(t[x][i]->val[t[x][y]->sommet]==t[x][y]->val[t[x][y]->sommet])
				cnt++;
			else
				break;
		}
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;
	for(i=1;i<3*n;i=i+3)                          /*niveau---------verticale*/
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
		if(t[i][y]->val[t[x][y]->sommet]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
		else
			break;
		}
	}
	if(cnt==n)		
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;
	for(i=1;i<3*n;i=i+3)                               /*niveau-------diagonale augmenter */
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
		if(t[i][i]->val[t[x][y]->sommet]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
		}
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;
	for(i=3*n-2,j=1;j<3*n;i=i-3,j=j+3)                       /*niveau--------diagonale descendre */
	{
		if(t[x][y]->val[t[x][y]->sommet]=='X'||t[x][y]->val[t[x][y]->sommet]=='O')
		{
		if(t[i][j]->val[t[x][y]->sommet]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
		}
	}
	if(cnt==n)                           
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;                                /*une ligne "en escalier montant "---------x constant  */
	for(i=1,j=t[x][y]->sommet-(y/3);i<3*n;i=i+3,j++)
	{
		if(t[x][i]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;                             	/* un ligne "en escalier descendant",--------x constant */
	for(i=1,j=t[x][y]->sommet+(y/3);i<3*n;i=i+3,j--)
	{
		if(t[x][i]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;         	                     /*une ligne "en escalier montant "-------- y constant  */
	for(i=1,j=t[x][y]->sommet-(x/3);i<3*n;i=i+3,j++)
	{
		if(t[i][y]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;                              	/* un ligne "en escalier descendant"------- y constant */
	for(i=1,j=t[x][y]->sommet+(x/3);i<3*n;i=i+3,j--)
	{
		if(t[i][y]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);	
			cnt=0;                                /*une ligne "en escalier montant "------- diagonale montant   */
	for(i=1,j=t[x][y]->sommet-(y/3);i<3*n;i=i+3,j++)
	{
		if(t[i][i]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;                             	/* un ligne "en escalier descendant",-------diagonale descendre  */
	for(i=1,j=t[x][y]->sommet+(y/3);i<3*n;i=i+3,j--)
	{
		if(t[i][i]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;         	                     /*une ligne "en escalier montant ",--------diagonale montant  */
	for(i=1,k=3*n-2,j=t[x][y]->sommet-(y/3);i<3*n;i=i+3,j++,k=k-3)                                      
	{
		if(t[k][i]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
	cnt=0;                              	/* un ligne "en escalier descendant"------diagonale descendre */
	for(i=1,k=3*n-2,j=t[x][y]->sommet+(y/3);i<3*n;i=i+3,j--,k=k-3)
	{
		if(t[k][i]->val[j]==t[x][y]->val[t[x][y]->sommet])
			cnt++;
	}
	if(cnt==n)
		printf("****%c a gagne!!!!!!!****",t[x][y]->val[t[x][y]->sommet]);
}
/*
@require t non null,flag=X ou flag=O
@assigns char **t
@ensures poser ou retirer un jeton sur le sommet d'pile
*/ 
pile ** poser (pile **t,char flag)
{

	int *g;
	int i;
	if(m==2||m==4)
		g=seisme(t);           /*¨¤ chaque changement de tour, chacune des piles du plateau a une probabilit¨¦ de s'effrondrer partiellement,*/
	int x=1;int y=1;
		choisi(x,y,t,flag);    /*¨¤ chaque changement de tour,on commence toujours ¨¤t[1][1]*/
	int s=1;
	while(s)                   /*s=1,mais quand joueur tape 'q' ou 'p', s=0,  while termine */    
	{
		scanf("%1s",buffer);
		key=buffer[0];
		switch(key)
		{
			case GAUCHE:             /*gauche*/ 
				if(y>=3)
				{
					y=y-3;
					choisi(x,y,t,flag);
				}
					break;
			case DROITE:            /*droite*/ 
				if(y<3*n-3)
				{
					y=y+3;
					choisi(x,y,t,flag);
				}
					break;
			case BAS:            /*bas*/
				if(x<3*n-3)
				{
					x=x+3;
					choisi(x,y,t,flag);
				}
					break;
			case HAUT:            /*haut*/
				if(x>=3)
				{
					x=x-3;
					choisi(x,y,t,flag);
				} 
					break;
			case RETIRER:                /*retirer un jeton ,et  v¨¦rifier les conditions de victoire*/
				if(t[x][y]->val[t[x][y]->sommet]!='.')
				{
					pop(&t[x][y]);
					if(m==1||m==2)
						gagner(t,x,y);
					else
						gagner3D(t,x,y);
					system("clear");
					choisi(x,y,t,flag);				
					printf("\n vous avez retire un jeton");
					break;
				}
				else
					printf("c'est le fond,vous ne pouvez pas retirer un jeton");    /*si t[x][y]->val[t[x][y]->sommet]=='.',on ne peut pas retirer un jeton */
					break;
			case POSER:
				s=0;
				break;
			case QUITTER:
				s=0;
				break;

		}
		
	}
	if(flag=='X')             /*poser un jeton*/
		push('X',&t[x][y]);
	else
		push('O',&t[x][y]);
	affiche(t);
	system("clear");
	if(m==1||m==2)
		gagner(t,x,y);                /*v¨¦rifier les conditions de victoire*/
	if(m==4||m==3)
		gagner3D(t,x,y);
	if(m==2||m==4)            /*si ils s'effondrent , supprimer les ¨¦toiles avant la prochaine tour*/
	{
		if(g[0]>1)
		{
			for(i=1;i<g[0];i=i+2)
			{	
				deletoile(g[i],g[i+1],t);
				if(t[g[i]][g[i+1]]->val[t[g[i]][g[i+1]]->sommet]!='.')
					gagner(t,g[i],g[i+1]);
			}
		}
	}
	return t;
}
 
int main() 
{
		printf("choisez un mode SVP:\n2D---tapez 1\n2D avec option séisme---tapez 2\n3D---tapez 3\n3D avec option séisme---tapez 4\n");
		scanf("%d",&m);
	while(m!=1&&m!=2&&m!=3&&m!=4)
	{
		printf("---------erreur------------\n");/*si le joueur a choisi un mode qui n'exsite pas ,erreur */
		printf("choisez un mode SVP:\n2D---tapez 1\n2D avec option séisme---tapez 2\n3D---tapez 3\n3D avec option séisme---tapez 4\n");
		scanf("%d",&m);
	}
	printf("tapez la taille du tableau(vous devez taper un entier)\n");
	scanf("%d",&n);
	while(n>50||n<0)
	{
		printf("tapez un entier entre 1-50 S.V.P");
		scanf("%d",&n);
	}
	printf("\n\n\n\n");
	pile **t=createTableau();                 
	int j,i;
	for(i=1;i<3*n;)               /*mettre un '.' dans chaque case, faire le tableau plus clair */
	{
		for(j=1;j<n*3;)
		{
		push('.',&t[i][j]);
			j=j+3;
		}
		i=i+3;
	}
	flag='X';
	while(key!=QUITTER)            /*quand le joueur taper 'q',on quitte ce jeu*/
	{ 
		t=poser(t,flag);
		alterJoueur(); 
	} 
	system("clear");
	printf("===========================game over===============================\n");
	return 0;
}

