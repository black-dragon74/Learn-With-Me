//
// Created by Nick on 11/21/19.
//

#include <iostream>
#include <vector>

using namespace std;

bool valueInStringArray(const string &value, const vector<string> &array)
{
    return find(array.begin(), array.end(), value) != array.end();
}

class Journey
{
private:
    string origin, dest, date;
    vector<string> allowedPlaces {"delhi", "mumbai", "kolkata", "chennai", "jaipur"};
public:
    Journey()
    {
        cout << "Enter origin: ";
        getline(cin, origin);

        cout << "Enter destination: ";
        getline(cin, dest);

        cout << "Enter date of journey: ";
        getline(cin, date);

        // Now we validate the inputs
        if (!valueInStringArray(origin, allowedPlaces))
        {
            cout << "Invalid value " << origin << " entered for origin";
        }

        if (!valueInStringArray(dest, allowedPlaces))
        {
            cout << "Invalid value " << dest << " entered for origin" << endl;
        }
    }

    double getFare()
    {
        if (origin == dest)
        {
            return 0;
        }

        // Now we calculate the fare, logic is, we find the difference in
        // the vector indices and then just return the value by multiplying it by 2000
        auto ptr = find(allowedPlaces.begin(), allowedPlaces.end(), origin);
        auto diff1 = (ptr - allowedPlaces.begin()) + 1;

        ptr = find(allowedPlaces.begin(), allowedPlaces.end(), dest);
        auto diff2 = (ptr - allowedPlaces.begin() + 1);

        auto distance = abs(diff2 - diff1);

        // Return fare with 12% GST
        return distance * 0.12 * 2000;
    }
};

int main(int argc, char **argv)
{
    Journey j{};
    cout << "Your fare is: " << j.getFare() << endl;

    return 0;
}