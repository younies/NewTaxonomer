import re
import os


path_names = "/export/project/hondius/yr_db/Viruses/names2.txt"
path_to_database = "/export/project/hondius/newProject/genomesDatabase/"


file_names = open(path_names , 'r')
names = file_names.read()
names = names.split('\n')


for name in names:
	uid = re.findall(r'uid[0-9]*/', name)
	if(not uid):
		print name
		continue
	uid = uid[0]
	uid = uid[ 3 : -1 ]
	os.system("cat " + name + " >> " + path_to_database + uid + ".fa")


file_names.close()
