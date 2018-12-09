#ifndef WET1STATICEYE_STATICEYE_H
#define WET1STATICEYE_STATICEYE_H

#include"Image.h"
#include "MapList.h"
#include "MapTree.h"

/** Image class and his fields */
class StaticEye {
    MapList<int,Image*> images_map_list;
    MapTree<int,void*> images_map_tree;
    int segments;

    /** StaticEye's private functions */

    /**
     * IsValidImageId - this function gets image id and check if the id is
     *                  valid
     *
     * @param image_id - image id to check
     * @return true if valid otherwise false
     */
    static bool IsValidImageId(int image_id);

public:
    /**                    Exceptions                    */
    class InvalidInput : public std::exception {};
    class Failure : public std::exception {};

    /**
     * StaticEye() - the default constructor
     */
    StaticEye(int segments):images_map_list(),images_map_tree(),
                            segments(segments){}

    /**
     * ~StaticEye() - the default destructor
     */
    ~StaticEye();

    /**
     * delete the copy constructor
     */
    StaticEye(const StaticEye&)=delete;

    /**
     * delete the operator=
     */
    StaticEye operator=(const StaticEye& StaticEye)=delete;

    /**
     * AddImage - this function get image id and add the id to the system
     *
     * @param image_id - image id to add
     */
    void AddImage(int image_id);
};

#endif //WET1STATICEYE_STATICEYE_H
