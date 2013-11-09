# $@ name of the target
# $* stem

# 
# CPPFLAGS=-O0 -g3 -ggdb -mfpmath=sse -msse4 -march=native -std=c++0x 
CPPFLAGS=-O3 -mfpmath=sse -msse4 -march=native -std=c++0x 
# CPPFLAGS=-O3 -mfpmath=sse -msse4 -march=native -std=c++0x -pg

OBJS=rt.o color.o ray.o elem.o cam.o ga.o ioga.o aabb.o

main: main.o $(OBJS)
	g++ -o $@ $^ -lSDL
	# -pg
	
test: test.o ${OBJS}
	g++ -o $@ $^ -lSDL

${OBJS} main.o test.o: %.o: %.cpp
	g++ -c -o $@ $< -I./boost ${CPPFLAGS}
			
clean:
	rm -f main test *.o


