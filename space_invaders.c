#include "macro_types.h"
#include "space_invaders.h"
#include "entities.h"
#include "bullet.h"

// affiche le fond du jeu et ses informations ainsi que le vaisseau du joueur
int display_update(player *element, Enemies *enemies, bool shot, bool background_status, char difficulty, int score, int life)
{
    clear();
    display_background(background_status, difficulty, score, life);
    color("0");
    if(difficulty!='h' && life==2) display_element_XY((*element).posX, (*element).posY, BROKEN_PLAYER1);
    else if(difficulty!='h' && life==1) display_element_XY((*element).posX, (*element).posY, BROKEN_PLAYER2);
    else display_element_XY((*element).posX, (*element).posY, PLAYER);
    int nb_enemies=display_enemies(enemies);
    return nb_enemies;
}

// retourne true si il y a collision entre un tir du joueur et un enemi
bool collision(Enemies *head, bullet *bullet, int score){
	Enemies *enemies = NULL;
	while(head){
		if(head->name=='m'){
			if(((head->posX==bullet->posX)||(head->posX+1==bullet->posX)||(head->posX+2==bullet->posX)||(head->posX+3==bullet->posX)||(head->posX+4==bullet->posX))&&(head->posY==bullet->posY)&&(head->is_dead==false)){
				head->HP--;
				if(head->HP==0){ head->is_dead=true; printf("  "); printf("\033[%d;%dH", head->posY, head->posX+1 ); printf("💥"); score++;}
				else{
					color("31");
					display_element_XY(head->posX, head->posY, MINION_DEFAULT);
				}
				return true;
				}
			}
		if(head->name=='c'){
			if(((head->posX==bullet->posX)||(head->posX+1==bullet->posX)||(head->posX+2==bullet->posX)||(head->posX+3==bullet->posX)||(head->posX+4==bullet->posX))&&(head->posY==bullet->posY)&&(head->is_dead==false)){
				head->HP--;
				if(head->HP==0){ head->is_dead=true; printf("  "); printf("\033[%d;%dH", head->posY, head->posX+1 ); printf("💥"); score++;}
				else{
					color("31");
					display_element_XY(head->posX, head->posY, CAPTAIN_DEFAULT);
				}
				return true;
				}
			}
		if(head->name=='g'){
			if(((head->posX==bullet->posX)||(head->posX+1==bullet->posX)||(head->posX+2==bullet->posX)||(head->posX+3==bullet->posX)||(head->posX+4==bullet->posX)||(head->posX+5==bullet->posX))&&(head->posY==bullet->posY)&&(head->is_dead==false)){
				head->HP--;
				if(head->HP==0){ head->is_dead=true; printf("  "); printf("\033[%d;%dH", head->posY+1, head->posX+2 ); printf("💥"); score++;}
				else{
					color("31");
					display_element_XY(head->posX, head->posY, GUARDIAN);
				}
				return true;
				}
			}
		if(head->name=='l'){
			if(((head->posX==bullet->posX)||(head->posX+1==bullet->posX)||(head->posX+2==bullet->posX)||(head->posX+3==bullet->posX)||(head->posX+4==bullet->posX)||(head->posX+5==bullet->posX)|| (head->posX+6==bullet->posX)||(head->posX+7==bullet->posX)||(head->posX+8==bullet->posX)||(head->posX+9==bullet->posX))&&(head->posY==bullet->posY)&&(head->is_dead==false)){
				head->HP--;
				if(head->HP==0){ head->is_dead=true; printf("  "); printf("\033[%d;%dH", head->posY+2, head->posX+4 ); printf("💥"); score++;}
				else{
					color("31");
					display_element_XY(head->posX, head->posY, LEVIATHAN);
				}
				return true;
				}
			}
	enemies=head;
    head=head->next;
	}
	return false;
}

// incremente la position des missiles du joueur
int bullet_update(player *element, Enemies *enemies, bool shot, bool background_status, char difficulty, int score, int life, bullet *bullet){
	bool col=false;
	while(bullet->posY!=1){
		printf("\033[%d;%dH", bullet->posX, bullet->posY+1);
        printf("  ");
        display_update(element, enemies, false, background_status, difficulty, score, life);
    	display_bullet(bullet);
    	fflush(stdout);
    	usleep(20000);
		col=collision(enemies, bullet, score);
    		if(col) return 10;
        	bullet->posY=bullet->posY-1;
    		}
    return -2;
}

// retourne vrai si le joueur recoit un missile
bool bomb_collision(player *element, bullet *bomb){
	if((bomb->posX>=element->posX+3 && bomb->posX<=element->posX+6 && bomb->posY==element->posY) ||
(bomb->posX>=element->posX+3 && bomb->posX<=element->posX+7 && bomb->posY==element->posY+1) ||
(bomb->posX>=element->posX+2 && bomb->posX<=element->posX+9 && bomb->posY==element->posY+2) ||
(bomb->posX>=element->posX+1 && bomb->posX<=element->posX+10 && bomb->posY==element->posY+3) ||
(bomb->posX>=element->posX && bomb->posX<=element->posX+11 && bomb->posY==element->posY+4)) return true;
	return false;
}

// incremente la position des missiles enemis
int bomb_update(player *element, Enemies *enemies, bool shot, bool background_status, char difficulty, int score, int life, bullet *bomb){
	bool col=false;
	if(bomb->posY!=52){
		display_update(element, enemies, false, background_status, difficulty, score, life);
	    display_bomb(bomb);
		col=bomb_collision(element, bomb);
    	if(col) return 1;
        bomb->posY=bomb->posY+2;
    	}
    if(bomb->posY+2>=52) return 1;
    return 0;
}

//retourne vrai si un enemy atteint le joueur ou le bas de l'ecran
bool defeat(Enemies *head, player *element){
	Enemies *enemies = NULL;
	while(head){
		if((head->posY==element->posY || head->posY==element->posY+1 || head->posY==element->posY+2) && (head->posX==element->posX || head->posX==element->posX+1 || head->posX==element->posX+2 || head->posX+1==element->posX+2 || head->posX+2==element->posX+2 || head->posX+1==element->posX+1 || head->posX+1==element->posX || head->posX+2==element->posX) && head->is_dead==false) return true;
		
		if(head->posY>=52 && head->is_dead==false) return true;
		enemies=head;
        head=head->next;
	}
	return false;
}


//fonction principale du jeu, permet d'executer les commandes donnees par le joueur
int player_listen(player *element, Enemies *enemies, bool shot, bullet *bull, bullet *bomb, char difficulty, int score, int life){

	bool background_status = false, win=true;
	double last_timestamp = timestamp();
	int i=0, nb_enemies=1;
    
    while(win)
    {
        TIMECHECK;
        printf("\033[%d;%dH", 52,130);
        char input; 
        input = key_pressed();
        if(defeat(enemies, element) || bomb_collision(element, bomb)) return 3;
    	
        if(nb_enemies==0) return 1;
        else if(life==0) return 0;
        else{
    	
        // Escape
        if (input == 27) 
        {
            clear();
            return -1;
        }
    
        // D INPUT = player goes right
        else if (input == 'd' && (*element).posX < PLAYER_X_MAX)
        {
            if ( (*element).posX + PLAYER_SPEED > PLAYER_X_MAX )
            {
                (*element).posX+=1;
                display_update(element, enemies, false, background_status, difficulty, score, life);
                display_enemies(enemies);
                display_bomb(bomb);
            }
    
            else
            {
                (*element).posX+=PLAYER_SPEED;
                display_update(element, enemies, false, background_status, difficulty, score, life);
                display_enemies(enemies);
                display_bomb(bomb);
            }
        }
    
        // Q INPUT = player goes left
        else if (input == 'q' && (*element).posX > PLAYER_X_MIN)
        {
            if ( (*element).posX - PLAYER_SPEED < PLAYER_X_MIN )
            {
                (*element).posX-=1;
                display_update(element, enemies, false, background_status, difficulty, score, life);
                display_enemies(enemies);
                display_bomb(bomb);
            }
    
            else
            {
                (*element).posX-=PLAYER_SPEED;
                display_update(element, enemies, false, background_status, difficulty, score, life);
                display_enemies(enemies);
                display_bomb(bomb);
                
            }
        }
        
        // Z INPUT = shoot
        if (input == 'z'){
        	bull = next_bullet(element, bull);
        	score+=bullet_update(element, enemies, shot, background_status, difficulty, score, life, bull);
            
        }
        }
    }
    return 0;
}


int main(){
	bool play_again=true, background_status=false;
	int score=0;
	while(play_again){
	
		// LAUNCHER
		char diff = choose_difficulty();
		int result=2;
		int life, nb_enemies;
		if(diff=='h') life=1;
		else life=3;
		Enemies *enemies=init_enemies(diff);
		player *me = player_init();
		nb_enemies=display_update(me, enemies, false, background_status, diff, score, life);
		while(life>=0 && (result!=-1 && result!=1 && result!=0)){
			// GAME INIT
			player *me = player_init();
			bullet *bull = bullet_init(me);
			bullet *enemies_bomb= bomb_init(enemies, nb_enemies);
			
			result = player_listen(me, enemies, false, bull, enemies_bomb, diff, score, life);
			
			if(result==3) life--;
			
			free(me);
			free(bull);
		}
		// END
		score=display_background(false, diff, score, life);
		play_again = end(result, score);
		
		// FREE, CLEAR SCREEN, QUIT 
		free_enemies(enemies);  
		clear();
	
	}
    return 0;
}



