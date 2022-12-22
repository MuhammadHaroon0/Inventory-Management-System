# Inventory-Management-System
Inventory Management System of University.

Two Structures:
InventoryItem: used for keeping record of all the Inventory Items.
Allocated_to:An array of structures used in the InventoryItem structure to allot that item to faculty members of university.

A MAIN FUNCTION:
displaying the menu from user can make choices and then the control goes to function of that choice entered by user.

A total of 12 functions:
8 Main Functions:

addInventoryItems:adding the items through the InventoryItem structure in the file.
viewInventoryItems:for viewing all the inventory items and their attributes with a well settled output implementation.
searchInventoryItems:takes name of item to search and show attributes of inventory item.
editInventoryItems:used for editing inventory item's attributes by taking its id from user.
deleteInventoryItems:used for deleting inventory item by taking its id from user.
assignInventoryItems:used for assigning the specific item to a faculty member by taking its id and the faculty member's id from user.
retrieveInventoryItems:used for retrieving the specific item from a faculty member by taking its id and the faculty member's id from user.
viewFacultyListofBorrowedItems:displays the list of all the members who have been assigned a specific inventory item.

4 Validation Functions:

validationForNegativeInput: never allows the user to enter a negative input.
validationForEmptyFile: never allows the program to run any function if the file has not items added.
validationForWrongItemId: never allows the user to enter an item id which is not present already. 
validationForWrongItemName:used in searchInventoryItems function to control wrong item name which has not been in the record.

Binary Input and Output Method has been used for data transfer from program to file.

Libraries used:
iostream
fstream
cstring
iomanip

cstrings are used in structures instead of c++ string objects.
