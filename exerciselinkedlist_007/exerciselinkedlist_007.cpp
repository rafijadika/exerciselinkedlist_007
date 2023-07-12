#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode(); //menambah node
    bool search(int rollno, Node** Rafi, Node** Jadika); //mencari node 
    bool listEmpty(); //mengecek linked list kosong
    bool delNode(); //menghapus node
    void traverse(); //menampilkan semua linked list
};

void CircularLinkedList::addNode() {
    Node* newNode = new Node();
    cout << "\nEnter roll number: ";
    cin >> newNode->rollNumber;
    cout << "Enter name: ";
    cin >> newNode->name;

    if (listEmpty()) { //jika linked list kosong
        newNode->next = newNode;
        LAST = newNode;
    }
    else { //linked list tidak kosong
        Node* rafi = LAST->next;
        Node* jadika = NULL;

        do {
            jadika = rafi;
            rafi = rafi->next;
        } while (rafi != LAST->next && rafi->rollNumber < newNode->rollNumber);

        jadika->next = newNode;
        newNode->next = rafi;

        if (rafi == LAST->next) {  //memasukan awal
            LAST->next = newNode;
        }
        if (rafi == LAST) { //memasukan akhir
            LAST = newNode;
        }
    }

    cout << "Node added successfully!" << endl;
}

bool CircularLinkedList::search(int rollno, Node** jadika, Node** rafi) {
    *jadika = LAST->next;
    *rafi = LAST->next;

    while (*rafi != LAST) {
        if (rollno == (*rafi)->rollNumber) {
            return true;
        }
        *jadika = *rafi;
        *rafi = (*rafi)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "\nList is empty. Deletion failed!" << endl;
        return false;
    }

    int rollno;
    cout << "\nEnter roll number to delete: ";
    cin >> rollno;

    Node* jadika = NULL;
    Node* rafi = NULL;

    if (!search(rollno, &jadika, &rafi)) { //jika mencari node
        cout << "Node not found. Deletion failed!" << endl; //hasil pencarian gagal
        return false;
    }

    if (jadika == rafi) { //jika hanya satu node di linkedlist
        LAST = NULL;
        delete rafi; //menghapus salh satu node
        cout << "Node deleted successfully!" << endl; //menghapus node berhasil
        return true;
    }

    if (rafi == LAST) {
        LAST = jadika;
    }

    jadika->next = rafi->next;
    delete rafi;

    cout << "Node deleted successfully!" << endl;
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) { //memeriksa list 
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n"; //merekam semua list
        Node* rafiNode = LAST->next;

        while (rafiNode != LAST) {
            cout << rafiNode->rollNumber << " " << rafiNode->name << endl;
            rafiNode = rafiNode->next;
        }

        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}