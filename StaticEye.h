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

    /**
    * IsLabelLegal - this function check if label is legal
    *
    * @param label - label to check
    * @return true if legal otherwise false
    */
    static bool IsLabelLegal(int label);

    /**
    * GetNumberOfSegmentsWithLabel - this function check how manny segments in
    *                                all the images has same label as the one
    *                                that was given. the function will run on
    *                                all the images and on all image will
    *                                run on all thw segments.
    *
    * @param label - label to check
    */
    int GetNumberOfSegmentsWithLabel(int label);

    /**
     * FillAllSegmentsByLabelArrays -  fill the images and segments array that
     *                                 was given to the GetAllSegmentsByLabel
     *                                 function after already allocate the
     *                                 arrays and calculate the number of
     *                                 segments with the label.
     *
     * @param images - images array that contains the image id of segment with
     *                 the given label
     * @param segments - segment to given label that correspond to the image
     *                   in the images array with the same index
     * @param number_of_segments - number of segments in all the images with
     *                             the given label
     */
    void FillAllSegmentsByLabelArrays(void* node_of_current_image,int label,
                                      int **images,int **segments,
                                      int *current_number_of_segments);

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

    /**
     * DeleteLabel - this function delete label from image segment by finding
     *                the image and deleting the label from image segments
     *                array and adding the segment to the uninitialized
     *                segments list
     *
     * @param image_id - image id to delete label in
     * @param segment_id - segment id to delete label of
     */
    void DeleteLabel(int image_id, int segment_id);

    /**
     * GetAllUnLabeledSegments - this function get image id and get a array of
     *                           all the unlabeled segments using the
     *                           uninitialized segments list of the image
     *
     * @param image_id - image to get uninitialized segments of
     * @param segments - return array with all the unlabeled segments
     * @param number_of_segments - number id unlabeled segments in the image
     */
    void GetAllUnLabeledSegments(int image_id, int **segments,
                                 int* number_of_segments);

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
    void GetAllSegmentsByLabel(int label, int **images, int **segments,
                               int *number_of_segments);
};

#endif //WET1STATICEYE_STATICEYE_H
