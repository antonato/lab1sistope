# variables
SRC = src
OBJ = obj

# encapsulamiento
SOURCES := $(wildcard $(SRC)/*.c)

OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

.PHONY: clean all debug

# compilacion
all: $(OBJECTS)
	echo "Generando ejecutable..."
	gcc $^ $(OPTIONS) -o lab1


$(OBJ)/%.o: $(SRC)/%.c
	@echo "Generando archivos object de $@ ...."
	gcc -I$(SRC) $(OPTIONS) -c $< -o $@ 


# modo debug
debug: OPTIONS := -DDEBUG
debug: all


clean :
	-rm -rfv $(OBJ)/*.o