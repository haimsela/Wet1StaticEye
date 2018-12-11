#ifndef WETONE_MAPLIST_H
#define WETONE_MAPLIST_H

#include <stdexcept>
#include "mapElement.h"
#include "list.h"

/** MapList class and his fields */
/**
 * @tparam T - the class of the key
 * @tparam K - the class of the value
 *
 */
template<class T,class K>
class MapList {
private:

    /** MapList's private fields */
    List<MapElement<T,K>> map_list;

public:
    /**                    Exceptions                    */
    class DataNotFoundException : public std::exception {};
    class KeyAlreadyExists : public std::exception {};

    /** MapList's public functions */

    /**
    * MapList(() - MapList constructor without arguments. The default
     *             constructor
    */
    MapList()=default;

    /**
    * ~MapList() - the destructor. The default destructor
    */
    ~MapList()=default;

    /**
     * delete copy c'tor
     */
    MapList(const MapList &) = delete;

    /**
     * delete operator =
     */
    MapList &operator=(const MapList &)= delete;

    /**
     * Add - This function get a key and value to enter the map. create a new
     *       map element with the data and enter the element to the list of
     *       elements in case the key not exists in the map. if the key exists
     *       throw exception.
     *
     * @param key - key to add
     * @param value - value to add
     * @return pointer to the node with the data
     */
    void* Add(const T &key,const K &value);

    /**
     * FindKey - find a key in the map. if the key exists return the value of
     *           the element otherwise throw exception
     *
     * @param key - key to find
     * @return the value of the element if the key found otherwise throw
     *         exception
     */
    const K& FindKey(const T &key);

    /**
     * DeleteKey - get a key and remove the mep element with the data if the
     *             key exists otherwise throw exception
     *
     * @param key - key to delete
     */
    void DeleteKey(const T &key);

    /**
     * DeleteByPointer - get node of map element and delete the element from
     *                   the map
     *
     * @param node - node to delete
     */
    void DeleteByPointer(void* node);

    /**
     * GetMapSize - return the number of elements in the map
     *
     * @return the number of elements in the map
     */
    int GetMapSize();

    /**
     * GetFirstNode - get the first node of the list
     *
     * @return - the first node in the list
     */
    void* GetFirstNode(){return this->map_list.ListGetFirst();}

    /**
     * GetFirstNode - get the first node of the list
     *
     * @return - the next node of the map
     */
    void* GetNextNode(void* current_node){
                          return this->map_list.ListGetNextNode(current_node);}

    /**
     * GetNodeData - get node and return the map element of the node
     *
     * @param current_node - node to get the element of
     * @return the map element of the node
     */
    const MapElement<T,K>& GetNodeData(void* current_node){
        return this->map_list.GetNodeData(current_node);}

};

/**
 * Add - This function get a key and value to enter the map. create a new
 *       map element with the data and enter the element to the list of
 *       elements in case the key not exists in the map. if the key exists
 *       throw exception.
 *
 * @param key - key to add
 * @param value - value to add
 * @return pointer to the node with the data
 */
template<class T,class K>
void* MapList<T,K>::Add(const T &key,const K &value){

    MapElement<T,K> new_element(key,value);

    return this->map_list.InsertFirst(new_element);

}

/**
 * FindKey - find a key in the map. if the key exists return the value of
 *           the element otherwise throw exception
 *
 * @param key - key to find
 * @return the value of the element if the key found otherwise throw
 *         exception
 */
template<class T,class K>
const K& MapList<T,K>::FindKey(const T &key){
    try {
        MapElement<T,K> new_element(key);

        void* node = this->map_list.Find(new_element);
        MapElement<T,K> element_searched = this->map_list.GetNodeData(node);
        return  element_searched.GetValue();
    } catch (typename List<MapElement<T,K>>::DataNotFoundException&
                                                                   not_found ){
        throw MapList<T,K>::DataNotFoundException();
    } catch (std::bad_alloc& bad_allocation ) {
        throw bad_allocation;
    }
}

/**
 * DeleteKey - get a key and remove the mep element with the data if the
 *             key exists otherwise throw exception
 *
 * @param key - key to delete
 */
template<class T,class K>
void MapList<T,K>::DeleteKey(const T &key){
    try {
        MapElement<T, K> new_element(key);
        this->map_list.RemoveByData(new_element);
    } catch (typename List<MapElement<T,K>>::DataNotFoundException&
    not_found ){
        throw MapList<T,K>::DataNotFoundException();
    } catch (std::bad_alloc& bad_allocation ) {
        throw bad_allocation;
    }
}

/**
 * DeleteByPointer - get node of map element and delete the element from
 *                   the map
 *
 * @param node - node to delete
 */
template<class T,class K>
void MapList<T,K>::DeleteByPointer(void* node){
    this->map_list.Remove(node);
}

/**
 * GetMapSize - return the number of elements in the map
 *
 * @return the number of elements in the map
 */
template<class T,class K>
int MapList<T,K>::GetMapSize(){
    return this->map_list.GetLength();
}

#endif //WETONE_MAPLIST_H
