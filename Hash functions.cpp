#include <iostream>
#include <string>

using namespace std;

// Define the hash table class
class hashT {
private:
    static const int tableSize = 10; // Constant for table size
    struct item { // Define structure for each item in the hash table
        string name;
        int age;
        item* next; // Pointer to the next item (for handling collisions)
    };
    item* HashTable[tableSize]; // Array of pointers to items (the hash table itself)
public:
    // Constructor and Destructor
    hashT();
    ~hashT();
    // Hash function to generate index for a given key
    int Hash(string key);
    // Function to add an item to the hash table
    void AddItem(string name, int age);
    // Function to count the number of items in a specific index
    int NumberOfItemsInIndex(int index);
    // Function to print the entire hash table
    void PrintTable();
    // Function to print items at a specific index
    void PrintItemsInIndex(int index);
    // Function to search for an item by name
    bool Search(string name);
    // Function to check if an item exists at a specific index
    bool IsItemAtEqual(int index, string name);
    // Function to retrieve an item by name
    void Retrieve(string name);
    // Function to remove an item by name
    void RemoveItem(string name);
};

// Constructor: Initialize hash table with null pointers
hashT::hashT() {
    for (int i = 0; i < tableSize; i++) {
        HashTable[i] = nullptr;
    }
}

// Destructor: Delete all items in the hash table
hashT::~hashT() {
    for (int i = 0; i < tableSize; i++) {
        item* Ptr = HashTable[i];
        while (Ptr != nullptr) {
            item* delPtr = Ptr;
            Ptr = Ptr->next;
            delete delPtr;
        }
    }
}

// Hash function: Generate index for a given key
int hashT::Hash(string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += (int)key[i];
    }
    return hash % tableSize;
}

// Function to add an item to the hash table
void hashT::AddItem(string name, int age) {
    int index = Hash(name);
    item* newItem = new item;
    newItem->name = name;
    newItem->age = age;
    newItem->next = nullptr;
    if (HashTable[index] == nullptr) {
        HashTable[index] = newItem;
    } else {
        item* Ptr = HashTable[index];
        while (Ptr->next != nullptr) {
            Ptr = Ptr->next;
        }
        Ptr->next = newItem;
    }
}

// Function to count the number of items in a specific index
int hashT::NumberOfItemsInIndex(int index) {
    int count = 0;
    item* Ptr = HashTable[index];
    while (Ptr != nullptr) {
        count++;
        Ptr = Ptr->next;
    }
    return count;
}

// Function to print the entire hash table
void hashT::PrintTable() {
    for(int i = 0; i < tableSize; i++) {
        cout << "--------------------\n";
        cout << "index = " << i << endl;
        cout << "# of Items: " << NumberOfItemsInIndex(i) << endl;
        PrintItemsInIndex(i);
        cout << " \n";
    }
}

// Function to print items at a specific index
void hashT::PrintItemsInIndex(int index) {
    item* Ptr = HashTable[index];
    if (Ptr == nullptr) {
        cout << "Empty" << endl;
    } else {
        while (Ptr != nullptr) {
            cout << Ptr->name << ": " << Ptr->age << endl;
            Ptr = Ptr->next;
        }
        cout << endl;
    }
}

// Function to search for an item by name
bool hashT::Search(string name) {
    int index = Hash(name);
    item* Ptr = HashTable[index];
    while (Ptr != nullptr) {
        if (Ptr->name == name) {
            return true;
        }
        Ptr = Ptr->next;
    }
    return false;
}

// Function to check if an item exists at a specific index
bool hashT::IsItemAtEqual(int index, string name) {
    item* Ptr = HashTable[index];
    while (Ptr != nullptr) {
        if (Ptr->name == name) {
            return true;
        }
        Ptr = Ptr->next;
    }
    return false;
}

// Function to retrieve an item by name
void hashT::Retrieve(string name) {
    int index = Hash(name);
    item* Ptr = HashTable[index];
    while (Ptr != nullptr) {
        if (Ptr->name == name) {
            cout << "Item found at index " << index << ": " << Ptr->name << ", " << Ptr->age << endl;
            return;
        }
        Ptr = Ptr->next;
    }
    cout << "Item not found." << endl;
}

// Function to remove an item by name
void hashT::RemoveItem(string name) {
    int index = Hash(name);
    item* delPtr;
    item* P1;
    item* P2;

    if (HashTable[index] == nullptr) {
        cout << name << " was not found in the Hash Table" << endl;
        return;
    }

    if (HashTable[index]->name == name) {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;
        cout << name << " was removed from the Hash Table" << endl;
    } else {
        P1 = HashTable[index]->next;
        P2 = HashTable[index];

        while (P1 != nullptr && P1->name != name) {
            P2 = P1;
            P1 = P1->next;
        }

        if (P1 == nullptr) {
            cout << name << " was not found in the Hash Table" << endl;
        } else {
            delPtr = P1;
            P1 = P1->next;
            P2->next = P1;
            delete delPtr;
            cout << name << " was removed from the Hash Table" << endl;
        }
    }
}

// Main function to test the hash table
int main() {
    // Create an instance of the hashT class
    hashT myHashTable;

    // Add items to the hash table
    myHashTable.AddItem("Mike", 31);
    myHashTable.AddItem("Rondy", 72);
    myHashTable.AddItem("Sue", 55);
    myHashTable.AddItem("Monique", 22);
    myHashTable.AddItem("Joe", 19);
    myHashTable.AddItem("Mike", 14); // Adding another item with the same name
    myHashTable.AddItem("Tom", 26);
    myHashTable.AddItem("Bill", 97);
    myHashTable.AddItem("Janice", 48);
    myHashTable.AddItem("Marcus", 11);

    // Print the entire hash table
    cout << "Hash Table with Hash Function 1:" << endl;
    myHashTable.PrintTable();

    // Create an instance of the hashT class with different hash function
    hashT myHashTable2;

    // Add items to the hash table with different hash function
    myHashTable2.AddItem("Mike", 31);
    myHashTable2.AddItem("Rondy", 72);
    myHashTable2.AddItem("Sue", 55);
    myHashTable2.AddItem("Monique", 22);
    myHashTable2.AddItem("Joe", 19);
    myHashTable2.AddItem("Mike", 14);
    myHashTable2.AddItem("Tom", 26);
    myHashTable2.AddItem("Bill", 97);
    myHashTable2.AddItem("Janice", 48);
    myHashTable2.AddItem("Marcus", 11);

    // Print the entire hash table
    cout << "\nHash Table with Hash Function 2:" << endl;
    myHashTable2.PrintTable();

    // Create an instance of the hashT class with different hash function
    hashT myHashTable3;

    // Add items to the hash table with different hash function
    myHashTable3.AddItem("Mike", 31);
    myHashTable3.AddItem("Rondy", 72);
    myHashTable3.AddItem("Sue", 55);
    myHashTable3.AddItem("Monique", 22);
    myHashTable3.AddItem("Joe", 19);
    myHashTable3.AddItem("Mike", 14);
    myHashTable3.AddItem("Tom", 26);
    myHashTable3.AddItem("Bill", 97);
    myHashTable3.AddItem("Janice", 48);
    myHashTable3.AddItem("Marcus", 11);

    // Print the entire hash table
    cout << "\nHash Table with Hash Function 3:" << endl;
    myHashTable3.PrintTable();

    return 0;
}

