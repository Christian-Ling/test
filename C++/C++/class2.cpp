#include <iostream>
using namespace std;

class MyClass {
private:
    int x;  
public:
    void setX(int value) {
        x = value;
    }

    int getX() {
        return x;
    }

    void display() {
        cout << "Value of x: " << x << endl;
    }
};

int main() {
    MyClass obj;
    obj.setX(10);       // Setter to access and modify private variable
    cout << obj.getX(); // Getter to access private variable
    obj.display();      
    return 0;
}
