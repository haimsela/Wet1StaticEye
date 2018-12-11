/*------------------------------------------------------------------------
  Include files:
------------------------------------------------------------------------*/
#include "StaticEye.h"

/*========================================================================
  StaticEye public functions:
========================================================================*/

/**
 * ~StaticEye() - the default destructor
 */
StaticEye::~StaticEye(){
    Image* current_image;
    void* current_node = this->images_map_list.GetFirstNode();

    for(int i=0;i<this->images_map_list.GetMapSize();i++){
        current_image = this->images_map_list.GetNodeData(current_node).
                                                                   GetValue();
        delete current_image;
        current_node = this->images_map_list.GetNextNode(current_node);
    }
}

/**
 * AddImage - this function get image id and add the id to the system
 *
 * @param image_id - image id to add
 */
void StaticEye::AddImage(int image_id){
    if(!IsValidImageId(image_id)){
        throw InvalidInput();
    }

    if(this->images_map_tree.IsKeyExists(image_id)){
        throw typename StaticEye::Failure();
    }


    Image* new_image = new Image(this->segments);

    try {
        void* new_node = this->images_map_list.Add(image_id,new_image);
        this->images_map_tree.Add(image_id,new_node);
    } catch (std::bad_alloc& bad_allocation ) {
        throw bad_allocation;
    }
}

/**
 * DeleteImage - delete image from the system by delete the image from the
 *               the tree map and the list map
 *
 * @param image_id - image to delete
 */
void StaticEye::DeleteImage(int image_id){
    if(!IsValidImageId(image_id)){
        throw InvalidInput();
    }

    try {
        void* node_of_image_to_delete = this->images_map_tree.FindKey(
                                                                     image_id);
        Image* image_to_delete = this->images_map_list.GetNodeData(
                                           node_of_image_to_delete).GetValue();
        delete image_to_delete;

        this->images_map_tree.DeleteKey(image_id);
        this->images_map_list.DeleteByPointer(node_of_image_to_delete);
    } catch (std::bad_alloc& bad_allocation ) {
        throw bad_allocation;
    } catch (typename MapList<int,Image*>::DataNotFoundException&  ){
        throw StaticEye::Failure();
    } catch (typename MapTree<int,void*>::DataNotFoundException& ) {
        throw StaticEye::Failure();;
    }
}

/**
 * AddLabel - this function add label to image segment by finding the image
 *            in the tree and adding the label to the image segments array
 *
 * @param imageID - image to add label to
 * @param segmentID - segment to label
 * @param label - the label to give to the segment
 */
void StaticEye::AddLabel(int image_id, int segment_id, int label) {
    if (!IsValidImageId(image_id)) {
        throw InvalidInput();
    }

    try {
        void *node_of_image_to_add_label_to = this->images_map_tree.FindKey(
                image_id);
        Image *image_to_add_label_to = this->images_map_list.GetNodeData(
                                    node_of_image_to_add_label_to).GetValue();
        image_to_add_label_to->AddLabel(segment_id, label);

    } catch (std::bad_alloc &bad_allocation) {
        throw bad_allocation;
    } catch (typename MapTree<int, void *>::DataNotFoundException &) {
        throw StaticEye::Failure();
    } catch (typename Image::InvalidInput &) {
        throw StaticEye::InvalidInput();
    } catch (typename Image::Failure &) {
        throw StaticEye::Failure();
    }
}

/**
 * GetLabel - this function get label from image segment by finding the
 *            image and getting the label from image segments array
 *
 * @param imageID - image to get label from
 * @param segmentID - segment to get label of
 * @param label - pointer to return value of label
 */
void StaticEye::GetLabel(int image_id, int segment_id, int* label){
    if (!IsValidImageId(image_id)) {
        throw InvalidInput();
    }

    try {
        void *node_of_image_to_get_label_of = this->images_map_tree.FindKey(
                                                                  image_id);
        Image *image_to_get_label_of = this->images_map_list.GetNodeData(
                                 node_of_image_to_get_label_of).GetValue();
        *label = image_to_get_label_of->GetLabel(segment_id);

    } catch (std::bad_alloc &bad_allocation) {
        throw bad_allocation;
    } catch (typename MapTree<int, void *>::DataNotFoundException &) {
        throw StaticEye::Failure();
    } catch (typename Image::InvalidInput &) {
        throw StaticEye::InvalidInput();
    } catch (typename Image::Failure &) {
        throw StaticEye::Failure();
    }
}

/**
 * DeleteLabel - this function delete label from image segment by finding
 *                the image and deleting the label from image segments
 *                array and adding the segment to the uninitialized
 *                segments list
 *
 * @param image_id - image id to delete label in
 * @param segment_id - segment id to delete label of
 */
void StaticEye::DeleteLabel(int image_id, int segment_id){
    if (!IsValidImageId(image_id)) {
        throw InvalidInput();
    }

    try {
        void *node_of_image_to_delete_label_of = this->images_map_tree.FindKey(
                                                                    image_id);
        Image *image_to_delete_label_of = this->images_map_list.GetNodeData(
                               node_of_image_to_delete_label_of).GetValue();
        image_to_delete_label_of->DeleteLabel(segment_id);

    } catch (std::bad_alloc &bad_allocation) {
        throw bad_allocation;
    } catch (typename MapTree<int, void *>::DataNotFoundException &) {
        throw StaticEye::Failure();
    } catch (typename Image::InvalidInput &) {
        throw StaticEye::InvalidInput();
    } catch (typename Image::Failure &) {
        throw StaticEye::Failure();
    }
}

/**
 * GetAllUnLabeledSegments - this function get image id and get a array of
 *                           all the unlabeled segments using the
 *                           uninitialized segments list of the image
 *
 * @param image_id - image to get uninitialized segments of
 * @param segments - return array with all the unlabeled segments
 * @param number_of_segments - number id unlabeled segments in the image
 */
void StaticEye::GetAllUnLabeledSegments(int image_id, int **segments,
                                        int* number_of_segments){
    if (!IsValidImageId(image_id)) {
        throw InvalidInput();
    }

    try {
        void *node_of_image_to_get_unlabeled_segments = this->images_map_tree.
                                                           FindKey(image_id);
        Image *image_to_get_unlabeled_segments = this->images_map_list.
                         GetNodeData(node_of_image_to_get_unlabeled_segments).
                         GetValue();

        *number_of_segments = image_to_get_unlabeled_segments->
                                           GetAllUnLabeledSegments(segments);

    } catch (std::bad_alloc &bad_allocation) {
        throw bad_allocation;
    } catch (typename MapTree<int, void *>::DataNotFoundException &) {
        throw StaticEye::Failure();
    } catch (typename Image::InvalidInput &) {
        throw StaticEye::InvalidInput();
    } catch (typename Image::Failure &) {
        throw StaticEye::Failure();
    }
}

/**
 * GetAllSegmentsByLabel - this function get all the segments in all the
 *                         images with given label. the function will
 *                         allocate two new arrays that contains the
 *                         segments and the image of the segment with
 *                         the given label.
 *
 * @param label - the label to find
 * @param images - images array that contains the image id of segment with
 *                 the given label
 * @param segments - segment to given label that correspond to the image
 *                   in the images array with the same index
 * @param number_of_segments - number of segments in all the images with
 *                             the given label
 */
void StaticEye::IsLabelLegal(int label, int **images, int **segments,
                           int *number_of_segments){
    if (!IsLabelLegal(label)) {
        throw InvalidInput();
    }

        *number_of_segments = this->GetNumberOfSegmentsWithLabel(label);
}

/*========================================================================
  StaticEye private functions:
========================================================================*/

/**
* GetNumberOfSegmentsWithLabel - this function check how manny segments in
*                                all the images has same label as the one
*                                that was given. the function will run on
*                                all the images and on all image will
*                                run on all thw segments.
*
* @param label - label to check
*/
int StaticEye::GetNumberOfSegmentsWithLabel(int label){
    int number_of_segments = 0;

    Image* current_image;
    void* current_node = this->images_map_list.GetFirstNode();

    for(int i=0;i<this->images_map_list.GetMapSize();i++){
        current_image = this->images_map_list.GetNodeData(current_node).
                                                              GetValue();
        number_of_segments += current_image.

        current_node = this->images_map_list.GetNextNode(current_node);
    }

}

/**
 * IsValidImageId - this function gets image id and check if the id is
 *                  valid
 *
 * @param image_id - image id to check
 * @return true if valid otherwise false
 */
bool StaticEye::IsValidImageId(int image_id){
    return image_id > 0;
}

/**
* IsLabelLegal - this function check if label is legal
*
* @param label - label to check
* @return true if legal otherwise false
*/
bool StaticEye::IsLabelLegal(int label){
    return label > 0;
}