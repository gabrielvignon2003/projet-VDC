# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= 

ifeq ($(OS),Windows_NT)
    MAIN	:= main.exe
    SOURCEDIRS	:= $(SRC)
    INCLUDEDIRS	:= $(INCLUDE)
    LIBDIRS		:= $(LIB)
    SFML_INCLUDE := -I"C:/SFML/include"
    SFML_LIB := -L"C:/SFML/lib"
    SFML_LINK := -lsfml-graphics -lsfml-window -lsfml-system
    FIXPATH = $(subst /,\,$1)
    RM		:= del /q /f
    MD		:= mkdir
else
    MAIN	:= main
    SOURCEDIRS	:= $(shell find $(SRC) -type d)
    INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
    LIBDIRS		:= $(shell find $(LIB) -type d)
    SFML_INCLUDE := -I/usr/include
    SFML_LIB := -L/usr/lib
    SFML_LINK := -lsfml-graphics -lsfml-window -lsfml-system
    FIXPATH = $1
    RM		:= rm -f
    MD		:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%)) $(SFML_INCLUDE)

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%)) $(SFML_LIB) $(SFML_LINK)

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))

# define the C object files
OBJECTS		:= $(SOURCES:.cpp=.o)

# define the dependency output files
DEPS		:= $(OBJECTS:.o=.d)

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LIBS)

# include all .d files
-include $(DEPS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(call FIXPATH,$(DEPS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!
