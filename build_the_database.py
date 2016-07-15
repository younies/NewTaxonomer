#!/usr/bin/python
"""
this program is going to call every thing and build the data base and taking only as argument how long of the kmers that you want
"""
import os
import sys
import subprocess


##some configuration variables:

path_to_the_program = "/export/project/hondius/newProject/"
name_of_genomes_database = "genomesDatabase"




if len(sys.argv) < 2:
	print "Usage: ./program_name <number of the kmers>"
	exit()
else:
	kmer = int(sys.argv[1])
	kmer_databaseName = 'kmerDatabase' + str(kmer)



##make the kmer database directory

make_directory = subprocess.Popen(['mkdir', path_to_the_program + kmer_databaseName], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

out , err = make_directory.communicate()

if not err:
	print "making the directory for the kmer database done!"
else:
	print err
	print "failed to build the kmer directory!"



## to get the names of all the fasta files in the database
namesOrder =  subprocess.Popen(['ls' , path_to_the_program + name_of_genomes_database  ], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

names , err = namesOrder.communicate()
names = names.split('\n')


if not err:
	print "getting the names succeded !"
else:
	print err
	print "failed to get the names"


full_names = []
for name in names:
	name = path_to_the_program + name_of_genomes_database + '/' + name
	full_names.append(name)


print full_names[0]
##for building all the data base

all_database_name = path_to_the_program + kmer_databaseName + '/all.jf'
"""
building_all = subprocess.Popen(['jellyfish', 'count' , '-m' , str(kmer) , '-s' , '10000M' , '-C' , '-o' , all_database_name ] + full_names, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

out , err = building_all.communicate()
if not err:
	print "all the data base built ...... succeed"
else:
	print err
	print "faiuled to build all the database"
	exit()

"""


## building the kmers for the database

name_of_fasta_all = path_to_the_program + kmer_databaseName + '/all.fa'

print all_database_name
print name_of_fasta_all

#building_all_fasta = subprocess.Popen(['jellyfish', 'dump' , all_database_name , '>' , name_of_fasta_all], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

err = os.system( "jellyfish dump " + all_database_name + " > " + name_of_fasta_all)
#out , err = building_all_fasta.communicate()
if not err:
	print "fasta for akmers is buit ..... done!"
else:
	print err
	print "failed to build the all kmers fasta file"








