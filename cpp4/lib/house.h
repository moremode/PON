#include "flat.h"

namespace Sage4
{
    class House
    {
        private:
            std::string _street;
            int _number;
            int _building;
            int _valueMeter;
            int _valueConst;
            Flat* _flat;
            int _flatRealLen = 15;
            int _flatLen = 0;
        public:
            House(std::string street, int number, int building, int valueMeter, int valueConst);
            House(std::string street, int number, int valueMeter, int valueConst) : House(street, number, 1, valueMeter, valueConst) {};
            ~House();
            std::string getStreet() const { return _street; };
            int getNumber() const { return _number; };
            int getBuilding() const { return _building; };
            int getValueMeter() const { return _valueMeter; };
            int getValueConst() const { return _valueConst; };
            void setStreet(std::string street);
            void setNumber(int number);
            void setBuilding(int building);
            void setValueMeter(int valueMeter);
            void setValueConst(int valueConst);

            void addFlat(Flat& flat);
            Flat& getFlat(int number) const;
            Flat* getFlats() const;
            int getFlatsCount() const { return _flatLen; };
            void removeFlat(int number);
            void printFlats();
    };
}