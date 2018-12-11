#include "StaticEye.h"
#include <iostream>

int main(int argc, const char**argv) {

    StaticEye test(3);
    test.AddImage(2);
    try{
        test.AddImage(2);
    } catch (typename StaticEye::Failure&){
        cout << "yay" << endl;
    }

    test.DeleteImage(2);
    test.AddImage(2);
    test.AddLabel(2, 1, 8);
    int lab;
    test.GetLabel(2, 1, &lab);
    cout << lab << endl;
    try{
        test.GetLabel(62, 1, &lab);
    } catch (typename StaticEye::Failure&){
        cout << "yay" << endl;
    }
    test.DeleteLabel(2, 1);
    try{
        test.GetLabel(2, 1, &lab);
    } catch (typename StaticEye::Failure&){
        cout << "yay" << endl;
    }


}
