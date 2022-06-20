// fonction donnee qui permet de recuperer les sorties du clavier
char key_pressed()
{
    struct termios oldterm, newterm;
    int oldfd; char c, result = 0;
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);
    if (c != EOF) {ungetc(c, stdin); result = getchar();}
    return result;
}

//fonction de gestion du temps, retourne un delai a attendre
double timestamp()
{
    struct timeval ts;
    gettimeofday(&ts, NULL); // valeur de retour ignoree

    double secs;
    double usecs; 
    double timestamp;
    secs = ts.tv_sec;
    usecs = ts.tv_usec;

	// Move
    while (usecs > 1) usecs = usecs/10;

    timestamp = secs + usecs;

    return timestamp;
}

//affiche a la position (x,y) le contenu du fichier en argument
void display_element_XY(int x, int y, char *file_path)
{
    int x_draw = x;
    int y_draw = y;
 
    printf("\033[%d;%dH", y_draw,x_draw);
    int c;
    FILE *file;
    file = fopen(file_path, "r");
    if (file) 
    {
        while ((c = getc(file)) != EOF)
        {
            if (c == '\n') 
            {
                y_draw+=1;
                printf("\033[%d;%dH", y_draw, x_draw);
            }
 
            else
                printf("%c", c);           
        }
 
        fclose(file);
    }
}
 
// affiche le fond d'ecran (tout ce qui s'affiche en bleu)
int display_background(bool background_status, char difficulty, int score, int life){
    color("34");
    printf("\033[%d;%dH", 1,1);
 
    int c;
    FILE *file;

    if (background_status == false) file = fopen(BACKGROUND01, "r");
    else file = fopen(BACKGROUND02, "r");

    if (file) 
    {
        while ((c = getc(file)) != EOF)
        {
            printf("%c", c);
        }
 
        fclose(file);
    }

    printf("\033[%d;%dH", 5,139);
    color("33");
    printf("%d", score);
    color("34");
    printf("\033[%d;%dH", 6,138);
    if(difficulty == 'h'){color("31"); printf("Hard"); color("34");}
    else if(difficulty == 'g'){ color("37"); printf("Gradual"); color("34");}
    else{ color("32"); printf("Easy"); color("34");}
    printf("\033[%d;%dH", 7,138);
    printf("%d", life);
    printf("\033[%d;%dH", 52, 1);
    return score;
}


/*----------------------------------------------------------------------------------------------------------------------------------*/

//
player * player_init()
{
    player *player = malloc(sizeof(player));
    (*player).HP = 10;
    (*player).posX = 54;
    (*player).posY = 45;
 
    return player;
} 

// permet de choisir la difficulte au debut d'une partie, retourne e, g ou h pour les trois modes disponibles: easy, gradual ou hard
char choose_difficulty(){
	clear();
	color("37");
	display_element_XY(40, 20, LAUNCHER);
	char difficulty='\0';
	printf("\033[%d;%dH", 33, 70 );
	printf("Difficulty (Easy (e), Hard (h), Gradual (g) : ");
	scanf("%c", &difficulty);
	if((difficulty!='h')&&(difficulty!='g')) difficulty='e';
    clear();
    return difficulty;
}

// fonction purement esthetique qui intervient a la fin du jeu
bool end(int result, int score){
	if(result==1){
		clear();
		color("32");
		display_element_XY(60, 20, WIN);
	}
	else{
		clear();
		color("31");
		display_element_XY(50, 20, GAMEOVER);
	}
	printf("\033[%d;%dH", 30, 75);
	printf("Score: %d Try again ? (y/n) : ", score);
	char play='\0';
	scanf("%c", &play);
	clear();
	if(play=='y'){
		return true;
	}
	color("33");
	display_element_XY(80, 20, END);
	fflush(stdout);
	usleep(1000000);
	clear();
	return false;
}




