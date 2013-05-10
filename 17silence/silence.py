import Image

"""
In the reduced images, the three lights are at rectangles:
f0 c0 f1 c1
3 6 8 24
74 6 79 24
143 6 150 24
diff: aprox (5,18)
"""
#Average color of rectangle (f0,c0)-(f1,c1)
def avgcol(v, pix):
  avg = [0,0,0]
  tot = 0
  for i in range(v[0],v[2]+1):
    for j in range(v[1],v[3]+1):
      tot += 1
      for k in range(3):
        avg[k] += pix[i,j][k]
  for k in range(3):
    avg[k] = avg[k]/tot
  return avg

def binaryval(p):
  if (p[0]<100 and p[1]<100): return 0
  elif(p[0]>100 and p[1]>100): return 1
  return -1 #should never happen

led = [[3,6,9,24], [74,6,79,24], [143,6,150,24]]
NIMG = 3424 #Duration: 5 min 42.40 sec, 10fps
"""
im = Image.open("image/image-0002491.png")
pix = im.load()
print avgcol(led[0],pix) #first led
print avgcol(led[1],pix) #second led
print avgcol(led[2],pix) #third led
for j in range(3):
  print binaryval(avgcol(led[j],pix)),
print ""
"""
for i in range(1,NIMG+1):
  zi = str(i).zfill(7)
  im = Image.open("image/image-"+zi+".png")
  pix = im.load()
  
  [x,y,z] = [avgcol(led[0],pix),avgcol(led[1],pix),avgcol(led[2],pix)]
  
  #print i,
  for j in range(3):
    x = binaryval(avgcol(led[j],pix))
    if x == -1:
      print "PIXEL NOT IDENTIFIED!!!"
      exit()
    print binaryval(avgcol(led[j],pix)),
  print ""
