/*
 * Hello.h
 *
 *  Created on: 26 août 2008
 *      Author: jmenaud
 */

#ifndef HELLO_H_
#define HELLO_H_

#include <drivers/Ecran.h>

class Hello {
	/**
	 * Ecran pour l'affichage.
	 */
	Ecran* ec;

public :

	void SetEcran(Ecran*);

	void Message();
};


#endif /* HELLO_H_ */
