!/bin/bash
To:
i) Show the permissions of a file or directory; 
ii) Show the number of files and directories under current directory separately; 
iii) Show the last modification time of a file in current directory;
iv) Exit from menu.
while [ 1 ]
do
	read -p "Enter your choice: " choice
	case $choice in
	1)
	read -p "Enter the name of the file: " filename
	if [ -e $filename ]
	then
		permissions=`ls -l | grep "$filename" | cut -c2-10`
		echo "The permissions granted to $filename are: $permissions"
	else
		echo "$filename is not a file under the current directory"
	fi
	;;
	2)
	files=`ls -l | grep "^-" | wc -l`
	directories=`ls -l | grep "^d" | wc -l`
	echo "The number of files under the current directory `pwd` is $files."
	echo "The number of directories under the current directory `pwd` is $directories."
	;;
	3)	
	read -p "Enter the name of the file: " filename
	if [ -e $filename ]
	then
		modtime=`ls -l | grep "$filename" | cut -c42-47`
		echo "The last modification time of the file $filename is $modtime"
	else
		echo "$filename is not a file under the current directory"
	fi
	;;
	4)
	echo "Exiting..."
	exit
	;;
	*)
	echo "Invalid Choice...Try Again"
	esac

done



# #! /bin/bash

# echo "1. Check File or Folder permission."
# echo "2. Check Number and List Files and Folders."
# echo "3. Check Number of users connected."
# echo "4. Check last Modifcation time of a file"
# echo "5. Press 5 to exit."
# read -p "Enter your Choice: " n
# while ((n!=5))
# do
# case $n in
# "1")
# 	read -p "Enter name of your File or Folder: " File
# 	if [ -d $File ];then
# 		echo "Permissions of the Folder $File is: " $( ls -l|grep "$File"|cut -c 2-10) 
# 	elif [ -e $File ];then 
# 		echo "Permissions of this File $File is: " $( ls -l |grep "$File"|cut -c 2-10)
# 	else
# 		echo "No such File exists!"
# 	fi;;

# "2")
# 	Dir=.
# 	if [ -d $Dir ]; then
# 		Out=($(cd $Dir && ls ))
# 		Dirs=()
# 		Files=()
# 		for item in "${Out[@]}"
# 			do
# 			if [ -d $item ];then
# 				Dirs+=($item)
# 			else
# 				Files+=($item)
# 			fi
# 			done
# 		echo "This Directory has ${#Files[@]} Number of Files and ${#Dirs[@]} Number of Folders"
# 		echo "The Files are: ${Files[@]}"
# 		echo "The Foldres are: ${Dirs[@]}"
# 	fi;;
# "3")
# 	echo "Number of Connected Users are: $(who|wc -l)"
# 	;;
# "4")
# 	read -p "Enter Filename: " File
# 	if [ -e $File ];then
# 		echo Last Modification Time is: $(stat -c %y $File)
# 	else
# 		echo Not a valid file.
# 	fi;;
# "5")
# 	exit 0;;
# *)
# 	echo "Please Give the correct option!";;
# esac
# read -p "Enter your choice: " n
# done