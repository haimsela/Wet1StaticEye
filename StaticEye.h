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
     *            by adding the image to the tree map and the list map
     *
     * @param image_id - image id to add
     */
    void AddImage(int image_id);

    /**
     * DeleteImage - delete image from the system by delete the image from the
     *               the tree map and the list map
     *
     * @param image_id - image to delete
     */
    void DeleteImage(int image_id);

    /**
     * AddLabel - this function add label to image segment by finding the image
     *            in the tree and adding the label to the image segments array
     *
     * @param imageID - image to add label to
     * @param segmentID - segment to label
     * @param label - the label to give to the segment
     */
    void AddLabel(int image_id, int segment_id, int label);

    /**
     * GetLabel - this function get label from image segment by finding the
     *            image and getting the label from image segments array
     *
     * @param imageID - image to get label from
     * @param segmentID - segment to get label of
     * @param label - pointer to return value of label
     */
    void GetLabel(int image_id, int segment_id, int* label);

};

#endif //WET1STATICEYE_STATICEYE_H
