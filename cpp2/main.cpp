#include <iostream>
#include "DescFolium.h"

using namespace std;

void createMenu()
{
    std::cout << "  ______    _ _                          __       _                          _            \n";
    std::cout << " |  ____|  | (_)                        / _|     | |                        | |           \n";
    std::cout << " | |__ ___ | |_ _   _ _ __ ___     ___ | |_    __| | ___  ___  ___ __ _ _ __| |_ ___  ___ \n";
    std::cout << " |  __/ _ \\| | | | | | '_ ` _ \\   / _ \\|  _|  / _` |/ _ \\/ __|/ __/ _` | '__| __/ _ \\/ __|\n";
    std::cout << " | | | (_) | | | |_| | | | | | | | (_) | |   | (_| |  __/\\__ \\ (_| (_| | |  | ||  __/\\__ \\\n";
    std::cout << " |_|  \\___/|_|_|\\__,_|_| |_| |_|  \\___/|_|    \\__,_|\\___||___/\\___\\__,_|_|   \\__\\___||___/\n\n";

    std::cout << "Formula: x^3 + y^3 = 3nxy\n";
    std::cout << "Choose your n: ";
}

void appMenu()
{
    std::cout << "\nChoose your fighter(just send me number):\n";
    std::cout << "1. Get N\n";
    std::cout << "2. Change N\n";
    std::cout << "3. Biggest Chord\n";
    std::cout << "4. Polar Center Distance\n";
    std::cout << "5. Get Top Curvature\n";
    std::cout << "6. Get Bottom Curvature\n";
    std::cout << "7. Get Area\n";
    std::cout << "8. Get Diameter\n";
    std::cout << "9. Get Distance to Diameter\n";
    std::cout << "10. Exit\n\n";
    std::cout << ">>> ";
}

void action(Sage::DescFolium* df)
{
    int action = Sage::getInt();
    switch (action)
    {
        case 1:
            std::cout << "Your N: " << df->getN() << '\n';
            break;
        
        case 2:
        {
            std::cout << "Enter your new N: ";
            float n = Sage::getFloat();
            df->setN(n);
            std::cout << "Success. Your N now: " << df->getN() << '\n';
            break;
        }
        case 3:
            std::cout << "The biggest chord is " << df->getChord() << '\n';
            break;

        case 4:
        {
            std::cout << "\nYour system:\n";
            std::cout << "1. Radians\n";
            std::cout << "2. Degrees\n";
            std::cout << ">>> ";
            int sys = Sage::getInt();
            float alpha = 0;
            bool flag = true;
            std::cout << "\nInput number: ";
            switch (sys)
            {
                case 1:
                {
                    alpha = Sage::getFloat();    
                    break;
                }
                case 2:
                {
                    alpha = Sage::getFloat() / 180 * 3.14159265359;
                    break;
                }
                default:
                    flag = false;
                    std::cout << "Invalid input\n";
                    break;
            }
            if (flag)
            {
                std::cout << "Distance is " << df->centerDistance(alpha) << '\n';
            }
            break;
        }
        case 5:
            std::cout << "The top curvature is " << df->getCurvatureUp() << '\n';
            break;

        case 6:
            std::cout << "The bottom curvature is " << df->getCurvatureDown() << '\n';
            break;

        case 7:
            std::cout << "The area is " << df->getArea() << '\n';
            break;

        case 8:
            std::cout << "The diameter is " << df->getPLen() << '\n';
            break;

        case 9:
            std::cout << "The distance to diameter is " << df->getPLenDistance() << '\n';
            break;

        case 10:
            std::exit(0);
            break;

        default:
            std::cout << "Invalid input\n";
            break;
    }   
}

int main()
{
    Sage::DescFolium* df = NULL;
    createMenu();
    float n = Sage::getFloat();
    df = new Sage::DescFolium(n);
    while (1)
    {
        appMenu();
        action(df);
    }
}