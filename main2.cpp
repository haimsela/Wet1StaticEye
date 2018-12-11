#include "StaticEye.h"
#include <iostream>

int main(int argc, const char**argv) {

    StaticEye test(5);
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

    test.AddLabel(2, 1, 8);
    test.AddLabel(2, 4, 6);

    int* segments;
    int number_of_segments;

    test.GetAllUnLabeledSegments(2, &segments, &number_of_segments);

    for(int i=0;i<number_of_segments;i++){
        cout << segments[i] << endl;
    }

    free(segments);
    test.AddImage(8);
    test.AddLabel(8, 4, 8);
    test.AddLabel(8, 1, 8);
    int* segmentslab;
    int* imagelab;
    int num_of_seg;

    test.GetAllSegmentsByLabel(8,&imagelab,&segmentslab,&num_of_seg);

    for(int j=0;j<num_of_seg;j++){
        cout << "Image: " << imagelab[j] << " segment: " << segmentslab[j] << endl;
    }

    free(segmentslab);
    free(imagelab);


}
