cmake ..
make
MAX=100;
MIN=0;
BROKEN=0;
FAILEDI=-1;
FAILEDJ=-1;
for ((i=MIN; i<=MAX; i++))
do
	for ((j=MIN; j<=MAX; j++))
	do
		echo "$i $j" > input.txt
		./Math_logic_HW3
		echo ./Check > tmp.txt
		if [ $? -eq 1 ] 
		then 
			BROKEN=1;
			FAILEDJ=$j
			FAILEDI=$i
			break
		fi
	done
	if [ $BROKEN -eq 1 ]
	then
		break
	fi
done

if [ $BROKEN -eq 1 ]
then
	echo "You have FAILED on test: $FAILEDI $FAILEDJ"
else
	echo "Your program is CORRECT!"
fi

rm tmp.txt