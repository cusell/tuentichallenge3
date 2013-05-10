import Image, ImageDraw
import sys

cas = 1
numcasos = int(raw_input())
for cas in range(numcasos):
  #Create a white N x N image
  N = 640
  im = Image.new("RGB", (N, N), "white")
  draw = ImageDraw.Draw(im)

  #Draw the given rectangles.
  for line in sys.stdin:
    box = [int(n) for n in line.split()]
    if box[0]!=-1:
      draw.rectangle(box, fill=0)
    else:
      break

  im.save("island-"+str(cas)+".png", "PNG")
