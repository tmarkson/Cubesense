

C:\MinGW\bin\g++ -c -DBUILDING_EXAMPLE_DLL dll_test1.cpp >r2.txt 2>&1

C:\MinGW\bin\g++ -shared -o dll_test1.dll dll_test1.o -Wl,--out-implib,dll_test1.a >r3.txt 2>&1
