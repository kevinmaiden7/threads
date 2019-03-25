gcc -Wall -I . -c fileManager.c -c dot_parallel.c -lpthread 
gcc -Wall -I . -o parallel.out *.o -lpthread
rm *.o
