#include <iostream>
#include "HashMap.h"

int main()
{
   
    HashMap hash_map;

    hash_map.Insert("Hello Aidan! Excellent HashMap man!");
    hash_map.Insert("Hello !Aidan Excel!lent HashMap man");
    hash_map.Insert("Hello! Aidan Exc!ellent HashMap man");
    
    hash_map.Remove("Hello !Aidan Excel!lent HashMap man");

    return 0;

}