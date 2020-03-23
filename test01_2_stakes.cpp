#include <iostream>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    unsigned long long gcdVal = 1;

    if (a == 0) gcdVal = b;
    else if (b == 0) gcdVal = a;
    else
    {
        unsigned long long t;
        // shift variable will be util if a and b are even. In this case, the
        // property (I) gcd(a, b) = 2 * gcd(a / 2, b / 2) is valid.
        // Ex.: gcd(4, 2) = 2 * gcd(2, 1) = 2. So, counting the trailing zeros
        // of a | b tells us how many times we can apply the property above.
        // This is equivalent of getting the number of trailing zeros of a and b and
        // compare which is smaller.
        int shift = __builtin_ctzll(a | b);
        // __builtin_ctzll is a builtin function of the C/C++ compilers
        // to get the number of trailing zeros of a 64bit number
        
        // After applying the property (I) above, if a or b is still even,
        // supposing b, we can apply the property gcd(a, b) = gcd(a, b / 2).
        // Ex.: gcd(5, 12) = gcd(5, 6) = gcd(5, 3). So, because of that, I divide
        // a and b until they are odd.
        a >>= __builtin_ctzll(a); // Divide a by 2 until it is odd

        do
        {
            b >>= __builtin_ctzll(b); // Divide b by 2 until it is odd

            if (a > b)
            { // Ensure that a always has the smallest value
                t = b;
                b = a;
                a = t;
            }

            // Now that a and b are odd, I can apply the property
            // gcd(a, b) = gcd(a, (b - a) / 2) considering that a <= b
            b = b - a;

        } while (b != 0);

        gcdVal = a << shift;
    }

    return gcdVal;
}

int main()
{
    unsigned long long width, height, stakes, gcdVal;
    cin >> width >> height;

    while (!cin.eof())
    {
        gcdVal = gcd(width, height);
        stakes = 2 * (width / gcdVal + height / gcdVal);
        
        cout << stakes << endl;
        cin >> width >> height;
    }
}
