echo "Enter the number of elements in the array: "
read n
echo "Enter the elements: "
for ((i=0;i<$n;i++))
do
	read arr[$i]
done
echo "Original array : ${arr[@]}"
for ((i=1;i<n;i++));
do
	key=${arr[i]}
	j=$((i-1))
	while ((j>=0 && arr[j]>key)); 
	do
		arr[j+1]=${arr[j]}
		j=$((j-1))
	done
	arr[j+1]=$key
done

echo "Sorted array: ${arr[@]}"
