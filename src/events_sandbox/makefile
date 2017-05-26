
all: opti

# Inspired from demo below.
# Phase 1: Very simple, no threading, dump output immediately.
# Phase 2: No threading, but redirect output strings to another class that will 
#          format them before outputing them.
opti: opti.cpp
	g++ opti.cpp -o opti -lboost_system -lpthread

# demo is code from StackOverflow
# Ref: http://stackoverflow.com/questions/7464025/designing-an-event-mechanism-in-c/7523319#7523319
# Used as basis example for my understanding.
demo: demo.cpp
	g++ demo.cpp -o demo -lboost_system -lpthread

clean:
	rm -f opti demo
