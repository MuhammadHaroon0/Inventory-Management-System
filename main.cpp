#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct Allocated_to
{
    char name[50];
    int facultyId;
    int numberOFItems;
};
struct InventoryItem
{
    char Name[50];
    int Item_ID;
    char Category[50];
    int Item_count;
    Allocated_to Allocated_to[56];
    int lastCount;
};

void addInventoryItems(fstream &,string);
void viewInventoryItems(fstream &,string);
void searchInventoryItems(fstream &,string);
void editInventoryItems(fstream &,string);
void deleteInventoryItems(fstream &,string);
void assignInventoryItems(fstream &,string);
void retrieveInventoryItems(fstream &,string);
void viewFacultyListofBorrowedItems(fstream &,string);

bool validationForNegativeInput(const int &);
bool validationForEmptyFile(fstream &);
bool validationForWrongItemId(const int&,string);
bool validationForWrongItemName(char [],string);

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
            assignInventoryItems(inventoryFile,nameOfFile);
            break;
        }
        /***RETRIEVE INVENTORY ITEMS FROM FACULTY MEMBERS***/
        case 7:
        {
            retrieveInventoryItems(inventoryFile,nameOfFile);
            break;
        }
        /***VIEW LIST OF FACULTY MEMBERS WHO BORROWED ITEMS***/
        case 8:
        {
            viewFacultyListofBorrowedItems(inventoryFile,nameOfFile);
            break;
        }
        }
        cout<<endl<<endl;
    }
    return 0;
}

///////////////////////////////////////////MAIN WORKING FUNCTIONS////////////////////////////////////////////

void addInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    /****OPENING FILE FOR ADDING INVENTORY ITEMS****/
    inventoryFile.open(nameOfFile.c_str(), ios :: app | ios:: binary);
    InventoryItem addItem;
    cout<<"\nEnter Name of new Inventory Item:";
    cin.ignore();
    cin.getline(addItem.Name,50);

    cout<<"\nEnter Item ID of new Inventory Item:";
    cin>>addItem.Item_ID;
    while(validationForNegativeInput(addItem.Item_ID)==1)
    {
        cout<<"\nEnter Valid Item ID!\n";
        cout<<"\nEnter Item ID of new Inventory Item:";
        cin>>addItem.Item_ID;
    }

    while(validationForWrongItemId(addItem.Item_ID,nameOfFile)==1)
    {
        cout<<"\nItem ID already present!\n";
        cout<<"\nEnter unique item id of item to be added:";
        cin>>addItem.Item_ID;
    }

    cout<<"\nEnter category of new Inventory Item:";
    cin.ignore();
    cin.getline(addItem.Category,50);

    cout<<"\nEnter count of number of new Inventory Items to add:";
    cin>>addItem.Item_count;

    while(validationForNegativeInput(addItem.Item_count)==1)
    {
        cout<<"\nEnter Valid Item Count!\n";
        cout<<"\nEnter count of number of new Inventory Items to add:";
        cin>>addItem.Item_count;
    };
    addItem.lastCount=0;

    inventoryFile.write(reinterpret_cast<char*>(&addItem),sizeof(addItem));
    inventoryFile.close();
    cout<<"\nAdded Successfully!\n";
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
        cout<<"____________________________________________________________________________________________\n";
            cout<<"\n"<<left<<setw(20)<<"Inventory item"<<setw(20)<<"Name";
            cout<<setw(20)<<"Item_ID"<<setw(20)<<"Category"<<setw(12)<<"Item_count"<<"|"<<endl;
        while(!inventoryFile.eof())
        {
            cout<<left<<setw(20)<<count;
            cout<<setw(20)<<viewItem.Name;
            cout<<setw(20)<<viewItem.Item_ID;
            cout<<setw(20)<<viewItem.Category;
            cout<<setw(12)<<viewItem.Item_count;
            cout<<"|"<<endl;
            count++;
            inventoryFile.read(reinterpret_cast<char*>(&viewItem),sizeof(viewItem));
        }
    }
            cout<<"____________________________________________________________________________________________";

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

        while(validationForWrongItemName(searchItemName,nameOfFile)==0)
        {
            cout<<"\nItem not found!\n";
            cout<<"\nEnter valid item name of item to be searched:";
            cin.getline(searchItemName,50);
        }

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
    InventoryItem editItem;

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
        while(validationForWrongItemId(editItemID,nameOfFile)==0)
        {
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
                cin.getline(editItem.Name,50);
                cout<<"Enter category to edit:";
                cin.getline(editItem.Category,50);
                cout<<"Enter count of item to edit:";
                cin>>editItem.Item_count;
                cout<<"\nEdited Successfully!\n";
                inventoryFile.seekp(-1*sizeof(editItem),ios::cur);
                inventoryFile.write(reinterpret_cast<char*>(&editItem),sizeof(editItem));
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
        while(validationForWrongItemId(deleteItemID,nameOfFile)==0)
        {
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


void assignInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    bool flag=0;
    int assignItemID,assignFacultyID;
    InventoryItem assignItem;

    /****OPENING FILE FOR ADDING INVENTORY ITEMS****/
    inventoryFile.open(nameOfFile.c_str(),ios :: out | ios :: in | ios::binary);
    if(validationForEmptyFile(inventoryFile)==0)
    {
        inventoryFile.close();
        return;
    }

    cout<<"Enter ID of item to assign to faculty member:";
    cin>>assignItemID;
    while(validationForWrongItemId(assignItemID,nameOfFile)==0)
    {
        cout<<"\nItem ID not found!\n";
        cout<<"\nEnter valid item id of item to be assigned:";
        cin>>assignItemID;
    }

    cout<<"Enter ID of Faculty member to assign item:";
    cin>>assignFacultyID;
    while(validationForNegativeInput(assignFacultyID)==1)
    {
        cout<<"\nEnter Valid Faculty ID!\n";
        cout<<"Enter ID of Faculty member to assign item:";
        cin>>assignFacultyID;
    };

    inventoryFile.read(reinterpret_cast<char*>(&assignItem),sizeof(assignItem));
    while(!inventoryFile.eof())
    {
        if(assignItemID==assignItem.Item_ID)
        {
            if(assignItem.Item_count<=0)  //cant assign if no more item left
            {
                cout<<"\nCannot Assign this Item, Don't Have anymore "<<assignItem.Name<<" left\n";
                inventoryFile.close();
                return;
            }
            for(int i=0; i<assignItem.lastCount; i++)
            {
                if(assignFacultyID==assignItem.Allocated_to[i].facultyId) //faculty member already present
                {
                    assignItem.Item_count--;
                    assignItem.Allocated_to[i].numberOFItems++;

                    inventoryFile.seekp(-1*sizeof(assignItem),ios::cur);
                    inventoryFile.write(reinterpret_cast<char*>(&assignItem),sizeof(assignItem));
                    cout<<"\nAssigned Successfully\n";
                    flag=1;
                    break;
                }
            }
            if(flag==0) //faculty member not already present
            {
                cout<<"Enter Name of Faculty member to assign item:";
                cin.ignore();
                cin.getline(assignItem.Allocated_to[assignItem.lastCount].name,50);
                assignItem.Item_count--;
                assignItem.Allocated_to[assignItem.lastCount].facultyId=assignFacultyID;
                assignItem.Allocated_to[assignItem.lastCount].numberOFItems=1;
                assignItem.lastCount++; //incrementing the array to assign next in next blank space

                inventoryFile.seekp(-1*sizeof(assignItem),ios::cur);
                inventoryFile.write(reinterpret_cast<char*>(&assignItem),sizeof(assignItem));
                cout<<"\nAssigned Successfully\n";
            }
            break;
        }
        inventoryFile.read(reinterpret_cast<char*>(&assignItem),sizeof(assignItem));
    }
    inventoryFile.close();
};


void retrieveInventoryItems(fstream &inventoryFile,string nameOfFile)
{
    bool flag=0;
    int retrieveItemID,retrieveFacultyID;

    inventoryFile.open(nameOfFile.c_str(), ios :: in | ios::binary);
    if(validationForEmptyFile(inventoryFile)==0)
    {
        inventoryFile.close();
        return;
    }
    InventoryItem retrieveItem;
    cout<<"Enter ID of item to retrieve from faculty member:";
    cin>>retrieveItemID;
    while(validationForWrongItemId(retrieveItemID,nameOfFile)==0)
    {
        cout<<"\nItem ID not found!\n";
        cout<<"Enter ID of item to retrieve from faculty member:";
        cin>>retrieveItemID;
    }
    cout<<"Enter ID of Faculty member to retrieve item:";
    cin>>retrieveFacultyID;
    while(validationForNegativeInput(retrieveFacultyID)==1)
    {
        cout<<"\nEnter Valid Faculty ID!\n";
        cout<<"Enter ID of Faculty member to retrieve item:";
        cin>>retrieveFacultyID;
    };

    ofstream updatedinventoryFile("xyz.txt",ios::binary);
    inventoryFile.read(reinterpret_cast<char*>(&retrieveItem),sizeof(retrieveItem));
    while(!inventoryFile.eof())
    {
        flag=0;
        if(retrieveItemID==retrieveItem.Item_ID)
        {
            for(int i=0; i<retrieveItem.lastCount; i++)
            {
                if(retrieveFacultyID==retrieveItem.Allocated_to[i].facultyId)
                {
                    retrieveItem.Item_count+=retrieveItem.Allocated_to[i].numberOFItems;
                    retrieveItem.lastCount--;
                    for(int j=i;j<retrieveItem.lastCount;j++){
                        strcpy(retrieveItem.Allocated_to[j].name,retrieveItem.Allocated_to[j+1].name);
                    retrieveItem.Allocated_to[j].numberOFItems=retrieveItem.Allocated_to[j+1].numberOFItems;
                    retrieveItem.Allocated_to[j].facultyId=retrieveItem.Allocated_to[j+1].facultyId;
                    }
                    flag=1;
                    updatedinventoryFile.write(reinterpret_cast<char*>(&retrieveItem),sizeof(retrieveItem));
                    cout<<"\nRetrieved Successfully!\n";
                    break;
                }
            }
            if(flag==0)
            {
                cout<<"\nFaculty Member already not assigned with this item!\n";
            }
        }
        if(flag==0)
        {
            updatedinventoryFile.write(reinterpret_cast<char*>(&retrieveItem),sizeof(retrieveItem));
        }
        inventoryFile.read(reinterpret_cast<char*>(&retrieveItem),sizeof(retrieveItem));
    }
    inventoryFile.close();
    updatedinventoryFile.close();
    remove(nameOfFile.c_str());
    rename("xyz.txt",nameOfFile.c_str());
};


void viewFacultyListofBorrowedItems(fstream &inventoryFile,string nameOfFile)
{
    bool flag=0;
    inventoryFile.open(nameOfFile.c_str(), ios :: in | ios::binary);
    if(validationForEmptyFile(inventoryFile)==0)
    {
        inventoryFile.close();
        return;
    }
    InventoryItem viewFacultyList;
    inventoryFile.read(reinterpret_cast<char*>(&viewFacultyList),sizeof(viewFacultyList));
    while(!inventoryFile.eof())
    {

        if(viewFacultyList.lastCount>0)
        {
            for(int i=0; i<viewFacultyList.lastCount; i++)
            {

                cout<<"\nName of item: "<<viewFacultyList.Name;
                cout<<"\nName of Person: "<<viewFacultyList.Allocated_to[i].name;
                cout<<"\nFaculty ID: "<<viewFacultyList.Allocated_to[i].facultyId;
                cout<<"\nNumber of items: "<<viewFacultyList.Allocated_to[i].numberOFItems;
                flag=1;
                cout<<"\n";
            }
        }
        inventoryFile.read(reinterpret_cast<char*>(&viewFacultyList),sizeof(viewFacultyList));
    }
    if(flag==0)
    {
        cout<<"\nNothing to show yet!";
    }
    inventoryFile.close();

};

/////////////////////////////////////////////*VALIDATION FUNCTIONS*///////////////////////////////////////////////
bool validationForNegativeInput(const int &input)
{
    if(input<=0)
    {
        return 1;
    }
    return 0;
}


bool validationForWrongItemId(const int &itemID,string nameOfFile)
{
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


bool validationForWrongItemName(char str[],string nameOfFile)
{
    InventoryItem temp;
    ifstream file(nameOfFile.c_str(),ios :: in | ios::binary);
    file.read(reinterpret_cast<char*>(&temp),sizeof(temp));
    while(!file.eof())
    {
        if(strcmp(str,temp.Name)==0)
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
    inventoryFile.seekg(0,ios::beg);
    return 1;
}
