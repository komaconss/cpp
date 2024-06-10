#include <boost/any.hpp>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    boost::any a(1);
    boost::any b(2.5);

    vector<boost::any> vec;
    vec.push_back(a);
    vec.push_back(b);
    int va = boost::any_cast<int>(vec[0]);
    double vb = boost::any_cast<double>(vec[1]);
    cout << va << ", " << vb << endl;

    return 0;
}