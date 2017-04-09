export b=Math_logic_HW2;
echo "compilation...";
cmake ..;
make;
echo -en 'compilation finished\n\n';
echo -en '---running \033[01;31mcorrect\033[00m tests--- \n\n';
for i in 1 2 5 6 7 8 9 10 11 12 13 14 15
do 
	./$b 1 correct$i.in
done
echo -en '\n';
echo -en '---running \033[01;31mincorrect\033[00m tests--- \n\n';
for i in 1 2 3 4 5 6 7 8 9 10 11
do
	./$b 1 incorrect$i.in
done
