#!/bin/bash
read -p "Enter Filename: " FILE

echo "1. Sort the records in reverse order of Roll. "
echo "2. Replace lower case letters with upper case."
echo "3. Find the records with unique name."
echo "4. Display 2nd and 3rd line from the file."
echo "5. Display a file."
echo "6. Press 5 to exit."

while [[ $ch -ne 6 ]]
do
	read -p "Enter your choice: " ch
	case $ch in
		1) 	sort -t "|" -nr -k2 $FILE | cat > Sorted.dat
			echo "***Sorted file created***"
			;;
			
		2)	upper=$(cat Sorted.dat)
			echo "$upper" | tr '[:lower:]' '[:upper:]' > Sorted.dat
			echo "***Case changed to uppercase***"
			;;

		3)	cat Sorted.dat | uniq -u Sorted.dat >> Students.dat
			echo "***Record with unique names created***"
			echo "***Record appended to Students.dat***"
			;;

		4)	echo "***Printing 2nd & 3rd line of Students.dat***"
			sed -n '2,3p' Students.dat
			;;

		5)	read -p "Enter Filename to display: " name
			cat $name
			;;

		6) 	echo "*****Process exiting*****"
			exit
			;;

		*) echo "Invalid choice"	
			;;	
	esac
done
