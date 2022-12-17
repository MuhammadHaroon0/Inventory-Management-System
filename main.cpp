#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

struct Allocated_to
{
    char name[50];
    int facultyId;
};
struct InventoryItem
{
    char Name[50];
    int Item_ID;
    char Category[50];
    int Item_count;
    Allocated_to Allocated_to;
};

void addInventoryItems(fstream &,string);
void viewInventoryItems(fstream &,string);
void searchInventoryItems();
void editInventoryItems();
void deleteInventoryItems();
void assignInventoryItems();
void retrieveInventoryItems();
void viewFacultyListofBorrowedItems();

int main()
{
    fstream inventoryFile; //object that will point to inventory items file
    const string nameOfFile="inventory_item_data.txt";  //string to store name of file;

    /******MAIN VARIABLES******/
    int selection;//for making selections between functions
    cout<<"\t\t\t\t*****| Faculty College of Information and technology |*****\n";
    while(1)
    {
        cout<<"\t\t\t\t     _________________________________________________\n\n";
        cout<<"1. Add inventory items\n";
        cout<<"2. View all inventory items\n";
        cout<<"3. Search inventory item\n";
        cout<<"4. Edit inventory item\n";
        cout<<"5. Delete inventory item\n";
        cout<<"6. Assign inventory item\n";
        cout<<"7. Retrieve inventory item\n";
        cout<<"8. View the list of faculty members who have borrowed a specific item\n";
        cout<<"\nMake your selection or press 9 to quit: ";
        cin>>selection;
        //validation loop for selection
        while(selection!=1 && selection!=2 && selection!=3 && selection!=4 && selection!=5
                && selection!=6 && selection!=7 && selection!=8 && selection!=9 &&selection!=9)
        {
            cout<<"\n\nPlease enter a valid choice:";
            cin>>selection;
        }

        if(selection==9 || selection==9) //quitting the program
        {
            break;
        }

        switch(selection)
        {
        /***ADD INVENTORY ITEMS***/
        case 1:
        {
            addInventoryItems(inventoryFile,nameOfFile);
            break;
        }

        /***VIEW INVENTORY ITEMS***/
        case 2:
        {
            viewInventoryItems(inventoryFile,nameOfFile);
            break;
        }
        /***SEARCH INVENTORY ITEMS***/
        case 3:
        {
            searchInventoryItems();
            break;
        }
        /***EDIT INVENTORY ITEMS***/
        case 4:
        {
            editInventoryItems();
            break;
        }
        /***DELETE INVENTORY ITEMS***/
        case 5:
        {
            deleteInventoryItems();
            break;
        }
        /***ASSIGN INVENTORY ITEMS TO FACULTY MEMBERS***/
        case 6:
        {
            assignInventoryItems();
            break;
        }
        /***RETRIEVE INVENTORY ITEMS FROM FACULTY MEMBERS***/
        case 7:
        {
            retrieveInventoryItems();
            break;
        }
        /***VIEW LIST OF FACULTY MEMBERS WHO BORROWED ITEMS***/
        case 8:
        {
            viewFacultyListofBorrowedItems();
            break;
        }
        }
        cout<<endl<<endl;
    }
    return 0;
}

void addInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    InventoryItem addItem;
    cout<<"\nEnter Name of new Inventory Item:";
    cin.ignore();
    cin.getline(addItem.Name,50);

    cout<<"\nEnter Item ID of new Inventory Item:";
    cin>>addItem.Item_ID;

    cout<<"\nEnter category of new Inventory Item:";
    cin.ignore();
    cin.getline(addItem.Category,50);

    cout<<"\nEnter count of number new Inventory Items to add:";
    cin>>addItem.Item_count;

            /****OPENING FILE FOR ADDING INVENTORY ITEMS****/
    inventoryFile.open(nameOfFile.c_str(), ios :: app | ios:: binary);
    inventoryFile.write(reinterpret_cast<char*>(&addItem),sizeof(addItem));
    inventoryFile.close();
};

void viewInventoryItems(fstream &inventoryfile,string nameOfFile) {
    int count=1;
    InventoryItem viewItem;
    
            /****OPENING FILE FOR VIEWING INVENTORY ITEMS****/
    inventoryfile.open(nameOfFile.c_str(), ios :: in | ios::binary);
    if(!inventoryfile)
    {
        cout<<"\nPlease add some inventory items to view them!\n";
    }
    else
    {
        inventoryfile.read(reinterpret_cast<char*>(&viewItem),sizeof(viewItem));
        while(inventoryfile)
        {
            cout<<"\n"<<"Inventory item "<<count<<" :\n";
            cout<<"Name: "<<viewItem.Name;
            cout<<"\nItem_ID: "<<viewItem.Item_ID;
            cout<<"\nCategory: "<<viewItem.Category;
            cout<<"\nItem_count: "<<viewItem.Item_count<<endl;
            count++;
            inventoryfile.read(reinterpret_cast<char*>(&viewItem),sizeof(viewItem));
        }
    inventoryfile.close();
    }
};

void searchInventoryItems() {};

void editInventoryItems() {};

void deleteInventoryItems() {};

void assignInventoryItems() {};

void retrieveInventoryItems() {};

void viewFacultyListofBorrowedItems() {};
