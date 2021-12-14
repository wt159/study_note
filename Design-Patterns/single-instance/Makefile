example1: main.cpp hello.so
    $(CXX) $(CXXFLAGS) -o example1 main.cpp -ldl
hello.so: hello.cpp
    $(CXX) $(CXXFLAGS) -shared -o hello.so hello.cpp
clean:
    rm -f example1 hello.so
.PHONY: clean