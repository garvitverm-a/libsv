OUTDIR := make_out
LIBRARY_NAME := sv
LIBRARY := lib$(LIBRARY_NAME).a

ifdef NDEBUG
MODE := -DNDEBUG -O3
else
MODE := -g -DDEBUG
SANITIZE := -fsanitize=address
endif

CXXFLAGS := -Wall -Wextra -Werror $(MODE) $(SANITIZE)
EXAMPLEFLAGS := -I$(OUTDIR)/include -L$(OUTDIR)/lib -l$(LIBRARY_NAME) -g $(SANITIZE)

SOURCES := sv.cpp
OBJECTS := sv.o
HEADERS := sv.h

EXAMPLEDIR := examples
EXAMPLESOURCES := $(wildcard $(EXAMPLEDIR)/*.cpp)
EXAMPLEBINS := $(patsubst $(EXAMPLEDIR)/%.cpp,$(OUTDIR)/examples/%,$(EXAMPLESOURCES))

all: $(LIBRARY) examples

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) $(OBJECTS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

install: install_out clean_lib clean_objects

install_out: $(HEADERS) $(LIBRARY)
	mkdir -p $(OUTDIR)/{include,lib}
	cp $(HEADERS) $(OUTDIR)/include
	cp $(LIBRARY) $(OUTDIR)/lib

examples: install example_step $(EXAMPLEBINS)

example_step:
	mkdir -p $(OUTDIR)/examples

$(OUTDIR)/examples/%: $(EXAMPLEDIR)/%.cpp
	$(CXX) $< -o $@ $(EXAMPLEFLAGS)

clean: clean_objects clean_lib clean_out

clean_objects:
	rm -f *.o

clean_lib:
	rm -f *.a
	rm -f *.dylib
	rm -f *.so

clean_out:
	rm -rf make_out/

.PHONY: all install examples clean
