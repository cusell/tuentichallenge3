import math
lines = []
while True:
  try:
    line = raw_input()
  except:
    break
  print sum(int(n) for n in str(math.factorial(int(line)))) 
