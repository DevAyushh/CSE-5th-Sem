echo "Enter any year: "
read yr
if ((yr < 0)); then
	echo "Invalid Year";

else	
if ((yr%4 == 0 && yr%100 != 0)) || ((yr%400 == 0)); then
	echo "It is a leap year"
else
	echo "It is a non-leap year"
fi
fi
