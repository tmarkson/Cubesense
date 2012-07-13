g++ -c -DBUILDING_EXAMPLE_DLL dll_test1.cpp

g++ -shared -o dll_test1.dll dll_test1.o -Wl,--out-implib,dll_test1.a