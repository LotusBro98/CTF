#!/bin/bash/

for i in $(ls order); do
	#sorted=$(echo $i | grep -o . | sort | tr -d '\n')
	#echo -e "$sorted"
	echo $(cat order/$i) $i $(cat order/$i)
done

#{}0011233345556667889aaaccddddddeeffgl
#0011233345556667889aaccddddddeef
