#include "Ecran.h"

// Ici nous allons manipuler un tableau ecran dont on fixe l'origine au d�but de la zone m�moire video.

volatile caseEcran* Ecran::origine = (volatile caseEcran*)VIDEO;

unsigned char Ecran::coderCouleur(Couleur c) {
	unsigned char r;
	switch(c){
	case NOIR:
		r = 0;
		break;
	case GRIS_SOMBRE:
		r = 8;
		break;
	case BLEU:
		r = 1;
		break;
	case BLEU_LEGER:
		r = 9;
		break;
	case VERT:
		r = 2;
		break;
	case VERT_LEGER:
		r = 10;
		break;
	case CYAN:
		r = 3;
		break;
	case CYAN_LEGER:
		r = 11;
		break;
	case ROUGE:
		r = 4;
		break;
	case ROUGE_LEGER:
		r = 12;
		break;
	case MAGENTA:
		r = 5;
		break;
	case MAGENTA_LEGER:
		r = 13;
		break;
	case MARRON:
		r = 6;
		break;
	case JAUNE:
		r = 14;
		break;
	case GRIS_LEGER:
		r = 7;
		break;
	case BLANC:
		r = 15;
		break;
	}
	return r;
}

unsigned char Ecran::coderAttribut(Couleur prPlan, Couleur arPlan,int clign) {
	unsigned char paramClignotement ;

	if (clign== CLIGN_OUI) paramClignotement=1; else paramClignotement=0;

	unsigned char codePremierPlan = coderCouleur(prPlan);
	unsigned char codeArrierePlan = coderCouleur(arPlan);
	return ( codePremierPlan | (codeArrierePlan << 4) | (paramClignotement << 7));
}

unsigned char Ecran::coderAttribut(Couleur prPlan, Couleur arPlan) {
	unsigned char paramClignotement = 0 ;

	unsigned char codePremierPlan = coderCouleur(prPlan);
	unsigned char codeArrierePlan = coderCouleur(arPlan);
	return ( codePremierPlan | (codeArrierePlan << 4) | (paramClignotement << 7));
}

// Les accesseurs

int Ecran::getLigne(){
	return ligne;
}

int Ecran::getColonne(){
	return colonne;
}

void Ecran::setLigne(int i){
	 ligne=i;
}

void Ecran::setColonne(int i){
	 colonne=i;
}

int Ecran::positionCourrante(){
	return getLigne() * COLONNES + getColonne();
}

void Ecran::avancerPositionCourrante(){
	int c = getColonne();
	int l = getLigne();
	c=c+1;
	if(c >=COLONNES){//hors de l'�cran, trop � droite
		c = 0;
		l++;
		if(l>=LIGNES){//hors de l'�cran, trop bas
			defilement(1);
			l--;
		}
	}
	setColonne(c);
	setLigne(l);
}

void Ecran::sautDeLigne(){
	int c = getColonne();
	int l = getLigne();

	c=0;
	l=l+1;

	if(l>=LIGNES){//hors de l'�cran, trop bas
			defilement(1);
			l--;
		}
	setColonne(c);
	setLigne(l);
}

// Partie fonctionnelle



// Efface l'ecran avec pour couleur de fond arPlan

void Ecran::effacerEcran(Couleur arPlan) {
	arrierePlan = arPlan;
	unsigned char attribut = coderAttribut(arrierePlan, arrierePlan);
	for(int i = 0 ; i < LIGNES*COLONNES ; i++){
		origine[i].caractere = 0;
		origine[i].couleurs = attribut;
		setLigne(0);
		setColonne(0);
	}
}

// Affiche un Caractere a la position courrante



void Ecran::afficherCaractere(Couleur prPlan,Couleur arPlan,const char caractere) {

	afficherCaractere(getLigne(),getColonne(), prPlan, arPlan, caractere);
	avancerPositionCourrante();
}

// Affiche un Caractere a la position donn�e en parametre (l,c)

void Ecran::afficherCaractere(int l,int c,Couleur prPlan,Couleur arPlan,const char caractere) {
	unsigned char attribut = coderAttribut(prPlan, arPlan);

	//Si en dehors de l'�cran, ne rien faire
	if ((c >=COLONNES) || (l >= LIGNES)) return;

	int position = l * COLONNES + c; // position lineaire relative

	origine[position].caractere = caractere;
	origine[position].couleurs = attribut;
}

// Affiche une chaine de caractere a la position courante

void Ecran::afficherMot(const char *mot,Couleur prPlan) {
	int i=0;

	while(mot[i]!='\0'){ // '\0' : caract�re de fin
		if(mot[i] == '\n'){ // '\n' : passage � la ligne
			sautDeLigne();
		}else
			afficherCaractere(prPlan,arrierePlan, mot[i]);
		i++;
	}
	//afficherCurseur();
}

// Affiche le curseur (mais la postion courante ne change pas)

void Ecran::afficherCurseur(){
	int position = positionCourrante();

	unsigned char attribut = coderAttribut(BLANC, arrierePlan,CLIGN_OUI);
	origine[position].caractere = CURSEUR;
	origine[position].couleurs = attribut;

}

// gere le d�filement de nline d'un coup. les nouvelles lignes ont pour fond la couler de fond courante

void Ecran::defilement(int nline) {
}




void Ecran::afficherChiffre( const int valeur){
}

