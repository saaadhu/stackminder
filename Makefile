PLUGIN_GCC=~/avr/mingw/install/bin/avr-gcc
GCC=i486-mingw32-g++

PLUGIN_SOURCE_FILES= plugin.cc
PLUGIN_OBJECT_FILES= $(patsubst %.cc,%.o,$(PLUGIN_SOURCE_FILES))
GCCPLUGINS_DIR:= /home/saaadhu/avr/mingw/install/lib/gcc/avr/4.7.2/plugin
CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include -I/home/saaadhu/avr/mingw/gcc-build/gmp -fPIC -O2

plugin.o : plugin.cc graph.h
	$(GCC) $(CXXFLAGS) plugin.cc -c -o plugin.o

plugin.dll : plugin.o
	$(GCC) -shared $^ -o $@ -lstdc++ -L$(GCCPLUGINS_DIR)/lib -lcc1 

all : plugin.dll

clean : 
	rm -rf plugin.dll plugin.o
