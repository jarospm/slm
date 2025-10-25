CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = slm
SRCDIR = src
OBJS = main.o model.o generation.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: $(SRCDIR)/main.cpp $(SRCDIR)/model.hpp $(SRCDIR)/generation.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp

model.o: $(SRCDIR)/model.cpp $(SRCDIR)/model.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/model.cpp

generation.o: $(SRCDIR)/generation.cpp $(SRCDIR)/generation.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/generation.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean

