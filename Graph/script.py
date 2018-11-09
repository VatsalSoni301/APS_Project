import matplotlib.pyplot as plt 
import random,os

inputs = [10,100,1000,10000,100000,1000000,10000000]
#inputs = [10,100,1000,10000]
def insert():
	
	y = []
	z = []
	for i in inputs:
		j=0
		f = open("insert.txt","w+")
		f.write(str(i)+"\n")
		while j<i:
			f.write(str(1)+"\n")
			f.write(str(long(random.uniform(1,1000000000)))+"\n")
			j=j+1
		
		cmd = "./splay.out < insert.txt"
		timesplay = float(os.popen(cmd).read())
		cmd1 = "./AVL.out < insert.txt"
		timeAVL = float(os.popen(cmd1).read())
		y.append(timesplay)
		z.append(timeAVL)

	line_up, = plt.plot(inputs,y, label='Splay')
	line_down, = plt.plot(inputs,z, label='AVL')
	plt.xlabel('Number Of inputs')
	plt.ylabel('Time (ms)') 
	plt.title("Insertion Graph") 
	plt.legend(handles=[line_down,line_up],loc=2)
	plt.savefig('insertion_graph.png')
	plt.show()

def delete():
	y = []
	z = []
	for i in inputs:
		j=0
		f = open("delete.txt","w+")
		f.write(str(2*i)+"\n")
		while j<i:
			f.write(str(1)+"\n")
			f.write(str(long(random.uniform(1,1000000000)))+"\n")
			j=j+1
		j=0
		while j<i:
			f.write(str(2)+"\n")
			f.write(str(long(random.uniform(1,1000000000)))+"\n")
			j=j+1
		cmd = "./splay.out < delete.txt"
		timesplay = float(os.popen(cmd).read())
		cmd1 = "./AVL.out < delete.txt"
		timeAVL = float(os.popen(cmd1).read())
		y.append(timesplay)
		z.append(timeAVL)

	line_up, = plt.plot(inputs,y, label='Splay')
	line_down, = plt.plot(inputs,z, label='AVL')
	plt.xlabel('Number Of inputs')
	plt.ylabel('Time (ms)') 
	plt.title("Deletion Graph") 
	plt.legend(handles=[line_down,line_up],loc=2)
	plt.savefig('deletion_graph.png')
	plt.show()

def search_random():
	
	y = []
	z = []
	for i in inputs:
		j=0
		f = open("search_random.txt","w+")
		f.write(str(2*i)+"\n")
		while j<i:
			f.write(str(1)+"\n")
			f.write(str(long(random.uniform(1,1000000000)))+"\n")
			j=j+1
		j=0
		while j<i:
			f.write(str(3)+"\n")
			f.write(str(long(random.uniform(1,1000000000)))+"\n")
			j=j+1
		cmd = "./splay.out < search_random.txt"
		timesplay = float(os.popen(cmd).read())
		cmd1 = "./AVL.out < search_random.txt"
		timeAVL = float(os.popen(cmd1).read())
		y.append(timesplay)
		z.append(timeAVL)

	line_up, = plt.plot(inputs,y, label='Splay')
	line_down, = plt.plot(inputs,z, label='AVL')
	plt.xlabel('Number Of inputs')
	plt.ylabel('Time (ms)') 
	plt.title("Random Search Graph") 
	plt.legend(handles=[line_down,line_up],loc=2)
	plt.savefig('Random_search_graph.png')
	plt.show()

def search_frequent():
	
	y = []
	z = []
	for i in inputs:
		j=0
		f = open("search_frequent.txt","w+")
		f.write(str(2*i)+"\n")
		set_1 = []
		while j<i:
			f.write(str(1)+"\n")
			tmp = long(random.uniform(1,1000000000))
			f.write(str(tmp)+"\n")
			if len(set_1) <= 20:
				set_1.append(tmp)

			j=j+1
		j=0
		while j<i:
			f.write(str(3)+"\n")
			tmp = random.choice(set_1)
			f.write(str(tmp)+"\n")
			j=j+1
		cmd = "./splay.out < search_frequent.txt"
		timesplay = float(os.popen(cmd).read())
		cmd1 = "./AVL.out < search_frequent.txt"
		timeAVL = float(os.popen(cmd1).read())
		y.append(timesplay)
		z.append(timeAVL)

	line_up, = plt.plot(inputs,y, label='Splay')
	line_down, = plt.plot(inputs,z, label='AVL')
	plt.xlabel('Number Of inputs')
	plt.ylabel('Time (ms)') 
	plt.title("Frequent Search Graph") 
	plt.legend(handles=[line_down,line_up],loc=2)
	plt.savefig('frequent_search_graph.png')
	plt.show()


cmd = "g++ splaytree.cpp -o splay.out"
os.system(cmd)
cmd1 = "g++ AVL.cpp -o AVL.out"
os.system(cmd1)

while 1:
	print "Press 1 for insert operation observation"
	print "Press 2 for delete operation observation"
	print "Press 3 for search random operation observation"
	print "Press 4 for search frequent operation observation"
	print "0 for exit"

	choice = int(raw_input())

	if choice == 1:
		insert()
	elif choice == 2:
		delete()
	elif choice == 3:
		search_random()
	elif choice == 4:
		search_frequent()
	else:
		break
