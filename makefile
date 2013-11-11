	
CPP_FLAGS=-mfpmath=sse -msse4 -march=native -std=c++0x 
CPP_FLAGS_RELEASE=-O3 
CPP_FLAGS_DEBUG=-O0 -g3 -ggdb 
# CPP_FLAGS_RELEASE_PROF=-O3 -pg


OBJS=rt.o color.o ray.o elem.o cam.o ga.o ioga.o aabb.o intersect.o grid.o


release: CPP_FLAGS+=${CPP_FLAGS_RELEASE}
release: main

debug: CPP_FLAGS+=${CPP_FLAGS_DEBUG}
debug: main
	
main: main.o $(OBJS)
	g++ -o $@ $^ -lSDL
	# -pg

test: CPP_FLAGS += ${CPP_FLAGS_DEBUG}
test: test.o ${OBJS}
	g++ -o $@ $^ -lSDL

${OBJS} main.o test.o: %.o: %.cpp
	g++ -c -o $@ $< -I./boost ${CPP_FLAGS}
			
clean:
	rm -f main test *.o


