hw1：
Write a program, use the following method: 
./sed [ -g(optional) ] [ -source(required) ] [ -target(required) ] 
The program reads from the standard input line by line, and the first occurrence of each line is Where the [ -source ] string is replaced by the [ -target ] string. 
If [ -g ] is enabled, replace all occurrences of the [ -source ] string with the [ -target ] string on each line. 
The length of [ -source ] and [ -target ] is between 1 and 256, and each line does not exceed 1024 bytes. 
Print the result to standard output. 
If there are two parameters, the parameters are [ -source ] and [ -target ] in sequence. 
If there are three input parameters, the parameters are [ -g ], [ -source ] and [ -target ] in sequence. 
Any Undefined operations need to print a help message.

hw2：
Please complete an address book program that can record name, email, web link and phone number and includes the following functions:
Create an address book
According to the program parameter argv[1], create a new address book of N contacts
N input, the format is <name>\t<email>\t<url>\t<phone_number>
Enter command mode after creation

Add Contact (i)
Format: i\t<name>\t<email>\t<url>\t<phone_number>
Function: Insert a new contact after the last contact in the address book. The data is separated by \t, and the data will not have empty values.
ex: i jack jack@email.example hello.world.tw 987654321 (Add jack)
	
update contact (u)
Format: u\t<name>\t<email>\t<url>\t<phone_number>
Function: Update the existing contact information. The data is separated by \t, and the data will not have empty values.
ex: u jack jack123@email.email hello.world.tw 123456789 (update jack contact information)

delete contact (d)
Format: d\t<name>
Function: delete a contact
ex: d jack (remove jack)
	
find (f)
Format: f\t<pattern>
Function: Find contacts with <pattern>, <pattern> is case sensitive.
If there is a matching contact, output the contact information; if not, output no result.
ex: f jack (find jack and contacts with jack in their name, for example: jack, jack_son, man_jack, etc.)
	
Sort(s)
Format: s\t<pattern>
Function: Sort by <pattern> field from small to large (only sort, no output required).
The fields are divided into n (name), e (email), u (website), p (phone number)
Phone numbers are sorted numerically, and the rest are compared by ASCII values
ex: s n (sort the address book by name from small to large)
	
Show address book content (p)
Format: p
Function: Output address book in a format
	
exit the program (q, quit)
Format: q , quit
Function: end program

hw6：
Write a program that uses Binary Search Tree (BST) for word statistics, and each node stores the word and the number of words.
The BST must satisfy that in each node, all node strings in the left subtree are smaller than this node string, and all node strings in the right subtree are larger than this node string.
If the input word is a new word, then insert, if it is already in BST, add or decrease the number of words.
Use inorder traversal to output the content of BST.
After converting the BST into an array, sort it.
The comparison method is that the number of words with a large number is in the front, and the small number is in the back
If the number is the same, the string with the smaller ASCII code is in front.
