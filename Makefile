default: count

count:
	g++ main.cpp -o count

clean: count
	rm count

