CFLAGS= -g -Wall -Wextra 
# g++ $(CFLAGS) CSP.cpp -o CSPexec
#g++ $(CFLAGS) comparitors.cpp JSONParser.cpp CSP_copy.cpp -o CSPexec2
all:
	g++ $(CFLAGS) CSP.o -ljsoncpp -o CSPexec
