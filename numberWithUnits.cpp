#include <iostream>
#include <fstream>
#include <sstream>
#include "NumberWithUnits.hpp"
#include <map>
#include <list>
 
using namespace std;
 
namespace ariel {
    map<string, map<string, double>> convert;
    
    void NumberWithUnits::read_units(ifstream& f) {
        double value1, value2;
        
        char c;
        
        string type1, type2;
        
        list<string> types;
        
        while(f.good()) {
            f >> value1 >> type1 >> c >> value2 >> type2;
        
            convert[type1][type2] = value2 / value1;
            convert[type2][type1] = value1 / value2;
            
            cout << convert[type1][type2] << " " << type1 << "-->" << convert[type2][type1] << " " << type2 << endl;
            bool found1 = (std::find(types.begin(), types.end(), type1) != types.end());
            bool found2 = (std::find(types.begin(), types.end(), type2) != types.end());
            
            if(!found1) types.insert(types.end(), type1);
            if(!found2) types.insert(types.end(), type2);
        }
        /* Mistake */
        
        for(string a : types) {
            convert[a][a] = 1;
            
            for(string b : types) {
                for(string c : types) {
                    if(convert[a][b] != INVALID && convert[b][c] != INVALID)
                        convert[a][c] = convert[a][b] * convert[b][c];
                }
            }
        }
    }   
    
    NumberWithUnits operator+(NumberWithUnits const &a, NumberWithUnits const &b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem8");
            
        const double value = (a.value + (convert[b.type][a.type] * b.value));
        
        return NumberWithUnits(value, a.type);
    }
    
    NumberWithUnits operator-(NumberWithUnits const &a, NumberWithUnits const &b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem7");
            
        const double value = (a.value - (convert[b.type][a.type] * b.value));
 
        return NumberWithUnits(value, a.type);
    }
    
    NumberWithUnits operator-(NumberWithUnits const &a) {
        return NumberWithUnits(-a.value, a.type);
    }
    NumberWithUnits operator+(NumberWithUnits const &a) {
        return NumberWithUnits(a.value, a.type);
    }
    
    NumberWithUnits operator*(NumberWithUnits a, double mul) {
        return NumberWithUnits(a.value * mul, a.type);
    }
     
    NumberWithUnits operator*(double mul, NumberWithUnits a) {
        return NumberWithUnits(a.value * mul, a.type);
    }
    
    bool operator>(NumberWithUnits a, NumberWithUnits b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem6");
            
        return a.value > convert[b.type][a.type] * b.value;
    }
    
    bool operator>=(NumberWithUnits a, NumberWithUnits b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem5");
            
        return a.value >= convert[b.type][a.type] * b.value;
    }
    
    bool operator<(NumberWithUnits a, NumberWithUnits b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem4");
            
        return a.value < convert[b.type][a.type] * b.value;
    }
    
    bool operator<=(NumberWithUnits a, NumberWithUnits b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem3");
            
        return a.value <= convert[b.type][a.type] * b.value;
    }
    
    bool operator==(NumberWithUnits a, NumberWithUnits b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem1");
        
        stringstream a1,b1;
        
        a1 << a.value;
        b1 << (convert[b.type][a.type] * b.value);
 
        return (a1.str() == b1.str());
    }
    
    bool operator!=(NumberWithUnits a, NumberWithUnits b) {
        if(convert[b.type][a.type] == INVALID)
            throw out_of_range("Problem2");
            
        stringstream a1,b1;
        
        a1 << a.value;
        b1 << (convert[b.type][a.type] * b.value);
 
        return (a1.str() != b1.str());
    }
}