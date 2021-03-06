#include "library2.h"
#include "StaticEye.h"
#include <iostream>
using namespace std;
void test1();

int main(int argc, const char**argv) {
    test1();
}

void test1(){
    void* DS;

    DS = Init(5);

    AddImage(DS,2);

    if(AddImage(DS,2) == FAILURE){
        cout << "yay" << endl;
    }

    DeleteImage(DS,2);
    AddImage(DS,2);
    AddLabel(DS,2, 1, 8);
    int lab;
    GetLabel(DS, 2, 1, &lab);
    cout << lab << endl;
    if(GetLabel(DS,62, 1, &lab) == FAILURE){
        cout << "yay" << endl;
    }

    DeleteLabel(DS,2, 1);

    if(GetLabel(DS,2, 1, &lab) == FAILURE){
        cout << "yay" << endl;
    }

    AddLabel(DS,2, 1, 8);
    AddLabel(DS,2, 4, 6);

    int* segments;
    int number_of_segments;

    GetAllUnLabeledSegments(DS,2, &segments, &number_of_segments);

    for(int i=0;i<number_of_segments;i++){
        cout << segments[i] << endl;
    }

    free(segments);
    AddImage(DS,8);
    AddLabel(DS,8, 4, 8);
    AddLabel(DS,8, 1, 8);

    AddImage(DS,4);
    AddLabel(DS,4, 3, 8);
    AddLabel(DS,4, 0, 8);
    AddLabel(DS,4, 2, 4);

    int* segmentslab;
    int* imagelab;
    int num_of_seg;

    GetAllSegmentsByLabel(DS,8,&imagelab,&segmentslab,&num_of_seg);

    for(int j=0;j<num_of_seg;j++){
        cout << "Image: " << imagelab[j] << " segment: " << segmentslab[j] << endl;
    }

    free(segmentslab);
    free(imagelab);

    Quit(&DS);

    if(DS== nullptr){
        cout << "yay" << endl;
    }
}
