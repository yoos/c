default: count

count:
	g++ main.cpp hashmap.cpp -I. -o count

clean: count
	rm count

