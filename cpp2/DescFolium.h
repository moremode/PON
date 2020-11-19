#include <math.h>

namespace Sage
{
    float getFloat();
    int getInt();

    class DescFolium
    {
        private:
            float n;
        public:
            DescFolium(float n = 1);
            float getN() const{ return n; }
            DescFolium& setN(float);
            float getChord() const{ return 3 * n / sqrt(2); }
            float centerDistance(float alpha) const{ return 3 * n * cos(alpha) * sin(alpha) / (pow(cos(alpha), 3) + pow(sin(alpha), 3)); }
            float getArea() const{ return 3 * pow(n, 2) / 2; }
            float getCurvatureUp() const{ return (3 * n) / (8 * sqrt(2)); }
            float getCurvatureDown() const{ return (3 * n) / 2; }
            float getPLen() const{ return 3*n*sqrt(10)/10; }
            float getPLenDistance() const{ return 3 * n / (sqrt(2) * 2); }
    };
}