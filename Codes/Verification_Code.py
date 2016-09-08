"""
Verification Code
1. No of cycles == 1 and the first input should be a cycle
2. The end points of the chain should be in the previous chain
3. In case a trival edge comes check weather it's visited or not.
4. If all cases are passed then the code output is Correct !!!!!! 
"""
visited_array=[0]*5000000 # Change the No_nodes to Number of nodes + 1
def visited(i):
	visited_array[i]=1
def is_visited(i):
	if visited_array[i]==1:
		return 0
	else:
		return 1
def check(map_list):
	flag=1
	for i in range(0,len(map_list)):
		if map_list[i]==0:
			flag=0
			return 0
	if flag:
		return 1
if __name__ == '__main__':
	path = '../output/'
	path = path + 'check.txt'
	print "Path = ", path
	file=open(path,'r')
	Num_cycle=0
	Num_chains=0
	Num_trival=0
	is_pass=True

	# info=map(int,file.readline().split())
	# print "No. of Nodes (n):"+str(info[0])	
	# print "No. of Edges (m):"+str(info[1])
	# print "n-m+1 :"+str(info[1]-info[0]+1)
	prev=map(int,file.readline().split())
	
	if(prev[0]==prev[len(prev)-1]): # first condition i.e cycle
		Num_cycle+=1
		map(visited,prev)
		for line in file:
			#print line
			line=map(int,line.split()) # converting string to int
			#print line
			if (line[0]!=line[len(line)-1]):
				if(visited_array[line[0]]==1 and visited_array[line[len(line)-1]]==1): # check weather the end points of a chain is visited or not.
					#print line[1:len(line)-1]
					#print "Map" + str(map(is_visited,line[1:len(line)-1]))
					map_list =map(is_visited,line[1:len(line)-1])
					#check(map_list)
					if len(line)==2:
						#print "if\n"
						Num_trival+=1
						map(visited,line)
					
					elif check(map_list):
						#print "else if\n"
						map(visited,line)
						if len(line)>2:
							Num_chains+=1
							prev = line
					else:
						is_pass=False
						print "Intermediate Vertices are Visited\n"
						break

				else:
					is_pass=False
					print "Wrong answer at"
					print line,"end points are not visited", line[0],visited_array[line[0]],line[len(line)-1],visited_array[line[len(line)-1]]
					map(visited,line)
					break
					
			else:
				is_pass=False
				print "More then one cyle found"
				print "It means the given graph is not biconnected"
				print "Please use a bi-connected graph"
				print line
				map(visited,line)
				break
	else:
		is_pass=False
		print "Incorrect"
		print "First line is not a cycle or the length of the cycle is 3","\n","please arrange the input in the correct format"
	#	print "The error cycle is ", prev
	
	if is_pass:
		print "Passed"
		print "Number of Ears :",Num_chains+Num_trival+1
		print "Number of Cycles : 1"
		print "Number of Chains : ", Num_chains
		print "Number of Trival Edges : ", Num_trival
	else:
		print "Not Bi-connected"
	for i in range(1,50000):
		if(not visited_array[i]):
			print "Number of nodes are visited is :", i-1, visited_array[i]
			break
