#makefile

a.out: trees.o tree-node.o
	g++ trees.o tree-node.o

trees.o: trees.cpp tree-node.h
	g++ -c trees.cpp

tree-node.o: tree-node.cpp tree-node.h
	g++ -c tree-node.cpp
