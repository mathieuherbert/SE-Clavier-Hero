OS=$(shell uname)
COMPILATEUR=CPP_$(OS)
LIEUR=LD_$(OS)

#-------------------
##Pour Mac
CPP_Darwin=i386-elf-g++-4.3.2
LD_Darwin=i386-elf-ld

#-------------------
##Pour Linux
CPP_Linux=g++
LD_Linux=ld
#CPPFLAGS  = -gdwarf-2 -g3 -Wall -fno-builtin -fno-rtti -fno-exceptions -nostdinc 
#LDFLAGS = --warn-common -nostdlib 

#-------------------
##POUR WINDOWS
CPP_WindowsNT=g++
LD_WindowsNT=ld
 
#-------------------
## Partie commune a toutes les configurations

CPPFLAGS  = -gdwarf-2 -g3 -Wall -fno-builtin -fno-rtti -fno-exceptions -nostdinc
LDFLAGS = --warn-common -nostdlib 

PWD :=.
DELE = rm
MV = mv -f


KERNEL_OBJ   = sextant.elf

# Main target
all: $(KERNEL_OBJ)


OBJECTS = 	hal/multiboot.o							\
			Applications/Hello/Hello.o				\
	  		drivers/Ecran.o  						\
	  		sextant/main.o
	  		
OBJ_FILES = $(wildcard build/all-o/*.o)

$(KERNEL_OBJ): $(OBJECTS)
	echo 'Votre compilateur $(COMPILATEUR) et votre lieur $(LIEUR)'
	$($(LIEUR)) $(LDFLAGS) -T ./support/sextant.lds -o build/boot/$@ $(OBJ_FILES)

# Create objects from C source code
%.o: %.cpp
	$($(COMPILATEUR)) -I$(PWD) -c $< $(CPPFLAGS) -o $@
	$(MV) $@ build/all-o
	
# Create objects from assembler (.S) source code
%.o: %.S
	$($(COMPILATEUR)) -I$(PWD)  -c $< $(CPPFLAGS) -DASM_SOURCE=1 -o $@
	$(MV) $@ build/all-o


# Clean directory
clean:
	$(DELE) -rf build/all-o/*.o
	$(REM) -f *.s
	$(REM) -f build/boot/*.elf
	