# $@ name of the target
# $* stem

OBJS=rt.o color.o ray.o elem.o cam.o ga.o ioga.o

main: main.o $(OBJS)
	g++ -o $@ $^ -lSDL -pg
	
test: test.o ${OBJS}
	g++ -o $@ $^ -lSDL

${OBJS} main.o test.o: %.o: %.cpp
#	g++ -c -o $@ $< -I./boost -std=c++0x -ffast-math
	g++ -c -o $@ $< -I./boost -mfpmath=sse -msse4 -O3  -march=native -std=c++0x -pg
	
# -pg
	
	
clean:
	rm -f main test *.o


