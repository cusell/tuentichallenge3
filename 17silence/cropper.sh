#!/bin/bash
for ((x=1;x<=3424;x+=1)); do mogrify -crop 156x30+406+332 image/image-`printf "%07d" $x`.png; done
