// merge contents of 2 files
//search a pattern from a file

echo -e "1. Merge two files\n2. Search for a pattern in a file\n"
read -p "Enter choice : " ch
case $ch in 
	1)
	echo "Enter 2 file names"
	read f1 f2
	if !([ -f "$f1" ] && [ -f "$f2" ])
	then
		echo "Files dont exist"
		exit 0
	fi
	read -p "Enter output file name : " f3
	cat "$f1" "$f2" > "$f3"
	echo "Copied"
	;;
	2)
	echo "Enter filename : "
	read f1
	if ! [ -f "$f1" ]
	then
		echo "File doesn't exist"
		exit 0
	fi
	echo "Enter pattern : "
	read patt
	echo $(grep "$patt" "$f1")
	echo -e "Command executed\n"
	;;
	*)
	echo -e "Invalid Option\n"
esac

//check whether palindrome or not

#!/bin/bash
echo "Enter a string: "
read input_string
# Reverse the string
reversed_string=$(echo "$input_string" | rev)
if [ "$input_string" = "$reversed_string" ]; then
    echo "Palindrome"
else
    echo "Not a palindrome"
fi

//display some desired number of lines from user entered line number

read -p "Enter file name : " file
read -p "Enter starting line : " start
read -p "Enter the number of lines to be displayed : " num
tail -n +$start $file | head -n $num

//number of presently active users
//display some desired number of lines from top of file
//updating the access time of a given file to current file
//if user gives invalid input it will prompt invalid message

read -p "Enter 1 for number of presently active users, 2 for displaying lines from top or 3 for updating access time of a file : " choice
case $choice in 
	1) who
	;;
	2) read -p "Enter file name : " file
	   read -p "Enter number of lines to be displayed : " num
	   head -n $num $file
	;;
	3) read -p "Enter file name : " file
	   touch -a $file
           stat $file
	;;
	*) echo "Invalid option"
esac 

//sort numbers in descending orders

echo "Enter the numbers : "
read -a arr
n=${#arr[@]}
echo "The original array : ${arr[@]}"
for (( i=0; i<n-1; i++ ))
	do
	for (( j=0; j<$n-i-1; j++ ))
		do
		if [  ${arr[$j]} -lt ${arr[$((j+1))]} ]
			then
			temp=${arr[$j]}
			arr[$j]=${arr[$((j+1))]}
			arr[$((j+1))]=$temp
		fi
		done
	done
echo "Descending order : ${arr[@]}"

//find max and min of some numbers

echo "Enter the numbers : "
read -a arr
n=${#arr[@]}
echo "The original array : ${arr[@]}"
maxi=${arr[0]}
mini=${arr[0]}
for (( i=1; i<n; i++ ))
do
	if [ $maxi -lt ${arr[$i]} ]
	then
		maxi=${arr[$i]}
	fi
	if [ $mini -gt ${arr[$i]} ]
	then
		mini=${arr[$i]}
	fi
done
echo "The maximum number : $maxi"
echo "The minimum number : $mini"

//create 2 infinitely processes in background and then prematurely terminate each of these infinite processes

#!/bin/bash
proc () {
	while :
	do
		#does nothing, is infinite
		echo $1
		sleep 1
	done
}
#process 1 and its pid
proc hi &
proc1_id=$!
#process 2 and its pid
proc bye &
proc2_id=$!
sleep 5
echo $proc1_id $proc2_id
kill $proc2_id
kill $proc1_id

//implement bubble sort

echo "Enter the numbers : "
read -a arr
n=${#arr[@]}
echo "The original array : ${arr[@]}"
for (( i=0; i<n-1; i++ ))
	do
	for (( j=0; j<$n-i-1; j++ ))
		do
		if [  ${arr[$j]} -gt ${arr[$((j+1))]} ]
			then
			temp=${arr[$j]}
			arr[$j]=${arr[$((j+1))]}
			arr[$((j+1))]=$temp
		fi
		done
	done
echo "The sorted array : ${arr[@]}"

//delete an element from specific position of an array

echo "Enter the numbers : "
read -a arr
echo "The original array : ${arr[@]}"
read -p "Enter the index number to be deleted : " index
unset arr[$index]
echo "The array : ${arr[@]}"

//works on student records

#!/bin/bash
filename="stdInfo.txt"
display_file() {
    echo "Student Information:"
    sort -k1,1n "$filename" #resistricts sorting till 1st column of fields only
}
display_student() {
    echo "Enter the roll number to display student info:"
    read roll_no
    grep -w "$roll_no" "$filename"
}
delete_student() {
    echo "Enter the roll number to delete student entry:"
    read roll_no
    sed -i "/^$roll_no /d" "$filename"
    echo "Student entry deleted successfully."
}
add_student() {
    echo "Enter roll number, Name, and city (separated by spaces):"
    read roll_no name city
    echo "$roll_no $name $city" >> "$filename"
    echo "Student entry added successfully."
}
update_student() {
    echo "Enter the roll number to update student info:"
    read roll_no
    echo "Enter new Name and new city (separated by spaces):"
    read new_name new_city
    sed -i "/^$roll_no /s/[^ ]* [^ ]* [^ ]*/$roll_no $new_name $new_city/" "$filename"
    echo "Student entry updated successfully."
}
while true; do
    echo "Menu:"
    echo "1. Display entire contents of the file"
    echo "2. Display student info by roll number"
    echo "3. Delete student entry by roll number"
    echo "4. Add a new student entry"
    echo "5. Update student entry"
    echo "6. Exit"
    read choice

    case $choice in
        1) display_file ;;
        2) display_student ;;
        3) delete_student ;;
        4) add_student ;;
        5) update_student ;;
        6) echo "Exiting..."
           break ;;
        *) echo "Invalid choice. Please select a valid option." ;;
    esac
done

//check for armstrong number

read -p "Enter the number : " num
len=${#num}
n=$num
while [ $n -gt 0 ]
do
	d=$((n % 10))
        sum=$((sum + d**len))
        n=$((n/10))
done
if [ $sum -eq $num ]
then
	echo "It is an Armstrong number"
else
	echo "It is not an Armstrong number"
fi

//print all possible combinations of 3 numbers

echo "Enter the three numbers : "
read -a arr
echo "All possible combinations : "
for i in ${arr[0]} ${arr[1]} ${arr[2]}
do	
	for j in ${arr[0]} ${arr[1]} ${arr[2]}
	do
		for k in ${arr[0]} ${arr[1]} ${arr[2]}
		do
			echo $i $j $k
		done
	done
done

//find position of substring in given string

read -p "Enter string : " str
read -p "Enter substring : " sub
rest=${str#*$sub}
echo $(( ${#str}-${#rest}- ${#sub} ))

//find GCD of 2 numbers

echo "Enter the two numbers : "
read num1 num2
for (( i=1; i<=num1 && i<=num2; i++ ))
do
	if [ $((num1%i)) -eq 0 ] && [ $((num2%i)) -eq 0 ]
	then
		gcd=$i
	fi
done
echo "The gcd of $num1 and $num2 is $gcd"

//count number of words, characters, white spaces and special symbols in a given task

echo "Enter a string : "
read text

word=$(echo -n "$text" | wc -w)
char=$(echo -n "$text" | wc -c)

space=$(expr length "$text" - length `echo "$text" | sed "s/ //g"`)
special=$(expr length "${text//[^\~!@#$&*()]/}")

echo "Number of words = $word"
echo "Number of characters = $char"
echo "Number of white spaces = $space"
echo "Number of special symbols = $special"

//find factorial of a given number

read -p "Enter the number : " n
fact=1
for (( i=1 ; i<=n; i++ ))
do
	fact=$((fact*i))
done
echo "The factorial of $n is $fact"

//print fibonacci series

read -p "Enter the value of n : " n
a=0
b=1
echo "The fibonacci series : "
for (( i=0 ; i<n; i++ ))
do
	echo "$a"
	c=$((a+b))
	a=$b
	b=$c
done

//print in descending order

echo "Enter the numbers : "
read -a arr
n=${#arr[@]}
echo "The original array : ${arr[@]}"
for (( i=0; i<n-1; i++ ))
	do
	for (( j=0; j<$n-i-1; j++ ))
		do
		if [  ${arr[$j]} -lt ${arr[$((j+1))]} ]
			then
			temp=${arr[$j]}
			arr[$j]=${arr[$((j+1))]}
			arr[$((j+1))]=$temp
		fi
		done
	done
echo "Descending order : ${arr[@]}"
