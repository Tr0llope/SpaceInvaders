
/*---------------fonctions d'initialisation, d'affichage et d'avancement dans la liste chainee des missiles du joueur------------------------------------------------------------*/

bullet * bullet_init(player *element){
	bullet *bullet = malloc(sizeof(bullet));
	bullet->posX= (*element).posX+4;
	bullet->posY= (*element).posY-1;
	bullet->next=NULL;
     	return bullet;
	}

bullet * next_bullet(player *element, bullet *bullet){
	bullet=bullet->next;
	bullet = bullet_init(element);
	return bullet;
}

void display_bullet(bullet *bullet){
	printf("\033[%d;%dH", bullet->posX,bullet->posY);
        color("36");
        display_element_XY(bullet->posX, bullet->posY, BULLET);
}

/*---------------fonctions d'initialisation, d'affichage et d'avancement dans la liste chainee des missiles enemis---------------------------------------------------------------*/

bullet * bomb_init(Enemies *head, int nb_enemies){
	Enemies *enemy=select_random_enemy(head, nb_enemies);
	bullet *bomb = malloc(sizeof(bullet));
	if((enemy->name=='m')&&(enemy->is_dead==false)){
		bomb->posX=enemy->posX+1;
		bomb->posY=enemy->posY+1;
		bomb->next=NULL;
	}
	else if((enemy->name=='c')&&(enemy->is_dead==false)){
		bomb->posX=enemy->posX+3;
		bomb->posY=enemy->posY+1;
		bomb->next=NULL;
			
	}
	else if((enemy->name=='g')&&(enemy->is_dead==false)){
		bomb->posX=enemy->posX+3;
		bomb->posY=enemy->posY+2;
		bomb->next=NULL;
			
	}
	else if((enemy->name=='l')&&(enemy->is_dead==false)){
		bomb->posX=enemy->posX+5;
		bomb->posY=enemy->posY+1;
		bomb->next=NULL;
	}
	else{
		srand(time(NULL));
		int i=0;
		while(i<2) i =rand() % 120;
		bomb->posX=enemy->posX=i;
		bomb->posY=enemy->posY=2;
		bomb->next=NULL;
	}
     	return bomb;
	}

bullet * next_bomb(Enemies *head, int nb_enemies, bullet *bomb){
	bomb=bomb->next;
	bomb = bomb_init(head, nb_enemies);
	return bomb;
}

void display_bomb(bullet *bomb){
	printf("\033[%d;%dH", bomb->posX,bomb->posY);
        color("31");
        display_element_XY(bomb->posX, bomb->posY, BOMB);
}
