#pragma once

#include <Windows.h>

#include <cstdint>
#include <string.h>

const uint16_t MAX_TABLE_SIZE = 256;

struct HashEntry
{

private:
    uint64_t key;
    const char* value;
    HashEntry* next;
    HashEntry* prev;

public:
    HashEntry(uint64_t _key, const char* _value)
        : key(_key), value(_value), next(nullptr), prev(nullptr)
    { }

    void SetNext(HashEntry* _next)
    {
        if (this) next = _next;
    }

    void SetPrev(HashEntry* _prev)
    {
        if (this) prev = _prev;
    }

    void SetValue(const char * new_value)
    {
        if (this) value = new_value;
    }

    HashEntry* GetNext()
    {
        return next;
    }

    HashEntry* GetPrev()
    {
        return prev;
    }

    const char* GetValue()
    {
        if (this) return value;
    }

    uint64_t GetKey()
    {   
        return key;
    }

};

struct LinkedList
{

    HashEntry* head;

    LinkedList()
        : head(nullptr)
    { }

    void Push(HashEntry * new_head)
    {

        //Save the old head
        HashEntry* old_head = head;

        //Reassign the new head
        head = new_head;

        //Link the new head to the old head;
        head->SetPrev(nullptr);
        head->SetNext(old_head);

        //Link old head to new head
        old_head->SetPrev(new_head);

    }

    void Pop(const char *value)
    {

        HashEntry* hash_entry = Search(value);

        if (!hash_entry) return;

        hash_entry->GetPrev()->SetNext(hash_entry->GetNext());
        hash_entry->GetNext()->SetPrev(hash_entry->GetPrev());
        
        ZeroMemory(hash_entry, sizeof(hash_entry));

    }

    HashEntry* Search(const char* value)
    {

        for (HashEntry* current_entry = head; current_entry; current_entry = current_entry->GetNext())
        {

            if (current_entry->GetValue() == value)
                return current_entry;

        }

        return nullptr;

    }

};


class HashMap
{

    LinkedList** linked_lists;
public:

    HashMap()
    {

        linked_lists = new LinkedList * [MAX_TABLE_SIZE];

        //Populate hash list
        for (size_t i = 0; i < MAX_TABLE_SIZE; i++)
        {

            linked_lists[i] = new LinkedList();

        }

    }

    uint64_t HashFunc(const char* text)
    {

        uint64_t hash_key = 0;

        //Iterates through whole text and adds it to the key
        for (int i = 0; i < strlen(text); ++i)
        {

            //Iterates to the current character and adds it's int value to the key
            hash_key += (int8_t)text[i];

        }

        return hash_key % MAX_TABLE_SIZE;

    }

    void Insert(const char* value)
    {

        //Calc our index with hash function
        uint64_t index = HashFunc(value);
        //Index to our linked list
        LinkedList* linked_list = linked_lists[index];
        //Create new hash entry
        HashEntry* new_entry = new HashEntry(index, value);

        linked_list->Push(new_entry);
            
    }

    void Remove(const char* value)
    {

        //Calc the index
        uint64_t index = HashFunc(value);
        //Index to appropriate list
        LinkedList* linked_list = linked_lists[index];
        //Remove the entry from the linked list        
        linked_list->Pop(value);

    }

};