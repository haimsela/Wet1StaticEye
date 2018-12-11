#include "library2.h"
#include "StaticEye.h"
#include <stdexcept>


/**
 * Init - initialize new StaticEye system
 *
 * @return the new system
 */
void *Init(int segments){
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

    try {
        ((StaticEye*)DS)->AddImage(imageID);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure()&  ){
        return FAILURE;
    } catch (typename StaticEye::InvalidInput()& ) {
        return INVALID_INPUT;
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

    try {
        ((StaticEye*)DS)->DeleteImage(imageID);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure()&  ){
        return FAILURE;
    } catch (typename StaticEye::InvalidInput()& ) {
        return INVALID_INPUT;
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

    try {
        ((StaticEye*)DS)->AddLabel(imageID,segmentID,label);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure()&  ){
        return FAILURE;
    } catch (typename StaticEye::InvalidInput()& ) {
        return INVALID_INPUT;
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

    try {
        ((StaticEye*)DS)->GetLabel(imageID,segmentID,label);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure()&  ){
        return FAILURE;
    } catch (typename StaticEye::InvalidInput()& ) {
        return INVALID_INPUT;
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

    try {
        ((StaticEye*)DS)->DeleteLabel(imageID,segmentID);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure()&  ){
        return FAILURE;
    } catch (typename StaticEye::InvalidInput()& ) {
        return INVALID_INPUT;
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

    try {
        ((StaticEye*)DS)->GetAllUnLabeledSegments(imageID,segments,
                                                  numOfSegments);
        return SUCCESS;
    } catch (std::bad_alloc& bad_allocation ) {
        return ALLOCATION_ERROR;
    } catch (typename StaticEye::Failure()&  ){
        return FAILURE;
    } catch (typename StaticEye::InvalidInput()& ) {
        return INVALID_INPUT;
    }
}
