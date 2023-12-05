echo "Enter the username: "
read name

if grep -c $name /etc/passwd
then
	echo "Valid User"
else
	echo "Invalid User"
fi
