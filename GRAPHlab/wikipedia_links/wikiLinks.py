import snap
G = snap.LoadEdgeListStr(snap.PUNGraph,'edgelist.tsv',0,1)
#G.Dump()
tnodes = G.GetNodes();
tedges = G.GetEdges();

print 'WikiLinks Graph has ', tnodes , 'nodes and ' ,tedges  ,' edges'
nodes = snap.TIntPrV()# pairs of (degree, num of nodes of that deg)
in_nodes= snap.TIntPrV()
out_nodes= snap.TIntPrV()

snap.GetInDegCnt(G, in_nodes)
snap.GetOutDegCnt(G, out_nodes)
snap.GetDegCnt(G,nodes)

#print 'degree\tfrequency'

f = open('wikiTotaldegDirected','w')
for degcntpr in nodes:
    #print degcntpr.GetVal1() , '\t' , degcntpr.GetVal2()
    f.write(str(degcntpr.GetVal1())+'\t'+ str(degcntpr.GetVal2()) + '\n')
f.close()

f = open('wikiIndegDirected','w')

for degcntpr in in_nodes:
    #print degcntpr.GetVal1() , '\t' , degcntpr.GetVal2()
    f.write(str(degcntpr.GetVal1())+'\t'+ str(degcntpr.GetVal2()) + '\n')
f = open('wikiOutdegDirected','w')

for degcntpr in out_nodes:
    #print degcntpr.GetVal1() , '\t' , degcntpr.GetVal2()
    f.write(str(degcntpr.GetVal1())+'\t'+ str(degcntpr.GetVal2()) + '\n')


f.close()
