export b=Math_logic_HW2;
echo "compilation...";
cmake ..;
make;
echo -en 'compilation finished\n\n';
echo -en '--- \033[01;31mtesting\033[00m --- \n\n';
for i in 1 2 5 6 7 8 9 10 12 13 14 15
do 
	cat ../tests/correct$i.in > proof.in
	echo -en 'testing \033[01;31mcorrect'$i.in'\033[00m\n';
	for j in 1 2 3
	do
		./Math_logic_HW2
		if [ $? -eq 1 ]
		then
			break
		fi
		cat out.txt > proof.in
	done
done
