CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = slm
SRCDIR = src
OBJS = main.o model.o textgen.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: $(SRCDIR)/main.cpp $(SRCDIR)/model.hpp $(SRCDIR)/textgen.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp

model.o: $(SRCDIR)/model.cpp $(SRCDIR)/model.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/model.cpp

textgen.o: $(SRCDIR)/textgen.cpp $(SRCDIR)/textgen.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/textgen.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean

