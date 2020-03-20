strassen: strassen.o graph1_utils.o
	g++ strassen.o -o mst -std=c++11

clean:
	rm *.o strassen