#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

struct grid {
    int *data;
    size_t l;
};

struct player {
    int px;
    int py;
    int vx;
    int vy;    
    int distance_initiale_x;
    int distance_initiale_y;
    int vx_max;
    int vy_max;
};

struct checkpoint {
    int x;
    int y;
    int h;
    int w;
    int x_best;
    int y_best;
};

void checkpoint_create (struct checkpoint *self){
    self->x=0;
    self->y=0;
    self->h=1;
    self->w=1;
    self->x_best=0;
    self->y_best=0;
}

void player_create (struct player *self){
    self->px=0;
    self->py=0;
    self->vx=0;
    self->vy=0;
}


void deplacement_one(struct player *self,const struct checkpoint *obj, const struct grid *grille){
    if(self->px<obj->x){
        switch(self->vx){
            case 1 :{
                self->px++;
            }break;
            case 0 :{
                self->px++;
                self->vx++;
            }break;
            case -1 :{
                self->vx--;
            }break;
            default:{}break;
        }
    } else {
        if(self->px>obj->x){
            switch(self->vx){
                case 1 :{
                    self->vx--;
                }break;
                case 0 :{
                    self->px--;
                    self->vx--;
                }break;
                case -1 :{
                    self->px--;
                }break;
                default:{}break;
            }

        } else {
            self->vx=0;
            if(self->py<obj->y){
                switch(self->vy){
                    case 1:{
                        self->py++;
                    }break;
                    case 0:{
                        self->py++;
                        self->vy++;
                    }break;
                    case -1:{
                        self->vy++;
                    }break;
                    default:{}break;
                }
            } else {
                if(self->py>obj->y){
                    switch(self->vy){
                        case 1 :{
                            self->vy--;
                        }break;
                        case 0 :{
                            self->py--;
                            self->vy--;
                        }break;
                        case -1:{
                            self->py--;
                        }break;
                        default:{}break;
                    }
                }
            }
        }
    }
}


int main(){

    struct grid grille;
    struct player one;
    struct checkpoint objective;

    checkpoint_create(&objective);
    player_create(&one);
    setbuf(stdout, NULL);
    char buf [BUFSIZE];

    //recuperation de la taille de la grille
    fgets(buf,BUFSIZE,stdin);
    grille.l = atoi(buf);
    grille.data = calloc(grille.l*grille.l,sizeof(int));

    //recuperation des valeurs de la grille
    for(size_t i=0;i<grille.l*grille.l;i++){
        fgets(buf,BUFSIZE,stdin);
        grille.data[i]=atoi(buf);
    }

    fgets(buf,BUFSIZE,stdin);
    one.px=atoi(buf);
    fgets(buf,BUFSIZE,stdin);
    one.py=atoi(buf);

    fgets(buf,BUFSIZE,stdin);
    objective.x=atoi(buf);
    fgets(buf,BUFSIZE,stdin);
    objective.y=atoi(buf);
    fgets(buf,BUFSIZE,stdin);
    objective.w=atoi(buf);
    fgets(buf,BUFSIZE,stdin);
    objective.h=atoi(buf);
    fprintf(stderr,"x %i\ny %i\nw %i\nh %i\n",objective.x,objective.y,objective.w,objective.h);

    //calcul_meilleure_case(&batman,&objective,&grille);
    //calcul_distance_initiale(&batman,&objective);
    //calcul_vitesse_max(&batman,&objective);
    

    for(;;){
        deplacement_one(&one,&objective,&grille);
        //fprintf(stderr,"px %i\npy %i\n",retad.distance_initiale_x,batman.distance_initiale_y);
       printf("%i\n%i\n",one.px,one.py);
       //printf("%i\n%i\n",bouledeneige.vx,bouledeneige.vy);
        fgets(buf,BUFSIZE,stdin);
        if(strcmp(buf,"ERROR\n")==0){
            break;
        }
        if(strcmp(buf,"CHECKPOINT\n")==0){
            fgets(buf,BUFSIZE,stdin);
            objective.x=atoi(buf);
            fgets(buf,BUFSIZE,stdin);
            objective.y=atoi(buf);
            fgets(buf,BUFSIZE,stdin);
            objective.w=atoi(buf);
            fgets(buf,BUFSIZE,stdin);
            objective.h=atoi(buf);
            fprintf(stderr,"x %i\ny %i\nw %i\nh %i\n",objective.x,objective.y,objective.w,objective.h);
          //  calcul_meilleure_case(&batman,&objective,&grille);
          //  calcul_distance_initiale(&batman,&objective);
          //  calcul_vitesse_max(&batman,&objective);
        }
        if(strcmp(buf,"FINISH\n")==0){
            break;
        }
    }
    return 0;
}