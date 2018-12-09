/*------------------------------------------------------------------------
  Include files:
------------------------------------------------------------------------*/
#include "StaticEye.h"

/*========================================================================
  StaticEye public functions:
========================================================================*/

/**
 * AddImage - this function get image id and add the id to the system
 *
 * @param image_id - image id to add
 */
void StaticEye::AddImage(int image_id){
    if(!IsValidImageId(image_id)){
        throw InvalidInput();
    }

    Image new_image(this->segments);

    try {
        void* new_node = this->images_map_tree.Add(image_id,new_image);
        this->images_map_list.Add(image_id,new_node);
    } catch (std::bad_alloc& bad_allocation ) {
        throw bad_allocation;
    } catch (typename MapList<int,void*>::KeyAlreadyExists&  ){
        throw StaticEye::Failure();
    } catch (typename MapTree<int,Image>::KeyAlreadyExists ) {
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