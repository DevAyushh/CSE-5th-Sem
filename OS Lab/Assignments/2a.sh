n=$#
if ((n<0)); then
	echo "Invalid"
	exit
fi

sum=0
while ((n>0))
do
	sum=$(($sum+$1))
	shift
	n=$(($n-1))
done
echo "The sum is $sum" 
