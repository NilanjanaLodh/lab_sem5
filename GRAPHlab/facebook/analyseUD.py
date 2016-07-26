# analyses an undirected graph
from sys import argv 
import snap
edge_list_file_name =argv[1]
G = snap.LoadEdgeList(snap.PUNGraph,edge_list_file_name,0,1,)
total_nodes = G.GetNodes();
total_edges = G.GetEdges();

print 'Graph has ', total_nodes , 'users and ' ,total_edges  ,' friendships . '
node_deg=[None] * total_nodes
f= open('NodevsDeg','w')
f.write('#Node vs Degree of each node\n')
for node in G.Nodes():
    node_deg[node.GetId()]=node.GetDeg()
    f.write(str(node.GetId())+'\t'+str(node.GetDeg())+'\n')
f.close()

# since this is an undirected graph, sum of all degrees = 2* |edges|

#_____________find degree distribution___________________


f=open('DegDistr','w')
degdistr=snap.TIntPrV()
snap.GetDegCnt(G,degdistr)
# Val1 : degree , Val2: freq
maxDegree=degdistr[degdistr.Len()-1].GetVal1()
print 'Maximum degree is ', maxDegree
degdistfreq=[0]*(1+maxDegree)

for pr in degdistr:
    deg =pr.GetVal1() 
    count =pr.GetVal2()
    degdistfreq[deg]=1.0 * count/total_nodes

degdistcf=[0]*(1+maxDegree) #cumulative frequency
degdistcf[0]=degdistfreq[0]

f.write(str(0)+'\t'+str(degdistfreq[0])+'\t'+ str(degdistcf[0])+'\n')
for d in range(1,1+maxDegree):
    degdistcf[d] = degdistcf[d-1] + degdistfreq[d]
    f.write(str(d)+'\t'+str(degdistfreq[d])+'\t'+ str(degdistcf[d])+'\n')
f.close()
#_____________diameter, etc______________________

dia = snap.GetBfsFullDiam(G,100)
print 'Diameter is ' , dia

#______clustering coefficient_______--

f= open('deg_cc_points','w')
node_cc_H = snap.TIntFltH() #node, cc hashmap
snap.GetNodeClustCf(G, node_cc_H)
node_cc= [None] * total_nodes;
for nodeId in node_cc_H:
    node_cc[nodeId]= node_cc_H[nodeId]

#nodeId ranges in [0,total_nodes)

for nodeId in range(total_nodes):
    f.write(str(node_deg[nodeId])+'\t'+str(node_cc[nodeId])+'\n')

f.close()
#_________________
