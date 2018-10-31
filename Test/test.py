import matplotlib.pyplot as plt 
import random,os


def insertTest():
	
	i=10001
	j=0
	f = open("insert.txt","w+")
	f.write(str(i)+"\n")
	while j<i-1:
		f.write(str(1)+"\n")
		f.write(str(long(random.uniform(1,1000000000)))+"\n")
		j=j+1
	
	f.write(str(4)+"\n")
	f.close()
	cmd = "./splay.out < insert.txt"
	os.popen(cmd).read()
	cmd1 = "./AVL.out < insert.txt"
	os.popen(cmd1).read()
		
	x=os.popen("diff test_inorder_splay.txt test_inorder_avl.txt").read()
	if x == "":
		return 1
	else:
		return 0


def searchTest():
	
	i=20000
	j=0
	f = open("insert.txt","w+")
	f.write(str(i)+"\n")
	set_1 = []
	while j<i/2:
		f.write(str(1)+"\n")
		tmp = long(random.uniform(1,1000000000))
		set_1.append(tmp)
		f.write(str(tmp)+"\n")
		j=j+1
	
	while j<i:
		f.write(str(3)+"\n")
		if j%2==0:
			tmp = random.choice(set_1)
		else:
			tmp = long(random.uniform(1,1000000000))
		f.write(str(tmp)+"\n")
		j=j+1

	f.close()
	cmd = "./splay.out < insert.txt"
	os.popen(cmd).read()
	cmd1 = "./AVL.out < insert.txt"
	os.popen(cmd1).read()
		
	x=os.popen("diff test_search_splay.txt test_search_avl.txt").read()
	if x == "":
		return 1
	else:
		return 0

def deleteTest():
	i=20000
	j=0
	f = open("insert.txt","w+")
	f.write(str(i)+"\n")
	set_1 = []
	while j<i/2:
		f.write(str(1)+"\n")
		tmp = long(random.uniform(1,1000000000))
		set_1.append(tmp)
		f.write(str(tmp)+"\n")
		j=j+1
	
	while j<i:
		f.write(str(2)+"\n")
		if j%2==0:
			tmp = random.choice(set_1)
		else:
			tmp = long(random.uniform(1,1000000000))
		f.write(str(tmp)+"\n")
		j=j+1

	f.close()
	cmd = "./splay.out < insert.txt"
	os.popen(cmd).read()
	cmd1 = "./AVL.out < insert.txt"
	os.popen(cmd1).read()
		
	x=os.popen("diff test_delete_splay.txt test_delete_avl.txt").read()
	if x == "":
		return 1
	else:
		return 0

cmd = "g++ splaytree.cpp -o splay.out"
os.system(cmd)
cmd1 = "g++ AVL.cpp -o AVL.out"
os.system(cmd1)

y=insertTest()
if y == 1:
	print "Inorder TestCase Passed"
else:
	print "Inorder TestCase Failed"
y=searchTest()
if y == 1:
	print "Search TestCase Passed"
else:
	print "Search TestCase Failed"

y=deleteTest()
if y == 1:
	print "Delete TestCase Passed"
else:
	print "Delete TestCase Failed"