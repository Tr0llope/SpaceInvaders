#############################################################################
# Fichier Makefile
# Project in C - ESIEA - 2021
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'\E9dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = space_invaders


#############################################################################
# definition des regles
#############################################################################

########################################################
# la regle par defaut
all : $(EXECUTABLES)

########################################################
# regle generique :
#  remplace les regles de compilation separee de la forme
#       module.o : module.c module.h
#               $(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

space_invaders.o : space_invaders.c space_invaders.h entities.h bullet.h macro_types.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module space_invaders"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $< 


########################################################
# regles explicites de creation des executables

space_invaders : space_invaders.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le repertoire
clean:
	rm -fR $(EXECUTABLES) *.o
	
# regle pour archiver le projet
zip:	
	rm -fR $(EXECUTABLES) *.o
	zip -r space_invaders_Guillaume_PARIS.zip *

