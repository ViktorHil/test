#include <iostream>
#include <time.h>
#include <string>
#include <inttypes.h>
#include <array>
#include <map>
#include <unordered_map>
#include <thread>
#include <sys/time.h>
#include <vector>
#include <stdlib.h>

#define X_SIZE 320
#define Y_SIZE 240
#define COUNT_MAX 10000000

int comp (const int *i, const int *j) {
    return *i - *j;
}

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

int main( int argc, char* argv[]) {
    int mas[Y_SIZE][X_SIZE];
    for ( int i = 0; i < Y_SIZE; i++) {
	for( int j = 0; j < X_SIZE; j++) {
	    mas[i][j] = rand();
//	    mas[i][j] = (rand() % (100 - 0 + 1)) + 0;
	    std::cout << mas[i][j] << ' ';
	}
	std::cout << std::endl;
    }
    std::cout << "-------------------------------------------------------------" << std::endl;
    long long t1 = current_timestamp();
    for( int i = 0; i < Y_SIZE; i++) {
        qsort( &mas[i][0], X_SIZE, sizeof (int), (int(*) (const void *, const void *)) comp);
    }
    long long t2 = current_timestamp();

    for ( int i = 0; i < Y_SIZE; i++) {
	for( int j = 0; j < X_SIZE; j++) {
	    std::cout << mas[i][j] << ' ';
	}
	std::cout << std::endl;
    }
    std::cout << "Delay was :" << (t2 - t1) << " ms" << std::endl;
    return 0;
}


