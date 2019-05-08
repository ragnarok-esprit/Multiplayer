#include "fonction.h"
void game (SDL_Surface *ecran){
int jumping=0;
int attacksync=0;
int mjump=0;
int mvm=20;
int charcattacking=0;
int hp[100];
int attackingnow=0;
int hpnumber=0;
perso perso,perso1 ;
int hit;
int falling=0;
int collisiopill=0;
int lastpos=0;
int collisiontumeur=0;
int collisionenuron=0;
int d=0,q=0,s=0,jump=0,x=0,y=1;//dep
int d1=0,q1=0,s1=0,jump1=0,x1=0,y1=0;//dep 2
int mvmspeed=20;
int jumpspeed=22;
int jumpheight=13;
ennemis firstenm ;
Objet attackcharc;
Objet tumor,pill,neuron,enemipoop,poopattack;
int continuer = 1;
int gravit=435;
int saut=1;
vie vie,vie1;

int debut[3];
int fin[3];
debut[0]=2195;
fin[0]=2523;
debut[1]=7205;
fin[1]=7517;
debut[2]=9139;
fin[2]=11521;
initialiservie(&vie) ;
initialiservie(&vie1) ;

int ennmouv,w=10;
SDL_Rect camera;
int prevd,prevq;
SDL_Surface *imageback=NULL;
SDL_Event event;
int p=1;
SDL_Surface *p1=NULL,*p2=NULL;
SDL_Rect pos;
p1=IMG_Load("player1.png");
p2=IMG_Load("player2.png");
pos.x=0;
pos.y=400;

if(p==1)p=0;

initialiserennemi(&firstenm);
imageback=Init_imagedefond(imageback ,&camera ,0, 0 );
initialiserperso(&perso);
initialiserperso(&perso1);
initialiserObj(&neuron,"../newgame/map/neuron.png",2700 ,435 );
initialiserObj(&attackcharc,"../newgame/charc/attack.png",-100 ,-100 );
initialiserObj(&pill ,"../newgame/map/pill1.png", 2350, 210 );
initialiserObj(&tumor ,"../newgame/map/tumor.png", 600,500 );
initialiserObj(&enemipoop ,"../newgame/charc/virus2.png", 3200,600 );
initialiserObj(&poopattack,"../newgame/charc/poopatc.png", 3250,610);
while(continuer)
{
if(vie.nb==0)
p=1;

if(perso.position.x<200)
{
SDL_BlitSurface(p1,NULL,imageback,&pos);
}
if(p==1)
{
SDL_BlitSurface(p2,NULL,imageback,&pos);
}
printf("\n%d",p);

	falling=0;
SDL_PollEvent(&event);
switch(event.type)
  	{
        case SDL_QUIT:
            continuer = 0;
	case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            			case SDLK_LEFT :
		q=1;	
                    	break ;
				case 'q':
		q1=1;
			break;
		case SDLK_RIGHT :
		d=1; 
			break ;
				case 'd':
		d1=1;
			break;
			case SDLK_LCTRL:

charcattacking=1;
			break;
		case SDLK_UP :
		jump=1; 
			break ;
		case 'z':
		jump1=1;
			break;
	    }
		break;
	case SDL_KEYUP:

            switch (event.key.keysym.sym)
            {
 		case SDLK_ESCAPE:
		    //continuer=0 ;
			break ;
				case SDLK_LCTRL:

charcattacking=0;
			break;
		

		case SDLK_LEFT :
		q=0;	
                    	break ;
		case 'q':
		q1=0;
			break;
		case SDLK_RIGHT :
		d=0; 
			break ;
		case 'd':
		d1=0;
			break;
		case SDLK_UP :
		jump=0; 
			break ;
		case 'z' :
		jump1=0;
			break;
	    }
		break;
}
SDL_Delay(20);
gravit=435;
mvmspeed=mvm;
if(perso.position.x+camera.x==10650)
enigm(ecran);
if(perso1.position.x+camera.x==10650)
enigm(ecran);
collisionpit(debut,fin,&gravit,3,perso.position,camera);
gravity(&perso.position,gravit,jump,jumping,jumpspeed,&falling);
jumpin(&perso.position,&camera,jump,&jumping,jumpheight,jumpspeed);
x=mouv(d,q,jumping,falling,x,perso,prevd,prevq);//mouvement perso 1
collisionenuron=collisionbb(perso.position,neuron.position,camera);

collisionpit(debut,fin,&gravit,3,perso1.position,camera);
gravity(&perso1.position,gravit,jump1,jumping,jumpspeed,&falling);
jumpin(&perso1.position,&camera,jump1,&jumping,jumpheight,jumpspeed);
x=mouv(d1,q1,jumping,falling,x1,perso1,prevd,prevq);//mouvement perso 1
collisionenuron=collisionbb(perso1.position,neuron.position,camera);

if(collisionenuron==1){
	mvmspeed=10;
}
collisiopill=collisionbb(perso.position,pill.position,camera);
collisiopill=collisionbb(perso1.position,pill.position,camera);
if(collisiopill==1){
	mvm=60;
	pill.position.y=-50;
	pill.position.x=-50;
}
if(attackingnow>0){
	attackcharc.position.x+=50;
	attackingnow--;
}
firstenm=mouvennemi(firstenm,perso,d,q,camera,ecran,&ennmouv,&w,&y,mvmspeed,&lastpos);
firstenm=mouvennemi(firstenm,perso1,d1,q1,camera,ecran,&ennmouv,&w,&y,mvmspeed,&lastpos);
//if(collisiontumeur==1&&d==1)
//perso.position.x-=30;
//else if(collisiontumeur==1&&q==1)
	//perso.position.x+=30;
mouvement(&perso.position,&camera,d,q,mvmspeed);
mouvement(&perso1.position,&camera,d1,q1,mvmspeed);
y=splitennemi(y);
attacking(&poopattack.position,&attacksync);
hp[0]=collisionbb(perso.position,poopattack.position,camera);
hp[1]=collisionbb(perso.position,enemipoop.position,camera);
if(perso.position.y>=550){
	hp[2]=1;
}else
hp[2]=0;

if(perso1.position.y>=550){
	hp[2]=1;
}else
hp[2]=0;

Health(&vie,hp,&camera,&perso.position,3);
Health(&vie1,hp,&camera,&perso1.position,3);
if(charcattacking==1&&attackingnow==0){
attackcharc.position.x=perso.position.x+camera.x+60;
attackcharc.position.y=perso.position.y+30;
attackingnow=30;
}
collisionennemi(&perso,&firstenm,&camera,&vie);
collisionennemi(&perso1,&firstenm,&camera,&vie1);
hit=collisionbb(firstenm.position,attackcharc.position,camera);

printf("%d\n",hit);
if(hit==1){
	firstenm.position.x=-5000;
	firstenm.position.y=-4000;
printf("azzzzzzze");
}//collisiontumeur=collisionbb(perso.position,tumor.position,camera);

SDL_BlitSurface(imageback, &camera, ecran, NULL);
affichageObj(attackcharc,ecran,camera);
affichageObj(pill , ecran,camera) ;
affichageObj(poopattack,ecran,camera) ;
affichageObj(enemipoop, ecran,camera) ;
affichageObj(neuron , ecran,camera);
if(p==0)afficherperso(perso,ecran,x);
if(p==1)afficherperso(perso1,ecran,x);
if(p==0)affichervie(&vie,perso,ecran);
if(p==1)affichervie1(&vie1,perso1,ecran);
afficherennemi(firstenm,ecran,y);
prevd = d;
prevq = q;
affichageObj(tumor , ecran,camera) ;
SDL_Flip(ecran);
}

SDL_FreeSurface(imageback);  
freefurfaceperso(&perso);
freefurfaceperso(&perso1);
freesurfaceennemi(&firstenm);
freesurfaceobject(&pill);
freesurfaceobject(&attackcharc);
freesurfaceobject(&poopattack);
freesurfaceobject(&tumor);
freesurfaceobject(&enemipoop);
freesurfaceobject(&neuron);
SDL_Quit();
}
