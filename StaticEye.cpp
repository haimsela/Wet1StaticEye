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

    Image* new_image = new Image(this->segments);

    try {
        void* new_node = this->images_map_list.Add(image_id,new_image);
        this->images_map_tree.Add(image_id,new_node);
    } catch (std::bad_alloc& bad_allocation ) {
        throw bad_allocation;
    } catch (typename MapList<int,Image*>::KeyAlreadyExists&  ){
        delete new_image;
        throw StaticEye::Failure();
    } catch (typename MapTree<int,void*>::KeyAlreadyExists& ) {
        delete new_image;
        throw StaticEye::Failure();;
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

/*========================================================================
  StaticEye private functions:
========================================================================*/

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