Projet réalisé par Guillaume PARIS 3A/I 30 2020

Fichiers sources contenus dans l'archive:

	Makefile

	bullet.h
	entities.h
	macro_types.h
	space_invaders.h

	space_invaders.c

	models/player/player_default2.txt
	models/background/win.txt
	models/background/stars01.txt
	models/background/launcher.txt
	models/background/stars02.txt
	models/background/gameover.txt
	models/background/END.txt
	models/captain/captain_right.txt
	models/captain/captain_left.txt
	models/captain/captain_default.txt
	models/minion/minion_right.txt
	models/minion/minion_left.txt
	models/minion/minion_default.txt
	models/guardians/captain_right.txt
	models/guardians/guardian_default.txt
	models/guardians/captain_left.txt
	models/leviathan/leviathan_default.txt
	models/bullet/bullet.txt

Lancement du programme:

	commande make à executer dans le repertoire ou les fichiers de l'archive sont extraits.

Interactions avec le jeu:

	Premier ecran: choix de la difficulte, si le caractere tape n'est ni e, ni g, ni h, la difficulte choisie par defaut est "Easy"
	Deuxieme ecan: Jeu. Vous pouvez aller a gauche avec q, droite avec d, tirer un missile avec z et quitter avec echap.
	Troisieme ecran: fin du jeu, vous pouvez choisir de rejouer en tapant y, ou de quitter (par defaut) avec n ou n'importe qu'elle autre touche.

Gameplay:

	On gagne 10 points par vaisseau touche et on en perd deux si le coup est manque.
	Un vaisseau est detruit selon son niveau de blindage. Du plus simple au plus blindé, nombre de coups necessaire: 1, 2, 4 et 5. Si l'apparence de l'ennemi change alors il ne lui reste plus que la moitié de sa vie.
	Le jeu est gagne si tous les enemis sont morts.
	Vous perdez si un vaisseau enemi ou un missile vous touche et votre score retombe à 0 si il vous reste au moins une vie.
	Si un enemi vivant atteint le bas de l'écran, vous perdez aussi.

	Modes de jeu:
		Easy: 2*10 minions, 2*8 captains, 4 guardians, 1 leviathan, speed=1, life=3
		Gradual: 4*12 minions, 3*10 captains, 6 guardians, 1 leviathan, speed=1 puis augmente petit a petit, life=3
		Hard: 4*12 minions, 3*10 captains, 6 guardians, 1 leviathan, speed=2, life=1
		
		Le mode Gradual correspond peut etre plus a un niveau intermediaire parce qu'il n'est pas infini.

Commentaires (problemes):

	Programme edite avec gedit et teste sous environnement linux (Ubuntu) sur un écran de 17 pouces.

	Problemes au niveau du deplacement des enemis non resolu, je ne comprends toujours pas comment y remedier.
	Impossible de tirer plusieurs missiles en même temps car on utilise la methode sleep et donc cela implique d'eviter de spammer ou de maintenir la touche de tir svp.
	Il y a plein d'autres aspects du gameplay qui peuvent être genant pour l'utilisateur et qui meriteraient d'etre ameliores: 
	Le plus difficile ayant ete la mise en mouvement des differents elements, je pense que mon plus gros point d'amelioration est d'arriver a fluidifier le jeu et les interacions, notamment en les rendant plus independantes (notamment faire bouger les vaisseaux separement).












