#pragma once
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
 
using namespace std;
 
#define INVALID 0
 
namespace ariel {
    extern map<string, map<string, double>> convert;
    
    class NumberWithUnits {
    private:
        double value;
        string type;
        
    public:
        static void read_units(ifstream& f);
        
        NumberWithUnits() : value(0.0), type("none") { }
        NumberWithUnits(double v, string t) {
            stringstream s;
            stringstream a, b;
            
            s << "Type: " << t << " " << "Value: " << convert[t][t] << " is not 1";
            a << convert[t][t];
            b << 1;
            
            if (a.str() != b.str())
                throw std::out_of_range(s.str());
                
            this->value = v;
            this->type = t;
        }
        
        NumberWithUnits& operator +=(const NumberWithUnits& other) {
            double mul = convert[other.type][this->type];
            
            if(mul == INVALID)
                throw std::out_of_range("Invalid types1");
                
            double newvalue = this->value + mul * other.value;
            
            this->value = newvalue;
 
            return *this;
        }
        
        NumberWithUnits& operator -=(const NumberWithUnits& other) {
            double mul = convert[other.type][this->type];
            
            if(mul == INVALID)
                throw std::out_of_range("Invalid types2");
                
            double newvalue = this->value - mul * other.value;
            
            this->value = newvalue;
 
            return *this;
        }
        
        NumberWithUnits& operator *=(const double mul) {
            double newvalue = this->value * mul;
            
            this->value = newvalue;
        
            return *this;
        }
        
        NumberWithUnits& operator--()
        {
            this->value = this->value - 1;
            
            return *this;
        }
        
        NumberWithUnits operator--(int)
        {
            NumberWithUnits temp = *this;
            
            this->value = this->value - 1;
            
            return temp;
        }
        
        NumberWithUnits& operator++()
        {
            this->value = this->value + 1;
            
            return *this;
        }
        
        NumberWithUnits operator++(int)
        {
            NumberWithUnits temp = *this;
            
            this->value = this->value + 1;
            
            return temp;
        }
        
        friend ostream& operator<<(ostream& os, NumberWithUnits obj) {
            os << obj.value << "[" << obj.type << "]";
     
            return os;
        }
     
        friend istream& operator>>(istream& is, NumberWithUnits& obj) {
            char c1, c2;
            
            is >> obj.value >> c1 >> obj.type >> c2;
            
            if(obj.type == "")
                throw std::out_of_range("Invalid type4");
            return is;
        }
        
        friend NumberWithUnits operator+(NumberWithUnits const &, NumberWithUnits const &);
        friend NumberWithUnits operator+(NumberWithUnits const &);
        friend NumberWithUnits operator-(NumberWithUnits const &);
        friend NumberWithUnits operator-(NumberWithUnits const &, NumberWithUnits const &);
        friend NumberWithUnits operator*(double mul, NumberWithUnits a);
        friend NumberWithUnits operator*(NumberWithUnits a, double mul);
        
        friend bool operator>(NumberWithUnits a, NumberWithUnits b);
        friend bool operator>=(NumberWithUnits a, NumberWithUnits b);
        friend bool operator<(NumberWithUnits a, NumberWithUnits b);
        friend bool operator<=(NumberWithUnits a, NumberWithUnits b);
        friend bool operator==(NumberWithUnits a, NumberWithUnits b);
        friend bool operator!=(NumberWithUnits a, NumberWithUnits b);
    };
}