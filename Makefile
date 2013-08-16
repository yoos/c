SRCS = hashmap.cpp

default: count test

count: test
	g++ main.cpp $(SRCS) -I. -o count

test:
	g++ test.cpp $(SRCS) -I. -o test

clean:
	rm test count

