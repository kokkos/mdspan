KOKKOS_PATH = ${HOME}/Kokkos/kokkos
SRC = $(wildcard *.cpp)
KOKKOS_DEVICES=OpenMP
KOKKOS_CUDA_OPTIONS=enable_lambda
KOKKOS_ARCH = SKX,Volta70
GOOGLEBENCHMARK_PATH = /home/projects/x86-64/google/benchmark/gcc/6.1.0
KOKKOS_CXX_STANDARD=c++14

default: build
	echo "Start Build"

CXX = g++
EXE = test.host

CXXFLAGS = -O3 -g -I${GOOGLEBENCHMARK_PATH}/include -I../../../include -I.. -I../../ 
LINK = ${CXX}
LINKFLAGS = -L${GOOGLEBENCHMARK_PATH}/lib64

DEPFLAGS = -M

OBJ = $(SRC:.cpp=.o)
LIB = -lbenchmark -lbenchmark_main

include $(KOKKOS_PATH)/Makefile.kokkos

build: $(EXE)

$(EXE): $(OBJ) $(KOKKOS_LINK_DEPENDS)
	$(LINK) $(KOKKOS_LDFLAGS) $(LINKFLAGS) $(EXTRA_PATH) $(OBJ) $(KOKKOS_LIBS) $(LIB) -o $(EXE)

clean: kokkos-clean 
	rm -f *.o *.cuda *.host

# Compilation rules

%.o:%.cpp $(KOKKOS_CPP_DEPENDS)
	$(CXX) $(KOKKOS_CPPFLAGS) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) $(EXTRA_INC) -c $<
