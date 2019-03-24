gcc -Wall -I . -c fileManager.c dot_sequential.c
gcc -Wall -I . -o sequential.out *.o
rm *.o
