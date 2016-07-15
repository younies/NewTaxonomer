//
//  YRJ.cpp
//  building_vectors
//
//  Created by Younies Mahmoud on 7/15/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "YRJ.hpp"


YRJ::YRJ(string path_to_file)
{
    this->path_to_file = path_to_file;
    ifstream fileStream(path_to_file);
    fileStream.read( (char *)&this->kmerLength  , sizeof(LONG));
    fileStream.read( (char *) &this->numOfKmers , sizeof(LONG));
    this->kmersVector = new LONG [this->numOfKmers];
    
    fileStream.read(kmersVector, this->numOfKmers * sizeof(LONG));
    
    fileStream.close();
}




bool YRJ::isKmerExist(LONG kmer)
{
    return binary_search(kmersVector.begin(), kmersVector.end(), kmer);
}





vector<LONG> YRJ::getRandomSamples(string file_path , LONG numOfSamples)
{
    
    vector<LONG> samples(numOfSamples);
    ifstream fileStream(file_path);
    string line;
    LONG indx;
    LONG pointer = 0;
    while (getline(fileStream, line))
    {
        stringstream ss(line);
        ss >> indx;
        samples[pointer++] = this->kmersVector[indx];
    }
    fileStream.close();
    
    return samples;
}





/*

LONG YRJ::getRandomSamples(vector<LONG> &samples , LONG numOfSamples)
{
    if (numOfSamples > this->numOfKmers)
    {
        numOfSamples = this->numOfKmers;
        samples = this->kmersVector;
        return numOfSamples;
    }
    
    
    
    
    
}
*/





