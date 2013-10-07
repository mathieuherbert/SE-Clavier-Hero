#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <Applications/Hello/Hello.h>


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Ecran ecran;
	Hello hello;

	/** Test de l'affichage **/
	/*** Affichage de chaines testant la prise en compte du défilement et '\n' ***/

	// Question 2 : Effacer l'Ecran

	hello.SetEcran(&ecran);
	hello.Message();

	while(true);
}
