//
//  main.cpp
//  building_vectors
//
//  Created by Younies Mahmoud on 7/15/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "headers.h"
#include "YRJ.hpp"


int main(int argc, const char * argv[])
{
   /* LONG numberOfSamples , kmerLength;
    string path_to_database , name_of_database = "kmerDatabase";
    
    string path_to_ten_unique_rand = "/export/project/hondius/yr_db/for_garbages/tenMillionRandom.txt";
    
    if(argc < 4)
    {
        cout << "Usage:: enter the number of sampling , the kmer size and the path to the database \n";
        return 1;
    }
    else
    {
        stringstream sampling(argv[1]);
        sampling >> numberOfSamples;
        
        stringstream kmerLS(argv[2]);
        kmerLS >> kmerLength ;
        
        path_to_database = argv[3];
    }
    
    */
    
    string path_to_ten_unique_rand = "/export/project/hondius/yr_db/for_garbages/tenMillionRandom.txt";
    
    string path_to_container = "/export/project/hondius/newProject/kmerDatabase31/";
    string path_to_all = "/export/project/hondius/newProject/kmerDatabase31/all.yrj";
    
    //for reading all the names
    LONG numOfUID = 8065;
    string path_to_names = "/export/project/hondius/newProject/namesOfFiles.txt";
    vector<string> namesOfFiles;
    ifstream namesStream(path_to_names);
    string name;
    while (getline(namesStream, name))
    {
        namesOfFiles.push_back(name);
    }
    namesStream.close();
    //end reading all the names

    YRJ all = *new YRJ(path_to_all);
    vector<LONG> samples = all.getRandomSamples(path_to_ten_unique_rand, 10000000);

    //&all.delete; I need to delete it
   // delete &all;
 //   all = NULL;
    //read all the uids
    vector<YRJ*> all_UIDs(numOfUID);
    for (int i = 0 ; i < numOfUID; ++i)
    {
        all_UIDs[i] = new YRJ(namesOfFiles[i]);
    }
    
    string path_to_result = "/export/project/hondius/newProject/result_ten_million.txt";
    ofstream os(path_to_result);
    
    
    
    for (int i = 0 , n = (int)samples.size(); i < n ; ++i)
    {
        char * c;
        int count1 = 0 , count0 = 0;
        for (int j = 0  ; j < numOfUID; ++j)
        {
            
            if(all_UIDs[j]->isKmerExist(samples[i]))
            {
                ++count1;
                *c = '1';
            }
            else
            {
                ++count0;
                *c = '0';
            }
            os.write(c, sizeof(char));
        }
        *c = '\n';
        os.write(c, sizeof(char));
        cerr << "cout0 : " << count0 << "   count1:  " << count1 << endl;
    }
    
    
    
    
    
    
    
}
