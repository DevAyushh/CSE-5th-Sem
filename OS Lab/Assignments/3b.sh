#!/bin/bash
# Write a menu driven shell script with three options:
# 1) Accept your personal details along with a password and store them in a data file (e.g. personal.dat);
# 2) Display the personal details stored in the data file after successfully matching the password stored in the file;
# 3) Exit from menu.
while [ 1 ]
do
	read -p "Enter your choice: " choice
	case $choice in
	1)
	read -p "Enter your name, roll and department separated by spaces: " name roll dept
	read -sp "Enter your PASSWORD: " password
	entry="$name|$roll|$dept|$password"
	echo "$entry" >> personal.dat
	echo "Your details have been added successfully"
	;;
	2)
	read -sp "Enter your PASSWORD: " password
	entry=`cat personal.dat | grep "$password"`
	if [ entry == "" ]
	then 
		echo "Password does not match with any of the entries...Try Again"
	else
		echo "Password verified successfully. Your details are as follows: "
		name=`echo "$entry" | cut -d "|" -f1`
		roll=`echo "$entry" | cut -d "|" -f2`
		dept=`echo "$entry" | cut -d "|" -f3`
		password=`echo "$entry" | cut -d "|" -f4`
		echo -e "Name: $name\nDepartment: $dept\nRoll Number: $roll"
	fi
	;;
	3)
	echo "Exiting..."
	exit
	;;
	*)
	echo "Invalid Choice..Try Again"
	;;
	esac
done


# #! /bin/bash

# echo "1. Accept Personal Details and store in a File."
# echo "2. Display Stored Details"
# echo "3. Enter 0 to exit."
# read -p "Enter your choice: " C
# while (($C!=0))
# do
# case $C in
# "1")
# 	read -p "Enter Username:" Name
# 	echo "Enter Your Details Press enter to store"
# 	read Details
# 	Filename=$(echo $Name|cut -d ' ' -f1)
# 	Filename+=Personal.dat
# 	if [ -a $Filename ];then
# 		echo "A File With Your data already Exists!"
# 		read -p "Enter (Y/y) to continue append to that file or Exit(N/n): " choice
# 		if (( $choice != "Y" && $choice != "y" )); then
# 			continue
# 		fi
# 	else
# 		stty -echo
# 		read -p "Enter password: " Pass
# 		stty echo
# 		$(touch $Filename)
# 		$(echo $Name >> $Filename)
# 		$(echo $Pass >> $Filename)
# 	fi
# 	$(echo -e "\n")
# 	$(echo $Details >> $Filename)
# 	echo -e "\n"
# 	echo Written Successfully!
# 	;;
# "2")
# 	read -p "Enter Username: " Name
# 	Filename=$(echo $Name|cut -d ' ' -f1)
# 	Filename+=Personal.dat
# 	if [ -a $Filename ] ; then
# 		stty -echo
# 		read -p "Enter Password: " Pass
# 		stty echo
# 		pass=$(sed -n '2p' $Filename)
# 		echo -e "\n"
# 		if (($pass == Pass)); then
# 			Details=$(tail -n +3 $Filename)
# 			echo $Details
# 		else
# 			echo Wrong Password!!
# 		fi
			
# 	else
# 		echo "Username not Registered!"
# 	fi
# 	;;
# "0")
# 	exit 0;;
# *)
# 	echo "Give correct Choice!"
# esac
# read -p "Enter your choice: " C
# done