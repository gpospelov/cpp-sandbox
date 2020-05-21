clang++ -std=c++2a -fmodules-ts --precompile -x c++-module -Xclang -fmodules-embed-all-files \
-Xclang -fmodules-codegen -Xclang -fmodules-debuginfo -o helloworld.pcm helloworld.mxx

clang++ -std=c++2a -fmodules-ts -o helloworld.pcm.o -c helloworld.pcm

clang++ -std=c++2a -fmodules-ts -x c++ -o hello.o -fmodule-file=helloworld.pcm -c helloworld.cpp

clang++ -std=c++2a -fmodules-ts -x c++ -o main.o -fmodule-file=hello=helloworld.pcm -c main.cpp

clang++ -o hello helloworld.pcm.o main.o hello.o
