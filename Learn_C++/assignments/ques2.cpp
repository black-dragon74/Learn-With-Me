//
// Created by Nick on 11/21/19.
//

#include <iostream>
#include <vector>

using namespace std;

class Collection
{
private:
    vector<float> data;
public:
    Collection()
    {
        // Really dumb way but works
        data = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    }

    void modifyValue(float oldValue, float newValue)
    {
        // First, get the index of the element if it exists
        auto it = find(data.begin(), data.end(), oldValue);

        if (it == data.end())
        {
            cout << "Element is not there in the vector" << endl;
            exit(1);
        }

        int index = distance(data.begin(), it);

        // Replace the value
        data.at(index) = newValue;
        cout << "Successfully replaced the value at index: " << index << " with " << newValue << endl;
    }

    // If called without args, will print each ele, else will print elems by stepping of `n`
    void display(int step = 1)
    {
        for (auto it = data.begin(); it <= data.end(); it+=step)
        {
            cout << *it << endl;
        }
    }
};

int main(int argc, char **argv)
{
    Collection c{};
    c.modifyValue(2, 20);
    c.display(4);

    return 0;
}