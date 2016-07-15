//
//  main.cpp
//  building_yj_database
//
//  Created by Younies Mahmoud on 7/14/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sysexits.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <fstream>

#define LONG long


using namespace std;


LONG convert_kmer_to_LONG(string kmer , LONG n);
int convert_to_int(char c);



int main(int argc, const char * argv[]) {
    
    //checking the good usage of the program
    if(argc < 5)
    {
        cout << "Usage: name_of_program <full path to the kmer fasta file> <the name of the fasta kmer> <file length> <kmer length>" << endl;
        return 1;
    }
    
    
    //getting the command line arguments
    string file_directory = argv[1];
    string file_name = argv[2];
    stringstream ss(argv[3]);
    LONG FileSize ;
    ss >> FileSize;
    
    
    stringstream ss2(argv[4]);
    LONG kmerSize ;
    ss2 >> kmerSize;
    
    vector<LONG> all_kemers(FileSize/2 , 0);
    
    ifstream input_file(file_directory + file_name  + ".fa", 'r');
    
    
    //to check if the file will open
    if(!input_file.is_open())
    {
        cout << "the file : " <<file_directory + file_name << " : could not be opened\n";
        return -1;
    }
    
    string tempKmer;
    LONG kmerNumbers = FileSize/2;
    for (LONG i = 0  ; i < kmerNumbers ; ++i)
    {
        getline(input_file, tempKmer );
        getline(input_file, tempKmer );
        all_kemers[i] = convert_kmer_to_LONG(tempKmer , kmerSize);
    }
    
    input_file.close();
    
    sort(all_kemers.begin(), all_kemers.end());
    
    //writing the file
    
    ofstream output_file(file_directory + file_name + ".yj");
    
    
    output_file.write( (char *) &kmerSize ,  sizeof(LONG));
    output_file.write( (char *) &kmerNumbers ,  sizeof(LONG));
    
    for (int i = 0 ; i < kmerNumbers ; ++i)
    {
         output_file.write( (char *) &all_kemers[i] ,  sizeof(LONG));
    }

    output_file.flush();
    output_file.close();
    
    
    
    
    
    return 0;
}







LONG convert_kmer_to_LONG(string kmer , LONG n) // n is the size
{
    LONG kmerBits = 0;//you have to put zeros
    int temp = 0;
    for(int i = 0 ; i < n - 1 ; ++i)
    {
        temp = convert_to_int(kmer[i]);
        kmerBits = kmerBits | temp;
        kmerBits = kmerBits << 2;
        
    }
    
    temp = convert_to_int(kmer[n - 1]);
    kmerBits = kmerBits | temp;
    return kmerBits;
}



int convert_to_int(char c)
{
    switch (c) {
        case 'A':
            return 0;
            break;
        case 'C':
            return 1;
            break;
        case 'G':
            return 2;
            break;
        case 'T':
            return 3;
            break;
            
        default:
            cerr << "the char is not A, C, G or T\n";
            break;
    }
    return -1;
}






