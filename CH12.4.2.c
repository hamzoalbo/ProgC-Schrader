/*
 * File: CH12.4.2.c
 * Project: Einführung in C - Schrader
 * Created Date: 2022-02-01, 3:38:26 pm
 * Author: Hamzenis Kryeziu
 * E-Mail: hamzenis.kryeziu@stud.fra-uas.de
 * -----
 * Last Modified: 2022-02-21, 4:23:42 pm
 * Modified By: Hamzenis Kryeziu
 * -----
 * Copyright (c) 2022
 *
 * Free for use
 * -----
 * HISTORY:
 * Date              		By		Comments
 * ------------------		----	----------------------------------------------------------
 * 2022-02-21, 4:03:31 pm	H.K.	Added Comments
 * 2022-02-20, 11:32:10 pm	H.K.	Neue Funktion addNoteSort()
 * 2022-02-01, 3:38:26 pm	H.K.	-start-
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    int day;
    int month;
    int year;
    char event[80];
};

// Define structure of a node
struct LinkedListNode {
    struct Data nodedata;

    // pointer to next node in list
    struct LinkedListNode* next;
};

/*
* define NodePointer as a pointer to a node in the list
* define NodePointer of data type struct LinkedList
*/
typedef struct LinkedListNode* NodePointer;

// creates a new empty node
NodePointer createNode() {

    // declare a node
    NodePointer ptrNewNode;

    // allocate memory for new node
    ptrNewNode = (NodePointer)malloc(sizeof(struct LinkedListNode));

    // check if allocation of memory was successful
    if (ptrNewNode == NULL) {
        fprintf(stderr, "\nUnable to allocate memory ");
        exit(-1);
    }

    // make next point to NULL
    ptrNewNode->next = NULL;
    // return the address of the new node
    return ptrNewNode;
}

// Print Funktion eines einzelnen Nodes (Für Debug Zwecke)
void printATest(NodePointer ptrNodeA) {
    printf("\n\%d-%02d-%02d - %s",
        ptrNodeA->nodedata.year,
        ptrNodeA->nodedata.month,
        ptrNodeA->nodedata.day,
        ptrNodeA->nodedata.event);
}

NodePointer addNodeEndOfList(NodePointer head,
    int year,
    int month,
    int day,
    char* event) {

    // pointer to newly created node
    NodePointer ptrNewNode;
    //used as pointer to nodes
    NodePointer ptrNode;

    // create new node and fill it with values
    ptrNewNode = createNode();

    // fill with values
    ptrNewNode->nodedata.year = year;
    ptrNewNode->nodedata.month = month;
    ptrNewNode->nodedata.day = day;
    strcpy(ptrNewNode->nodedata.event, event);

    // if list is empty make node the head of list
    if (head == NULL) {
        // when linked list is empty
        head = ptrNewNode;
    }
    else {
        // go to end of list
        // assign head to p
        ptrNode = head;

        // now traverse the list until p is the last node.
        // The last node always points to NULL.
        while (ptrNode->next != NULL) {
            ptrNode = ptrNode->next;
        }

        // Point the previous last node to the new node created.
        ptrNode->next = ptrNewNode;
    }

    // return the address of first node
    return head;
}

/*
* Ein Node wird nach Datum sortiert in die Linked List hinzugefügt.
* Nur wenn vorher mindestens ein Node vorhanden ist!
* Wenn kein Node vorhanden ist addNodeEndOfList() verwenden.
*/
NodePointer addNodeSort(NodePointer head,
    int year,
    int month,
    int day,
    char* event) {

    NodePointer ptrNewNode;
    NodePointer ptrNode;

    ptrNewNode = createNode();
    ptrNewNode->nodedata.year = year;
    ptrNewNode->nodedata.month = month;
    ptrNewNode->nodedata.day = day;
    strcpy(ptrNewNode->nodedata.event, event);

    ptrNode = head;

    /*
    * Linked List wird nacheinander durch gegangen
    * und jeder Node wird verglichen mit dem hinzuzufügenden nach Datum
    * bis er der lexikografisch nächste wäre.
    * Die nachfolgenden Nodes werden nach dem hinzugefügt.
    */
    NodePointer temp = ptrNode->next;
    while (ptrNode->next != NULL) {
        // Der Node vorher muss größer sein, als ptrNewNode
        if (ptrNode->nodedata.year <= ptrNewNode->nodedata.year) {
            if (ptrNode->nodedata.month <= ptrNewNode->nodedata.month) {
                if (ptrNode->nodedata.day <= ptrNewNode->nodedata.day) {
                    // Der Node nachher muss kleiner sein, als ptrNewNode
                    if (temp->nodedata.year >= ptrNewNode->nodedata.year) {
                        if (temp->nodedata.month >= ptrNewNode->nodedata.month) {
                            if (temp->nodedata.day >= ptrNewNode->nodedata.day) {                                
                                break;
                            }
                        }
                    }
                }
            }
        }
        /*
        * Falls die Bedingung nicht erfüllt wurden, 
        * wird die nächste Stelle gesucht
        */
        temp = temp->next;
        ptrNode = ptrNode->next;
    }

    /*
    * Einfügen des neuen Nodes an seinen lexikographischen Platz
    * 
    */
    ptrNode->next = ptrNewNode;
    ptrNewNode->next = temp;

    return head;

}

void printList(NodePointer head) {
    NodePointer ptrNode;
    ptrNode = head;
    while (ptrNode != NULL) {

        // print data of node
        printf("\n\%d-%02d-%02d - %s",
            ptrNode->nodedata.year,
            ptrNode->nodedata.month,
            ptrNode->nodedata.day,
            ptrNode->nodedata.event);

        // traverse to next node
        ptrNode = ptrNode->next;
    }
}

int main() {

    //pointer to first node of list
    NodePointer head = NULL;

    head = addNodeEndOfList(NULL, 2022, 1, 1, "New Year");
    addNodeEndOfList(head, 2022, 1, 18, "C Programming Lecture");
    addNodeEndOfList(head, 2022, 3, 20, "C Programming Exercise");
    addNodeEndOfList(head, 2022, 4, 25, "C Programming Exercise");
    addNodeEndOfList(head, 2022, 8, 28, "Restart of Lectures");
    addNodeEndOfList(head, 2022, 9, 4, "CTest2");

    addNodeSort(head, 2022, 1, 23, "CTEST");
    
    

    addNodeSort(head, 2022, 5, 2, "Debug");

    printList(head);
}