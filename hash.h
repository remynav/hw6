#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

      unsigned long long w[5];
      for(int i = 0; i< 5; i++){
        w[i] = 0;
      }

      //build w[4]
      int end = (int)k.size();
      int wi = 4;

      while( end > 0 && wi >=0){
        int start = end - 6;
        if(start < 0){
          start = 0;
        }

          unsigned long long value = 0;

          //conversion
          for(int i = start; i < end; i++){
            value = value *36 + (unsigned long long)letterDigitToNumber(k[i]);
          }

          w[wi] = value;
          wi--;
          end = start;
      }
        

        unsigned long long h =0;
        for(int i = 0; i < 5; i++){
          h += (unsigned long long)rValues[i] * w[i];
        }

      return (HASH_INDEX_T)h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        
        //uppercase to lowercase
        if(letter >= 'A' && letter <= 'Z'){
          letter = static_cast<char>(letter - 'A' + 'a');
        }

        //a-z to 0-25
        if(letter >= 'a' && letter <= 'z'){
          return static_cast<HASH_INDEX_T>(letter - 'a');
        }

        //0-9 to 26-35
        if(letter >= '0' && letter <= '9'){
          return static_cast<HASH_INDEX_T>(26 + (letter - '0'));
        }

        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
