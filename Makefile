PLUGIN_GCC=~/avr/install/bin/avr-gcc
GCC=~/native/install/bin/gcc
PLUGIN_SOURCE_FILES= plugin.cc
PLUGIN_OBJECT_FILES= $(patsubst %.cc,%.o,$(PLUGIN_SOURCE_FILES))
GCCPLUGINS_DIR:= $(shell $(PLUGIN_GCC) -print-file-name=plugin)
CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include -I~/code/git/gcc/gcc -fPIC -O2

plugin.so: $(PLUGIN_OBJECT_FILES)
	$(GCC) -shared $^ -o $@ -lstdc++

