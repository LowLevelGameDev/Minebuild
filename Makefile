CCP = g++
SC = glslc

LIBS = -lpolygl -lvulkan -lglfw
INCLS = -I./ -I./shared

VERT_SHADERS_SRC = $(shell find ./client/shaders -name '*.vert')
VERT_SHADERS = $(VERT_SHADERS_SRC:.vert=.vert.spv)
FRAG_SHADERS_SRC = $(shell find ./client/shaders -name '*.frag')
FRAG_SHADERS = $(FRAG_SHADERS_SRC:.frag=.frag.spv)

SRCS = $(shell find ./client ./server ./safe_server ./setup ./shared -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)

all: minebuild ${VERT_SHADERS} ${FRAG_SHADERS}

%.vert.spv: %.vert
	${SC} $< -o $@

%.frag.spv: %.frag
	${SC} $< -o $@

%.o: %.cpp
	${CCP} -c ${LIBS} ${INCLS} -o $@ $<

minebuild: ${OBJS}
	${CCP} ${LIBS} ${INCLS} -o $@ $^

clean:
	rm client/*.o server/*.o safe_server/*.o setup/*.o shared/*.o
