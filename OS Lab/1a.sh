echo "Enter a number: "
read num
fact=1
if (( $num < 0 )); then
	echo "Invalid"
else
	for ((i=1;i<=$num;i++))
	{
		fact=$((fact*i))
	}
echo "The fact is: $fact"
fi
