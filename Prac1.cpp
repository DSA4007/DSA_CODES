#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
};

class Hash
{
private:
    int elements[10];      // Array to store inserted elements
    int elementCount;      // Count of inserted elements
    node *Hashtable[10];   // For chaining
    int LinearTable[10];   // For linear probing
    bool isOccupied[10];   // To track occupied slots in linear probing

public:
    Hash()
    {
        elementCount = 0;
        for (int i = 0; i < 10; i++)
        {
            elements[i] = -1; // Initialize with -1
            Hashtable[i] = NULL; // Initialize chaining table
            LinearTable[i] = -1; // Initialize linear probing table
            isOccupied[i] = false; // Mark all slots as unoccupied
        }
    }

    node *create(int val)
    {
        node *temp = new node;
        temp->data = val;
        temp->next = NULL;
        return temp;
    }

    int hashfunction(int data)
    {
        return (data % 10);
    }

    void insertElement(int data)
    {
        if (elementCount >= 10)
        {
            cout << "Cannot insert more elements. Array is full.\n";
            return;
        }
        elements[elementCount++] = data;
        cout << "Inserted " << data << " into elements array.\n";
    }

    void displayChaining()
    {
        // First, rebuild the chaining table based on inserted elements
        for (int i = 0; i < 10; i++)
            Hashtable[i] = NULL; // Reset chaining table

        for (int i = 0; i < elementCount; i++)
        {
            int ele = hashfunction(elements[i]);
            node *head = create(elements[i]);
            if (Hashtable[ele] == NULL)
            {
                Hashtable[ele] = head;
            }
            else
            {
                node *temp = Hashtable[ele];
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = head;
            }
        }

        // Display the chaining table
        cout << "Hashtable using Chaining:\n";
        for (int i = 0; i < 10; i++)
        {
            node *temp = Hashtable[i];
            cout << "Index " << i << ":- ";
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << "\n";
        }
    }

    void displayLinearProbing()
    {
        // First, rebuild the linear probing table based on inserted elements
        for (int i = 0; i < 10; i++)
        {
            LinearTable[i] = -1;    // Reset linear probing table
            isOccupied[i] = false; // Reset occupied slots
        }

        for (int i = 0; i < elementCount; i++)
        {
            int ele = hashfunction(elements[i]);
            for (int j = 0; j < 10; j++)
            {
                int idx = (ele + j) % 10; // Linear probing formula
                if (!isOccupied[idx])
                {
                    LinearTable[idx] = elements[i];
                    isOccupied[idx] = true;
                    break;
                }
            }
        }

        // Display the linear probing table
        cout << "Hashtable using Linear Probing:\n";
        for (int i = 0; i < 10; i++)
        {
            if (isOccupied[i])
                cout << LinearTable[i] << " ";
            else
                cout << "- ";
        }
        cout << "\n";
    }

    void deleteElement(int data, bool isChaining)
    {
        int index = hashfunction(data);

        if (isChaining)
        {
            // Delete in chaining
            node *temp = Hashtable[index];
            node *prev = NULL;

            while (temp != NULL && temp->data != data)
            {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL)
            {
                cout << "Element " << data << " not found in Chaining Table.\n";
                return;
            }

            if (prev == NULL)
            {
                Hashtable[index] = temp->next; // Update head
            }
            else
            {
                prev->next = temp->next; // Skip the node
            }

            delete temp;
            cout << "Element " << data << " deleted from Chaining Table.\n";
        }
        else
        {
            // Delete in linear probing
            for (int i = 0; i < 10; i++)
            {
                int idx = (index + i) % 10;
                if (isOccupied[idx] && LinearTable[idx] == data)
                {
                    LinearTable[idx] = -1;    // Mark the slot as empty
                    isOccupied[idx] = false; // Reset the occupied flag
                    cout << "Element " << data << " deleted from Linear Probing Table.\n";
                    return;
                }
            }
            cout << "Element " << data << " not found in Linear Probing Table.\n";
        }

        // Also remove from the elements array
        for (int i = 0; i < elementCount; i++)
        {
            if (elements[i] == data)
            {
                for (int j = i; j < elementCount - 1; j++)
                {
                    elements[j] = elements[j + 1];
                }
                elements[elementCount - 1] = -1;
                elementCount--;
                break;
            }
        }
    }
};

int main()
{
    Hash h;
    int ch, num;

    do
    {
        cout << "\nWelcome to Hashing Program!\n";
        cout << "1. Insert element\n";
        cout << "2. Display Hashtable using Chaining\n";
        cout << "3. Display Hashtable using Linear Probing\n";
        cout << "4. Delete Element\n";
        cout << "5. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter element you want to insert: ";
            cin >> num;
            h.insertElement(num); // Insert into the generic elements array
            break;

        case 2:
            h.displayChaining(); // Display using chaining
            break;

        case 3:
            h.displayLinearProbing(); // Display using linear probing
            break;

        case 4:
            cout << "Enter element you want to delete: ";
            cin >> num;
            cout << "Delete from (1) Chaining or (2) Linear Probing? ";
            int method;
            cin >> method;
            h.deleteElement(num, method == 1);
            break;

        case 5:
            cout << "Thank you for using the program!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (ch != 5);

    return 0;
}
