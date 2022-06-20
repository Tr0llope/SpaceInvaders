#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

//PLAYER
#define PLAYER_HP 10
#define PLAYER_SPEED 4
#define PLAYER_X_MIN 2
#define PLAYER_X_MAX 117
#define PLAYER_WIDTH 9
 
// X: 127 - Y - 52
#define LIMIT_X 120
#define LIMIT_Y 52

// Levels parameters: number of enememies, speed, HP
 
//RESSOURCES
#define LEVIATHAN "./models/leviathan/leviathan_default.txt"
#define BROKEN_LEVIATHAN "./models/leviathan/leviathan_broken.txt"
#define GUARDIAN "./models/guardians/guardian_default.txt"
#define BROKEN_GUARDIAN "./models/guardians/guardian_broken.txt"
#define CAPTAIN_DEFAULT "./models/captain/captain_default.txt"
#define BROKEN_CAPTAIN "./models/captain/captain_broken.txt"
#define CAPTAIN_LEFT "./models/captain/captain_left.txt"
#define CAPTAIN_RIGHT "./models/captain/captain_right.txt"
#define CAPTAIN_WIDTH 6
#define MINION_DEFAULT "./models/minion/minion_default.txt"
#define MINION_LEFT "./models/minion/minion_left.txt"
#define MINION_RIGHT "./models/minion/minion_right.txt"
#define PLAYER "./models/player/player_default2.txt"
#define BROKEN_PLAYER1 "./models/player/player_broken.txt"
#define BROKEN_PLAYER2 "./models/player/player_broken2.txt"
#define BACKGROUND01 "./models/background/stars01.txt"
#define BACKGROUND02 "./models/background/stars02.txt"
#define BULLET "./models/bullet/bullet.txt"
#define BOMB "./models/bullet/bomb.txt"
#define LAUNCHER "./models/background/launcher.txt"
#define GAMEOVER "./models/background/gameover.txt"
#define WIN "./models/background/win.txt"
#define END "./models/background/END.txt"

// defini le "pas" qui permet d'incrementer le jeu
#define TIMECHECK \
    if ( (last_timestamp + 0.5) < timestamp()) \
    { \
        last_timestamp = timestamp(); \
        background_status = !background_status; \
        i++; \
        nb_enemies=display_update(element, enemies, false, background_status, difficulty, score, life); \
        update_enemies(enemies, i, difficulty); \
        int new=bomb_update(element, enemies, shot, background_status, difficulty, score, life, bomb); \
        if(new==1) bomb=next_bomb(enemies, nb_enemies, bomb); \
    } \

#define clear() printf("\033[H\033[J")
#define color(param) printf("\033[%sm",param) // colors: {30:37} = { black, red, green, yellow, blue, magenta, cyan, white}

        
typedef struct player player;
struct player
{
    int HP;
    int posX;
    int posY;
    bool is_dead;
};

typedef struct Enemies Enemies;
struct Enemies
{
	char name;
    int HP;
    int posX;
    int posY;
    int model; // D:1 - E:2 - W:3
    int speed;
    int direction;
    bool is_dead;
    struct Enemies *next;
};
 
typedef struct bullet bullet;
struct bullet
{
    int posX;
    int posY;
    int speed;
    bullet *next;
};
