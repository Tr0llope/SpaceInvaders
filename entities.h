
//initialise et retourne une liste chainee contenant tous les enemis
Enemies *init_enemies(char difficulty){
	Enemies *head = NULL, *enemies = NULL;
	int MINION_NBR=10, MINION_WAVE_NB=2, CAPTAIN_NBR=8, CAPTAIN_WAVE_NB=2, GUARDIAN_NBR=4, GUARDIAN_WAVE_NB=1, POSY_GUARDIAN=10, POSY_CAPTAIN=POSY_GUARDIAN+GUARDIAN_WAVE_NB*3, LEVIATHAN_NBR=1;
	int speed=1;
	if(difficulty=='h' || difficulty=='g'){
    	MINION_NBR=12; MINION_WAVE_NB=4; CAPTAIN_NBR=12; CAPTAIN_WAVE_NB=3; GUARDIAN_NBR=6; GUARDIAN_WAVE_NB=2; POSY_GUARDIAN=10; POSY_CAPTAIN=POSY_GUARDIAN+GUARDIAN_WAVE_NB*3; LEVIATHAN_NBR=2;
    	speed=2;
    	if(difficulty=='g') speed=1;
    }

    for(int i=0; i<LEVIATHAN_NBR;i++){
		enemies = malloc(sizeof(Enemies));
		enemies->name= 'l';
    	enemies->HP = 10;
    	if(difficulty=='e') enemies->posX = 60+20*i;
    	else enemies->posX = 50+20*i;
    	enemies->posY = 3;
    	enemies->speed = speed;
		enemies->is_dead = false;
		enemies->direction=1;
    	enemies->next=head;
        head=enemies;
    	}


	int posgy=POSY_GUARDIAN;
	for(int i=0; i<GUARDIAN_WAVE_NB;i++){
		int posgx=36;
		if(difficulty=='e') posgx=46;
		for(int j=0; j<GUARDIAN_NBR;j++){
		
			enemies = malloc(sizeof(Enemies));
			enemies->name= 'g';
			enemies->HP = 4;
			enemies->posX = posgx;
			enemies->posY = posgy;
			enemies->model = 1;
			enemies->speed = speed;
			enemies->is_dead = false;
			enemies->direction=1;
			enemies->next=head;
            head=enemies;
			posgx=posgx+10;
			}
			posgy+=3;
		}
	
	int poscy=POSY_CAPTAIN ;
	for(int i=0; i<CAPTAIN_WAVE_NB;i++){
		int poscx=23;
		if(difficulty=='e') poscx=37;
		for(int j=0; j<CAPTAIN_NBR;j++){
			enemies = malloc(sizeof(Enemies));
			enemies->name= 'c';
			enemies->HP = 2;
			enemies->posX = poscx;
			enemies->posY = poscy;
			enemies->model = 1;
			enemies->speed = speed;
			enemies->is_dead = false;
			enemies->direction=1;
			enemies->next=head;
            head=enemies;
			poscx=poscx+7;
			}
			poscy+=2;
		}
		   
    int posmy=POSY_CAPTAIN + CAPTAIN_WAVE_NB*2;
    for(int i=0; i<MINION_WAVE_NB;i++){
    	int posmx=23;
    	if(difficulty=='e') posmx=30;
		for(int j=0; j<MINION_NBR;j++){
		
			enemies = malloc(sizeof(Enemies));
			enemies->name= 'm';
			enemies->HP = 1;
			enemies->posX = posmx;
			enemies->posY = posmy;
			enemies->model = 1;
			enemies->speed = speed;
			enemies->is_dead = false;
			enemies->direction=-1;
			enemies->next=head;
            head=enemies;
			posmx=posmx+7;
		}
		posmy+=2;
	}
    return head;
}

//affiche les enemis
int display_enemies(Enemies *head){
	int nb_enemies=0;
	Enemies *enemies = NULL;
	while(head){
		if((head->name=='m')&&(head->is_dead==false)){
			color("33");
			display_element_XY(head->posX, head->posY, MINION_DEFAULT);
        		nb_enemies++;
		}
		if((head->name=='c')&&(head->is_dead==false)){
			color("32");
			if(head->HP>1) display_element_XY(head->posX, head->posY, CAPTAIN_DEFAULT);
			else display_element_XY(head->posX, head->posY, BROKEN_CAPTAIN);
        		nb_enemies++;
		}
		if((head->name=='g')&&(head->is_dead==false)){
			color("35");
			if(head->HP>=2) display_element_XY(head->posX, head->posY, GUARDIAN);
			else display_element_XY(head->posX, head->posY, BROKEN_GUARDIAN);
        		nb_enemies++;
		}
		if((head->name=='l')&&(head->is_dead==false)){
			color("36");
			if(head->HP>=5) display_element_XY(head->posX, head->posY, LEVIATHAN);
			else display_element_XY(head->posX, head->posY, BROKEN_LEVIATHAN);
        		nb_enemies++;
		}
		
		//INCREMENT
		enemies=head;
        head=head->next;
	}
	return nb_enemies;
}

//incremente la position des enemis
void update_enemies(Enemies *head, int i, char diff){
	Enemies *enemies = NULL;
	bool way=true;
	while(head){
		
		//augmente petit a petit la vitesse de deplacement en mode gradual
		if(diff=='g' && i%25==0) head->speed++;
		
		//Axis X
		
		if((head->posX-head->speed==5 && head->direction==-1) || (head->posX+head->speed==LIMIT_X && head->direction==1)){
			way=!way;
			break;
		}
		if(head->direction==1) head->posX+=head->speed;
		if(head->direction==-1) head->posX-=head->speed;
		
		//Axis Y
		if(diff=='h') {if(i%20==0) head->posY+=head->speed;}
		else {if(i%15==0) head->posY+=head->speed;}
		
		//INCREMENT
		enemies=head;
        head=head->next;
	}
	
	while(head){
		if(!way) head->direction=head->direction*(-1);
		//INCREMENT
		enemies=head;
        head=head->next;
	}
}


//libere l'espace memoire alloue aux enemis
void free_enemies(Enemies *head){
	Enemies *enemies = NULL;
	while(head!=NULL){
		free(head);
		
		//INCREMENT
		enemies=head;
        head=head->next;
	}
}


Enemies *select_random_enemy(Enemies *head, int nb_enemies){
	Enemies *enemies = NULL;
	srand(time(NULL));
	int i;
	i =rand() % nb_enemies;
	for(int j=0;j<i;j++){
		enemies=head;
        head=head->next;
	}
	return head;
}









