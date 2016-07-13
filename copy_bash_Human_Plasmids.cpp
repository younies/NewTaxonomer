//
//  main.cpp
//  build_database
//
//  Created by Younies Mahmoud on 7/8/16.
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

using namespace std;

vector<pair<int, int> > giIdMapper;

int mapsize = 562270495;



void build_the_mapper(string filePath , int file_size);
int strTolong(string s);
int gi_to_tax(int gi , int mapp_size);
int first_line_to_taxId(string line);
int get_first_line(string path);


vector<string> getFileNames(string names_path);

int main(int argc, const char * argv[]) {
    // insert code here...
    string file_path_gi = "/export/project/hondius/yr_db/taxogi/gi_taxid_nucl.dmp";
    string path_to_data = "/export/project/hondius/yr_db/";
    string path_to_database = "/export/project/hondius/newProject/genomesDatabase/";
    string path_to_bash = "/export/project/hondius/newProject/NewTaxonomer/copyHumanPlasmids.sh";
    vector<string> folders;
//    folders.push_back("Bacteria");
   folders.push_back( "Human"); 
  //  folders.push_back( "Viruses");
     folders.push_back(  "Plasmids" );
    string name_of_names_file = "names2.txt";
    
    build_the_mapper(file_path_gi, mapsize);
    
    ofstream output_bash(path_to_bash);
    output_bash << "#!/bin/bash \n\n";
    
    
    for (int i = 0 , n = (int)folders.size(); i < n ; ++i)
    {
	string transPath = path_to_data + folders[i] +"/"+ name_of_names_file ;
	cerr << transPath << endl; 
        vector<string> names = getFileNames( transPath);
        int taxId;
        for (int j = 0 , m = (int)names.size(); j < m ; ++j)
        {
            taxId = get_first_line(names[j]);
            string command = "cat  "  + names[j] + "   >>  " + path_to_database + to_string(taxId) + ".fa  " ;
            output_bash << command << "\n";
        }
    }
    
    
    
    return 0;
}



void build_the_mapper(string filePath , int file_size)
{
    //open the gi_to_idx file
    ifstream gi_file(filePath);
    
    if(!gi_file.is_open())
    {
        cerr << "the gi_to_id file doesnot exist \n";
        return;
    }
    
    string line;
    int gi;
    int taxId;
    int pointer = 0;
    giIdMapper.resize(file_size);
    
    while (getline(gi_file, line))
    {
        pointer++;
        stringstream liness(line);
        liness >> gi;
        liness >> taxId;
        giIdMapper[pointer].first = gi;
        giIdMapper[pointer].second = taxId;
        
    }
    
    gi_file.close();
    if(pointer != file_size  - 1)
        cerr << "pointer not != and  " << pointer << "  " << file_size << endl;
}




int gi_to_tax(int gi , int mapp_size)
{
    int first = 0;
    int last = mapp_size - 1;
    int mid;
    while (last >= first)
    {
        mid = (first + last) / 2;
        if(giIdMapper[mid].first == gi)
            return giIdMapper[mid].second;
        else if(giIdMapper[mid].first > gi)
            last = mid - 1;
        else
            first = mid + 1;
    }
    return -1;
}



int first_line_to_taxId(string line)
{
    stringstream liness(line);
    getline(liness, line, '|');
    getline(liness, line, '|');
    stringstream liness2(line);
    int gi;
    liness2 >> gi;
    
    
    return gi_to_tax(gi , mapsize );

}



int get_first_line(string path)
{
    //open the fasta file
    ifstream fasta_file(path);
    
    if(!fasta_file.is_open())
    {
        cerr << "the fasta file doesnot exist \n";
        return -1;
    }
    
    string line;
    getline(fasta_file, line);
    
    fasta_file.close();
    return  first_line_to_taxId( line);

}


vector<string> getFileNames(string names_path)
{
    vector<string> ret;
    string line;
    ifstream names_file(names_path);
    
    while (getline(names_file, line))
    {
        ret.push_back(line);
    }
    
    names_file.close();
    
    return ret;
}






