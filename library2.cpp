#include "library2.h"
#include "StaticEye.h"
#include <stdexcept>

static bool IsValidMaxSegments(int segments);
static bool IsValidImage(int image);
static bool IsValidSegments(int segments, int max_segments);
static bool IsValidLabel(int label);

/**
 * Init - initialize new StaticEye system
 *
 * @return the new system
 */
void *Init(int segments){
    if(!IsValidMaxSegments(segments)){
        return nullptr;
    }

    try {
        StaticEye* DS = new StaticEye(segments);
        return (void*)DS;
    } catch (std::bad_alloc& bad_allocation ) {
        return nullptr;
    }
}

/**
 * AddImage - add new image to the StaticEye system
 *
 * @param DS - StaticEye system
 * @param imageID - image to add to the system
 * @return status of the operation
 */
StatusType AddImage(void *DS, int imageID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    if(!IsValidImage(imageID)){
        return INVALID_INPUT;
    }

    try {
        ((StaticEye*)DS)->AddImage(imageID);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure&  ){
        return FAILURE;
    }
}

/**
 * DeleteImage - delete image from the StaticEye system given
 *
 * @param DS - StaticEye to remove image from
 * @param imageID - image to remove
 * @return status of the operation
 */
StatusType DeleteImage(void *DS, int imageID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    if(!IsValidImage(imageID)){
        return INVALID_INPUT;
    }

    try {
        ((StaticEye*)DS)->DeleteImage(imageID);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure&  ){
        return FAILURE;
    }
}

/**
 * AddLabel - add label to segment in image in StaticEye system given
 *
 * @param DS - StaticEye to add label to image on
 * @param imageID - image to add label to
 * @param segmentID - segment in image to add the label to
 * @param label - label to put to the segment in the image
 * @return status of the operation
 */
StatusType AddLabel(void *DS, int imageID, int segmentID, int label){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    if(!IsValidImage(imageID) ||
       !IsValidSegments(segmentID,((StaticEye*)DS)->GetMaxSizeOfSegments()) ||
       !IsValidLabel(label) ){
        return INVALID_INPUT;
    }

    try {
        ((StaticEye*)DS)->AddLabel(imageID,segmentID,label);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure&  ){
        return FAILURE;
    }
}

/**
 * GetLabel - get label of segment in StaticEye system given
 *
 * @param DS - StaticEye to add label to image on
 * @param imageID - image to get segment label on
 * @param segmentID - segment to get label of
 * @param label - return value for the label of a segment
 * @return status of the operation
 */
StatusType GetLabel(void *DS, int imageID, int segmentID, int *label){
    if(DS == nullptr || label == nullptr){
        return INVALID_INPUT;
    }

    if(!IsValidImage(imageID) ||
       !IsValidSegments(segmentID,((StaticEye*)DS)->GetMaxSizeOfSegments())){
        return INVALID_INPUT;
    }

    try {
        ((StaticEye*)DS)->GetLabel(imageID,segmentID,label);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure&  ){
        return FAILURE;
    }
}

/**
 * DeleteLabel - delete label from segment in image in StaticEye system given
 *
 * @param DS - StaticEye to delete label from segment in image in
 * @param imageID - image to delete label from segment in
 * @param segmentID - segment to delete label of
 * @return status of the operation
 */
StatusType DeleteLabel(void *DS, int imageID, int segmentID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    if(!IsValidImage(imageID) ||
       !IsValidSegments(segmentID,((StaticEye*)DS)->GetMaxSizeOfSegments())){
        return INVALID_INPUT;
    }

    try {
        ((StaticEye*)DS)->DeleteLabel(imageID,segmentID);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure&  ){
        return FAILURE;
    }
}

/**
 * GetAllUnLabeledSegments - return all the unlabeled segments in image in
 *                           given StaticEye system
 *
 * @param DS - StaticEye system to get all unlabeled segments in image in
 * @param imageID - image to get all the unlabeled segments in
 * @param segments - pointer to return new array with all the unlabeled
 *                   segments in given image
 * @param numOfSegments - pointer to return the number of unlabeled segments in
 *                        the image
 * @return status of the operation
 */
StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments,
                                   int *numOfSegments){
    if(DS == nullptr || segments == nullptr  || numOfSegments == nullptr){
        return INVALID_INPUT;
    }

    if(!IsValidImage(imageID)){
        return INVALID_INPUT;
    }

    try {
        ((StaticEye*)DS)->GetAllUnLabeledSegments(imageID,segments,
                                                  numOfSegments);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure&  ){
        return FAILURE;
    }
}

/**
 * GetAllSegmentsByLabel - this function returns all the segment in all the
 *                         images that labeled by a given label
 *
 * @param DS - StaticEye system to get all the segments with the label in
 * @param label - label to return all the segments with
 * @param images - pointer to return images array that contains the image id
 *                 of segment with the given label
 * @param segments - pointer to return segment with given label that correspond
 *                   to the image in the images array with the same index
 * @param number_of_segments - number of segments in all the images with
 *                             the given label
 * @return
 */
StatusType GetAllSegmentsByLabel(void *DS, int label, int **images,
                                 int **segments, int *numOfSegments){
    if(DS == nullptr || images == nullptr  || segments == nullptr ||
       numOfSegments == nullptr ){
        return INVALID_INPUT;
    }

    if(!IsValidLabel(label)){
        return INVALID_INPUT;
    }

    try {
        ((StaticEye*)DS)->GetAllSegmentsByLabel(label,images,segments,
                                                numOfSegments);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure&  ){
        return FAILURE;
    }
}

/**
 * Quit - destroy a given StaticEye system  and free all the systems resources
 *
 * @param DS - StaticEye system to destroy
 */
void Quit(void** DS){
    if(DS == nullptr){
        return;
    }

    delete ((StaticEye*)*DS);
    *DS = nullptr;
}

/**
 * IsValidMaxSegments - check if max segments is valid
 * @param segments - max segments to label
 * @return true if valid, false else
 */

static bool IsValidMaxSegments(int segments ){
    return segments > 0 ;
}

/**
 * IsValidImage - check if image is valid
 * @param image - image id
 * @return true if valid, false else
*/

static bool IsValidImage(int image){
    return image > 0;
}

/**
 * IsValidSegments - check if  segments is valid
 * @param segments - segments to label
 * @param max_segments - max number of segments in image
 * @return true if valid, false else
 */
static bool IsValidSegments(int segments, int max_segments){
    return segments >= 0 && segments < max_segments;
}

/**
 * IsValidLabel - check if Label is valid
 * @param Label - label to tag in image
 * @return true if valid, false else
 */
static bool IsValidLabel(int label){
    return label > 0;
}