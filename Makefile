EXEC = ./ostroiul

CXX = g++
CXXFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11 

DXFILE = Doxyfile

RM = rm -rf
MKDIR = mkdir -p

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)



  all: 
	make compile
	make doc


  run:
	$(EXEC) $(MAP) $(QUEST)



  compile: $(OBJS)
	   $(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) -lncurses



  doc: 
	doxygen $(DXFILE)


 
  %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@



  clean:
	$(RM) $(OBJS) $(EXEC) doc/