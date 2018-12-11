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
 * AddLabel - add label to image in StaticEye system given
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
 * GetLabel - get label
 * @param DS
 * @param imageID
 * @param segmentID
 * @param label
 * @return
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
 * Size - get the size of the data structure
 *
 * @param DS - data structure get size of
 * @param n - pointer to return value of the size
 * @return the size as pointer and status
 */
StatusType Size(void *DS, int *n){
    if(DS==nullptr || n == nullptr){
        return INVALID_INPUT;
    }

    *n = ((MapList<int,void*>*)DS)->GetMapSize();

    return SUCCESS;
}
/**
 * Quit - This function free the data structure resources
 *
 * @param DS -  data structure to free
 */
void Quit(void** DS){
    if(DS == nullptr){
        return;
    }

    delete (MapList<int,void*>*)(*DS);
    *DS= nullptr;
}
