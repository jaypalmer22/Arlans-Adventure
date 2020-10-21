/*
 Student Name: Jason Palmer
 Date: 03/27/2019

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
  HashTableEntry* newOne = (HashTableEntry *)malloc(sizeof(HashTableEntry)); // Malloc space for the size of the ht entry
  newOne->key = key; // set the new entry's key to the given key
  newOne->value = value; // set the new entry's value to the given value
  newOne->next = NULL; // set the new entry's next to NULL
  return newOne;
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
  int index = hashTable->hash(key); // Hash function returns the index of the bucket based on key
  HashTableEntry *node = hashTable->buckets[index]; // node is a pointer to the head of the bucket[index]
  while (node != NULL && node->key != key) // If the has table is empty and the keys don't match, check next node
    node = node->next; // Keep looking 
  return node;
 
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets contain indeterminant values, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

void destroyHashTable(HashTable* hashTable) {
  int num = hashTable->num_buckets; // Get number of buckets
  for (int i = 0; i < num; i++) {
    HashTableEntry *node = hashTable->buckets[i]; // Get head of current bucket
    if (node != NULL) {
      HashTableEntry *temp = node->next; // Get next value to scroll through
      while (temp != NULL && node != NULL) { // Scroll through the list and delete the nodes and their values
        free(node->value);
        free(node);
        node = temp;
        temp = temp->next;
      }
      free(node); // Free the last remaining node
    }
  }
  free(hashTable->buckets); // Free the buckets and then the ht
  free(hashTable);
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
  int index = hashTable->hash(key);
  HashTableEntry *node = findItem(hashTable,key);
  if (node == NULL) {
    HashTableEntry *newOne = createHashTableEntry(key,value); // Create new hashtable entry
    newOne->next = hashTable->buckets[index]; // Set the next of the new to the current head
    hashTable->buckets[index] = newOne; // Set the head to the current new entry
    return NULL; // If the key DNE return null
  } else { // If the key exists, replace it and return the old value
    void* old = node->value;
    node->value = value;
    return old; 
  }
}

void* getItem(HashTable* hashTable, unsigned int key) {
  HashTableEntry *node = findItem(hashTable,key); // Find the item we are looking for
  if (node == NULL) { // If you don't find it, return NULL
    return NULL; 
  } else { // If you find it, return it's value
    return (node->value);
  }
}

void* removeItem(HashTable* hashTable, unsigned int key) {
  HashTableEntry *node = findItem(hashTable,key);
  if (node != NULL) {
    HashTableEntry *previous = hashTable->buckets[hashTable->hash(key)]; // Get head of bucket
    while (previous->next != node && previous->next != NULL) // Find the previous node
      previous = previous-> next;
    if (node == hashTable->buckets[hashTable->hash(key)]) // If node is the head then change the head to the next node 
      hashTable->buckets[hashTable->hash(key)] = node->next; 
    else 
      previous->next = node->next; //If it's not the head, set the previous nodes next to node's next
  } else {
    return NULL; // If node is null, return null
  }
  void* val = node->value; // Store the value temporarily
  free(node); // free the node
  return val; // return the value
}
    
void deleteItem(HashTable* hashTable, unsigned int key) {
  free(removeItem(hashTable, key)); // Call remove and free the value that it returns as well
}
