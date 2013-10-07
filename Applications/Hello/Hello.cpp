/*
 * Hello.cpp
 *
 *  Created on: 26 août 2008
 *      Author: jmenaud
 */

#include "Hello.h"

void Hello::SetEcran(Ecran *ecran) {
	ec=ecran;
};

void Hello::Message() {
	(*ec).effacerEcran(NOIR);
	(*ec).afficherMot("Bienvenue a toi, petit terrien !\n",JAUNE);
};
