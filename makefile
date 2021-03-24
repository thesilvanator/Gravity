CC=clang
CC-ARGS=-Wall -O0
INCS=-I/usr/local/include/
LIBS=-L/usr/local/lib/ -lSDL2
FILES=main.c p_math.c planet.c render.c
EXE=gravity

default:$(EXE)

$(EXE): $(FILES)
	$(CC) $(CC-ARGS) $(INCS) $(LIBS) -o $(EXE) $(FILES)

verbose: $(FILES)
	$(CC) $(CC-ARGS) -o $(EXE) --verbose $(FILES)


run: default
	time ./$(EXE)
