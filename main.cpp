#include <iostream>
#include <fstream>
#include <cstring>

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
void searchInventoryItems(fstream &,string);
void editInventoryItems(fstream &,string);
void deleteInventoryItems(fstream &,string);
void assignInventoryItems();
void retrieveInventoryItems();
void viewFacultyListofBorrowedItems();

bool validationForEmptyFile(fstream &);
bool validationForNULLItemId(const int&,string);

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
            searchInventoryItems(inventoryFile,nameOfFile);
            break;
        }
        /***EDIT INVENTORY ITEMS***/
        case 4:
        {
            editInventoryItems(inventoryFile,nameOfFile);
            break;
        }
        /***DELETE INVENTORY ITEMS***/
        case 5:
        {
            deleteInventoryItems(inventoryFile,nameOfFile);
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

void viewInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    int count=1;
    InventoryItem viewItem;

    /****OPENING FILE FOR VIEWING INVENTORY ITEMS****/
    inventoryFile.open(nameOfFile.c_str(), ios :: in | ios::binary);
    if(validationForEmptyFile(inventoryFile)==0)
    {
        inventoryFile.close();
        return;
    }
    else
    {
        inventoryFile.seekg(0,ios::beg);
        inventoryFile.read(reinterpret_cast<char*>(&viewItem),sizeof(viewItem));
        while(!inventoryFile.eof())
        {
            cout<<"\n"<<"Inventory item "<<count<<" :\n";
            cout<<"Name: "<<viewItem.Name;
            cout<<"\nItem_ID: "<<viewItem.Item_ID;
            cout<<"\nCategory: "<<viewItem.Category;
            cout<<"\nItem_count: "<<viewItem.Item_count<<endl;
            count++;
            inventoryFile.read(reinterpret_cast<char*>(&viewItem),sizeof(viewItem));
        }
    }
    inventoryFile.close();
};

void searchInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    char searchItemName[50];
    InventoryItem searchItem;

    /****OPENING FILE FOR SEARCHING INVENTORY ITEMS****/
    inventoryFile.open(nameOfFile.c_str(), ios :: in | ios::binary);
    if(validationForEmptyFile(inventoryFile)==0)
    {
        inventoryFile.close();
        return;
    }
    else
    {
        inventoryFile.seekg(0,ios::beg);
        cout<<"\nEnter item name of item to search:";
        cin.ignore();
        cin.getline(searchItemName,50);

        inventoryFile.read(reinterpret_cast<char*>(&searchItem),sizeof(searchItem));
        while(!inventoryFile.eof())
        {
            if(strcmp(searchItemName,searchItem.Name)==0)
            {
                cout<<"\nName: "<<searchItem.Name;
                cout<<"\nItem_ID: "<<searchItem.Item_ID;
                cout<<"\nCategory: "<<searchItem.Category;
                cout<<"\nItem_count: "<<searchItem.Item_count<<endl;
                break;
            }
            inventoryFile.read(reinterpret_cast<char*>(&searchItem),sizeof(searchItem));
        }
    }
    inventoryFile.close();

};

void editInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    int editItemID;
    InventoryItem editItem,newItem;

    /****OPENING FILE FOR EDITING INVENTORY ITEMS****/
    inventoryFile.open(nameOfFile.c_str(),ios :: out | ios :: in | ios::binary);
    if(validationForEmptyFile(inventoryFile)==0)
    {
        inventoryFile.close();
        return;
    }
    else
    {
        inventoryFile.seekg(0,ios::beg);
        cout<<"\nEnter item id of item to be edited:";
        cin>>editItemID;
        while(validationForNULLItemId(editItemID,nameOfFile)==0){
            cout<<"\nItem ID not found!\n";
            cout<<"\nEnter valid item id of item to be edited:";
            cin>>editItemID;
        }

        inventoryFile.read(reinterpret_cast<char*>(&editItem),sizeof(editItem));
        while(!inventoryFile.eof())
        {
            if(editItemID==editItem.Item_ID)
            {
                cout<<"\nEnter name to edit: ";
                cin.ignore();
                cin.getline(newItem.Name,50);
                cout<<"Enter category to edit:";
                cin.getline(newItem.Category,50);
                cout<<"Enter count of item to edit:";
                cin>>newItem.Item_count;
                newItem.Item_ID=editItemID;
                cout<<"\nEdited Successfully!\n";
                inventoryFile.seekg(-sizeof(editItem),ios::cur);
                inventoryFile.write(reinterpret_cast<char*>(&newItem),sizeof(newItem));
                break;
            }
            inventoryFile.read(reinterpret_cast<char*>(&editItem),sizeof(editItem));
        }
    }
    inventoryFile.close();

};

void deleteInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    int deleteItemID;
    InventoryItem deleteItem;

    /****OPENING FILE FOR DELETING INVENTORY ITEMS****/
    inventoryFile.open(nameOfFile.c_str(),ios :: out | ios :: in | ios::binary);
    if(validationForEmptyFile(inventoryFile)==0)
    {
        inventoryFile.close();
        return;
    }
    else
    {
        inventoryFile.seekg(0,ios::beg);
        cout<<"\nEnter Item ID of inventory item to delete:";
        cin>>deleteItemID;
        while(validationForNULLItemId(deleteItemID,nameOfFile)==0){
            cout<<"\nItem ID not found!\n";
            cout<<"\nEnter valid item id of item to be deleted:";
            cin>>deleteItemID;
        }

        /***Making a new FILE to replace it with old file with deleted item***/
        ofstream updatedinventoryFile("xyz.txt",ios::binary);
        inventoryFile.read(reinterpret_cast<char*>(&deleteItem),sizeof(deleteItem));
        while(!inventoryFile.eof())
        {
            if(deleteItemID!=deleteItem.Item_ID)
            {
                updatedinventoryFile.write(reinterpret_cast<char*>(&deleteItem),sizeof(deleteItem));
            }
            inventoryFile.read(reinterpret_cast<char*>(&deleteItem),sizeof(deleteItem));
        }
        updatedinventoryFile.close();
    }
    cout<<"\nDeleted Successfully!\n";
    inventoryFile.close();
    remove(nameOfFile.c_str());
    rename("xyz.txt",nameOfFile.c_str());

};

void assignInventoryItems() {};

void retrieveInventoryItems() {};

void viewFacultyListofBorrowedItems() {};

///////////////*VALIDATION FUNCTIONS*//////////////
bool validationForNULLItemId(const int &itemID,string nameOfFile){
    InventoryItem temp;
    ifstream file(nameOfFile.c_str(),ios :: in | ios::binary);
    file.read(reinterpret_cast<char*>(&temp),sizeof(temp));
    while(!file.eof())
        {
            if(itemID==temp.Item_ID)
            {
                file.close();
                return 1;
            }
           file.read(reinterpret_cast<char*>(&temp),sizeof(temp));
        }
        file.close();
        return 0;
}
bool validationForEmptyFile(fstream &inventoryFile)
{
    inventoryFile.seekg(0,ios::end);
    if(!inventoryFile || inventoryFile.tellg()==0)  //check for empty file for
    {
        cout<<"\nPlease add some inventory items first!\n";
        inventoryFile.seekg(0,ios::beg);
        return 0;
    }
    return 1;
}