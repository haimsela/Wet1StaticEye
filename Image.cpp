/*------------------------------------------------------------------------
  Include files:
------------------------------------------------------------------------*/

#include "Image.h"

/*========================================================================
  Image public functions:
========================================================================*/

/**
* Image(int segments) - constructor that gets the number of segments in
*                       the image and initialize the arrat and the list
*
* @param segments - the number of segments in the image
*/
Image::Image(int segments) : segments(segments) ,
                                      uninitialized_segments() {
    segments_array = new int[segments];
    InitializeSegmentsArray(segments_array,segments);
    InitializeUninitializedSegmentsList(&uninitialized_segments,segments);
}

/**
     * ~Image() - the image destructor destroy the list(automatically using
     *            the list destructor) and delete the segments array
     */
Image::~Image(){
    delete[] segments_array;
}

/**
 * AddLabel - this function get segment id and label and add the label to
 *            the segment. if one of the parameter is incorrect or the
 *            segment is already labeled throw error.
 *            this function also update the uninitialized segments list
 *
 * @param segment_id - segment id to add the label to
 * @param label - label to add
 */
void Image::AddLabel(int segment_id,int label){
    if((!this->IsSegmentIdLegal(segment_id)) || (IsLabelLegal(label))){
        throw InvalidInput();
    }

    if(this->segments_array[segment_id]!=UNINITIALIZED_SEGMENT){
        throw Failure();
    }

    this->segments_array[segment_id]=label;
    this->uninitialized_segments.RemoveByData(segment_id);
}

/**
 * GetLabel - this function get segment id and return the label of the
 *            segment. if the segment id is invalid or the segment is
 *            uninitialized throw error
 *
 * @param segment_id - the segment id to get the label to
 * @return
 */
int Image::GetLabel(int segment_id){
    if(!this->IsSegmentIdLegal(segment_id)){
        throw InvalidInput();
    }

    if(this->segments_array[segment_id]==UNINITIALIZED_SEGMENT){
        throw Failure();
    }

    return this->segments_array[segment_id];
}

/**
 * DeleteLabel - this function get segment id and return delete the label
 *               of the segment. if the segment id is invalid or the
 *               segment is uninitialized throw error. this function also
 *               update the uninitialized segments list
 *
 * @param segment_id - the segment id to delete the label to
 */
void Image::DeleteLabel(int segment_id){
    if(!this->IsSegmentIdLegal(segment_id)){
        throw InvalidInput();
    }

    if(this->segments_array[segment_id]==UNINITIALIZED_SEGMENT){
        throw Failure();
    }

    this->uninitialized_segments.InsertFirst(segment_id);
    this->segments_array[segment_id]=UNINITIALIZED_SEGMENT;
}

/**
 * GetAllUnLabeledSegments - fill the give segments array with all the
 *                           unlabeled segments ids and return the number
 *                           of unlabeled segments
 *
 * @param segments - pointer to array to create with all the uninitialized
 *                   segments
 * @return the number of unlabeled index
 */
int Image::GetAllUnLabeledSegments(int **segments){
 *segments = (int*)malloc(sizeof(**segments)*
                                   (this->uninitialized_segments.GetLength()));

    FillUnlabeledArrayUsingTheUnlabeledList(
                                   &this->uninitialized_segments,
                                   *segments,
                                   this->uninitialized_segments.GetLength());

 return this->uninitialized_segments.GetLength();
}

/**
 * FindNumberOfSegmentsWithLabel - this function get label and return the
 *                                 number of segments in the image with
 *                                 the label
 *
 * @param label - label to search
 * @return number of segments with the label
 */
int Image::FindNumberOfSegmentsWithLabel(int label){
    int number_of_segments_with_label=0;

    for( int i=0;i<this->segments;i++){
        if(this->segments_array[i]==label){
            number_of_segments_with_label++;
        }
    }

    return number_of_segments_with_label;
}

/**
 * GetAllSegmentsByLabel - This function get already allocated array and
 *                         fill the array with all the segments in the
 *                         image with the given label.
 *
 * @param segments - the segments array
 * @param label - the label to find
 */
void Image::GetAllSegmentsByLabel(int **segments, int label ){
    int current_index_in_segments_array=0;

    for(int i=0;i<this->segments;i++){
        if(this->segments_array[i]==label){
            *segments[current_index_in_segments_array] = i;
            current_index_in_segments_array++;
        }
    }
}

/*========================================================================
  Image private functions:
========================================================================*/

/**
 * InitializeUninitializedSegmentsList - this function get uninitialized
 *                                       list that represent all the
 *                                       uninitialized segments in the
 *                                       image. an init all the segments
 *                                       are uninitialized.
 *
 * @param uninitialized_segments_list - uninitialized list that at the end
 *                                      of this function will contain all
 *                                      the segments of the image
 * @param segments - number of segments in the image
 */
 void Image::InitializeUninitializedSegmentsList(
                                        List<int>* uninitialized_segments_list,
                                        int segments){
    for(int i=0;i<segments;i++){
        uninitialized_segments_list->InsertFirst(i);
    }
}

/**
 * InitializeSegmentsArray - this function get segments array and the
 *                           the number of segments in the image and
 *                           set all the cells in the array to be
 *                           UNINITIALIZED_SEGMENT
 *
 * @param segments_array - the segments array
 * @param segments - number of segments in the image
 */
void Image::InitializeSegmentsArray(int* segments_array, int segments){

    for(int i=0;i<segments;i++){
        segments_array[i] = UNINITIALIZED_SEGMENT;
    }
}

/**
* IsSegmentIdLegal - this function check if segment id is ok dependent
*                    by the number of segments in the array
*
* @param segment_id - segment id
* @return true if legal otherwise false
*/
bool Image::IsSegmentIdLegal(int segment_id){
    return segment_id >= 0 && segment_id < this->segments;
}

/**
* IsLabelLegal - this function check if label is legal
*
* @param label - label to check
* @return true if legal otherwise false
*/
bool Image::IsLabelLegal(int label){
    return label > 0;
}

/**
 * FillUnlabeledArrayUsingTheUnlabeledList - this function fill a given
 *                                           array of unlabeled segments
 *                                           using the unlabeled segments
 *                                           list.
 *
 * @param uninitialized_segments_list - the unlabeled segments list
 * @param segments - array to fill
 * @param number_of_uninitialized_segments - number of uninitialized
 *                                           labels
 */
void Image::FillUnlabeledArrayUsingTheUnlabeledList(
                                        List<int>* uninitialized_segments_list,
                                        int* segments,
                                        int number_of_uninitialized_segments){
    void* current_node = uninitialized_segments_list->ListGetFirst();

    for(int i=0;i<number_of_uninitialized_segments;i++){
        segments[i]=uninitialized_segments_list->GetNodeData(current_node);
        current_node = uninitialized_segments_list->ListGetNextNode(
                                                                 current_node);
    }
}