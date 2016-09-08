from collections import *
from Queue import *
import time,math,heapq,sys

"""
1. Change the name of the file
2. Give the number of the nodes + 1
3. REmove the last number from the output file
"""

class Graph:
  def __init__(self):
    self.nodes = set()
    self.edges = defaultdict(list)
  def add_node(self, value):
    self.nodes.add(value)

  def add_edge(self, from_node,to_node):
      self.edges[from_node].append(to_node)
      self.edges[to_node].append(from_node)
def Get_no_of_edges():
	#name=raw_input("Please give the file name of number of edges:")
	path = '/home/saiharsh/Desktop/honor_code/ear/saiharsh@10.2.40.4/Experiments/bcc_graph/'
	path = path + 'soc-Epinions1_s0.mtx'
	# path = '/home/saiharsh/Desktop/honor_code/'
	# path = path + 'input.txt'
	# print "Path = ", path
	f=open(path,'r')
	ans={}
	for line in f:
		try:
			tmp = line.split()
			tmp[0] = int(tmp[0]) + 1
			tmp[1] = int(tmp[1]) + 1
			tmp[2] = int(tmp[2])
			ans[tmp[0],tmp[1]]=1
		except:
			pass
	return ans

GT=Graph()
edges=Get_no_of_edges()
edges= OrderedDict(sorted(edges.items()))
for node in range(1,1001): # Enter the number of nodes + 1 i.e for range
	GT.add_node(node)
for edge,j in edges.iteritems():
	GT.add_edge(edge[0],edge[1])
row=['1']
count=1
Colum=[]
s=''
for i in GT.nodes:
	for j in GT.edges[i]:
		s=s+str(j)+" "
		Colum.append(j)
	count=count+len(GT.edges[i])
	row.append(str(count))

print len(row)-1
print len(Colum)
print " ".join(row)
print s
