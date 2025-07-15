Please note that some of these programs will only work when launched from a terminal or IDE (like by typing ./hw1.exe when in the correct directory). Some of them are also expecting certain files to be present, but those cases will be listed below. 

Note: The original version of HW5 is quite buggy. I had been able to get it to work fine for class, but running it today it sometimes doesn't launch, and when it does, output frequently includes garbage data. It likely has to do with the alias string being limited to 11 characters, but longer strings being passed to it. I fixed this in the HW5-Patched.c file by changing the length of the alias string to 64 characters. Still, the compiled program HW5-Patched.exe only worked properly when I compiled and ran it in Ubuntu.

## Functions of each program

### HW1

Takes an integer and says whether it is postive or negative. 

### HW2

Takes an integer between 1 and 999,999, then returns each digit in reverse order and states whether it is divisible by 9. 

### HW3

Takes a name and an integer between 1 - 1,000,000 and displays the number in binary, octal, and hexadecimal.
Also gives the option to save that info to a file including name and date. 

### HW4

Prompts the user for a name. Then, opening the file "CS222_Inet.txt", it sorts the list of usernames & IP addresses in ascending or descending order based on user input. It then saves that information to the file "222_Alias_List.txt" along with name, date, and time.

### HW5

As with program 4, it uses the address list "222_Alias_List.txt". However, it has far more functionality. 

It allows the user to select from several options: 

1) Add address
2) Look up address
3) Display list
4) Display aliases for location
5) Save to file
6) Quit

- Option 1 lets the user add an IP address (along with a username) to the list. It only allows the user to enter valid Ipv4 addresses. 

- Option 2 allows the user to look up addresses by alias. 

- Option 3 displays the whole list of IP addresses, along with the number of entries (nodes). 

- Option 4 allows the user to search for aliases based on locality of IP addresses (the first two numbers of an IPv4 address. So if you enter "123.55", it will display all aliases that have an IP address of 123.55.x.x)

- Option 5 lets the user save their modified list of IP addresses to a file of their choosing. 

You know what option 6 does. 
 






