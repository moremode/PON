#include "resident.h"

namespace Sage4
{
    class Flat
    {
        private:
            int _square;
            int _number;
            int _count = 0;
            Resident** _resident = nullptr;
        public:
            /**
            * ... text ...
            */
            Flat() : Flat(0, 0) {};
            Flat(int, int);
            Flat(Resident**, int, int, int);
            ~Flat();
            int getResidentCount() const { return _count; };
            int getSquare() const { return _square; };
            int getFlatNumber() const { return _number; };
            Resident** getResidents() { return _resident; };
            int commonResidents();
            int concessionaryResidents();
            bool typeOfFlatResident();
            void setFlatNumber(int number) { _number = number; };
            void setResidents(Resident** resident, int count);
            void info();
            void clearResident();
    };
}