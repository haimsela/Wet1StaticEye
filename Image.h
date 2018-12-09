#ifndef WET1STATICEYE_IMAGE_H
#define WET1STATICEYE_IMAGE_H

#include "list.h"

/** Game class and his fields */
class Image {
    int segments;
    int* segments_array;
    List<int> uninitialized_segments;
    static const int UNINITIALIZED_SEGMENT = 0;

    /** Image's private functions */

    /**
     * InitializeUninitializedSegmentsList - this function get uninitialized
     *                                       list that represent all the
     *                                       uninitialized segments in the
     *                                       image. an init all the segments
     *                                       are uninitialized.
     *
     * @param uninitialized_segments_list - pointer to uninitialized list that
     *                                      at the end of this function will
     *                                      contain all the segments of the
     *                                      image
     *
     * @param segments - number of segments in the image
     */
    static void InitializeUninitializedSegmentsList(
                                        List<int>* uninitialized_segments_list,
                                        int segments);

    /**
     * InitializeSegmentsArray - this function get segments array and the
     *                           the number of segments in the image and
     *                           set all the cells in the array to be
     *                           UNINITIALIZED_SEGMENT
     *
     * @param segments_array - the segments array
     * @param segments - number of segments in the image
     */
    static void InitializeSegmentsArray(int* segments_array, int segments);

    /**
     * IsSegmentIdLegal - this function check if segment id is ok dependent
     *                    by the number of segments in the array
     *
     * @param segment_id - segment id
     * @return true if legal otherwise false
     */
    bool IsSegmentIdLegal(int segment_id);

    /**
    * IsLabelLegal - this function check if label is legal
    *
    * @param label - label to check
    * @return true if legal otherwise false
    */
    static bool IsLabelLegal(int label);

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
    static void FillUnlabeledArrayUsingTheUnlabeledList(
            List<int>* uninitialized_segments_list,
            int* segments,
            int number_of_uninitialized_segments);

    /**
     * FindNumberOfSegmentsWithLabel - this function get label and return the
     *                                 number of segments in the image with
     *                                 the label
     *
     * @param label - label to search
     * @return number of segments with the label
     */
    int FindNumberOfSegmentsWithLabel(int label);

public:
    /**                    Exceptions                    */
    class InvalidInput : public std::exception {};
    class Failure : public std::exception {};

    /**
     * Image(int segments) - constructor that gets the number of segments in
     *                       the image and initialize the arrat and the list
     *
     * @param segments - the number of segments in the image
     */
    explicit Image(int segments);

    /**
     * ~Image() - the image destructor destroy the list(automatically using
     *            the list destructor) and delete the segments array
     */
    ~Image();

    /**
     * AddLabel - this function get segment id and label and add the label to
     *            the segment. if one of the parameter is incorrect or the
     *            segment is already labeled throw error.
     *            this function also update the uninitialized segments list
     *
     * @param segment_id - segment id to add the label to
     * @param label - label to add
     */
    void AddLabel(int segment_id,int label);

    /**
     * GetLabel - this function get segment id and return the label of the
     *            segment. if the segment id is invalid or the segment is
     *            uninitialized throw error
     *
     * @param segment_id - the segment id to get the label to
     * @return
     */
    int GetLabel(int segment_id);

    /**
     * DeleteLabel - this function get segment id and return delete the label
     *               of the segment. if the segment id is invalid or the
     *               segment is uninitialized throw error. this function also
     *               update the uninitialized segments list
     *
     * @param segment_id - the segment id to delete the label to
     */
    void DeleteLabel(int segment_id);

    /**
     * GetAllUnLabeledSegments - fill the give segments array with all the
     *                           unlabeled segments ids and return the number
     *                           of unlabeled segments
     *
     * @param segments - pointer to array to create with all the uninitialized
     *                   segments
     * @return the number of unlabeled index
     */
    int GetAllUnLabeledSegments(int **segments);

    /**
     * GetAllSegmentsByLabel - This function get already allocated array and
     *                         fill the array with all the segments in the
     *                         image with the given label.
     *
     * @param segments - the segments array
     * @param label - the label to find
     */
    void GetAllSegmentsByLabel(int **segments, int label );
};



#endif //WET1STATICEYE_IMAGE_H
