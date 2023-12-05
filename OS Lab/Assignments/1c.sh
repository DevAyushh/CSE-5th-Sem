echo "Enter any number: "
read num
sum=0
rem=0

if (( $num < 0 )); then
		echo "INVALID INPUT"
else
	while (( $num > 0 ))
	do
			rem=`expr $num % 10`
			sum=`expr $sum + $rem`
			num=`expr $num / 10`
	done
	echo "Sum is: $sum"
fi	

