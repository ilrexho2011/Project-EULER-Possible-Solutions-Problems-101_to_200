import time
stime = time.time() # Beginning time.

mat = [map(int, line.strip().replace('-','0').split(',')) for line in open('data/network.txt')]
nw, lm = sum(map(sum, mat))/2, len(mat)
distance, node = [], set()

def searchnode(st):
  global mat,distance,node
  temporary = {}
  for k in st:
    a = min([x for x in mat[k] if x])
    temporary.update([(a, k)])
  b= min(temporary.keys()) # minimum distance between the rest connecting nodes
  i = temporary[b]
  j = mat[i].index(b)
  # eliminate the very distances in mat so it won't bother in next term
  mat[i][j], mat[j][i] = 0, 0
  if i not in node or j not in node:
    distance.append(b)
    node.add(i)
    node.add(j)

searchnode(xrange(lm))
while len(node) < lm:
  searchnode(node)

etime = time.time(); time = str(etime - stime) # Finishing time.
print 'consumed_time:', time[:time.index('.')+4], 's'
print nw - sum(distance), len(distance)