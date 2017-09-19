all : ques1 ques2

ques1: q1.o
	g++ q1.o -o ques1

ques2: q2.o
	g++ q2.o -o ques2

q1.o: q1.cpp
	g++ -c q1.cpp

q2.o: q2.cpp
	g++ -c q2.cpp

clean:
	rm *.o ques1 ques2

