PLUGIN_GCC=~/avr/install/bin/avr-gcc
GCC=gcc

PLUGIN_SOURCE_FILES= plugin.cc
PLUGIN_OBJECT_FILES= $(patsubst %.cc,%.o,$(PLUGIN_SOURCE_FILES))
GCCPLUGINS_DIR:= $(shell $(PLUGIN_GCC) -print-file-name=plugin)
CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include -I~/code/git/gcc/gcc -fPIC -O2

plugin.o : plugin.cc graph.h
	$(GCC) $(CXXFLAGS) plugin.cc -c -o plugin.o

plugin.so : plugin.o
	$(GCC) -shared $^ -o $@ -lstdc++

all : plugin.so

clean : 
	rm -rf plugin.so plugin.o
