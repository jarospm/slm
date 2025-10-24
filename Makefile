CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = slm
SRCDIR = src
OBJS = main.o training.o generation.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: $(SRCDIR)/main.cpp $(SRCDIR)/training.hpp $(SRCDIR)/generation.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp

training.o: $(SRCDIR)/training.cpp $(SRCDIR)/training.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/training.cpp

generation.o: $(SRCDIR)/generation.cpp $(SRCDIR)/generation.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/generation.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean

