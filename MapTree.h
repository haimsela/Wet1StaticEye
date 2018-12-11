#ifndef WETONE_MAPTREE_H
#define WETONE_MAPTREE_H

#include <stdexcept>
#include "mapElement.h"
#include "tree.h"

/** MapTree class and his fields */
/**
 * @tparam T - the class of the key
 * @tparam K - the class of the value
 *
 */
template<class T,class K>
class MapTree {
private:

    /** MapTree's private fields */
    Tree<MapElement<T,K>> map_tree;

public:
    /**                    Exceptions                    */
    class DataNotFoundException : public std::exception {};
    class KeyAlreadyExists : public std::exception {};

    /** MapTree's public functions */

    /**
    * MapTree(() - MapTree constructor without arguments. The default
    *              constructor
    */
    MapTree()=default;

    /**
    * ~MapTree() - the destructor. The default destructor
    */
    ~MapTree()=default;

    /**
     * delete copy c'tor
     */
    MapTree(const MapTree &) = delete;

    /**
     * delete operator =
     */
    MapTree &operator=(const MapTree &)= delete;

    /**
     * Add - This function get a key and value to enter the map. create a new
     *       map element with the data and enter the element to the tree of
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

    // for the test
    const T& GetNodeData(void * node){return
                                          map_tree.GetNodeData(node).GetKey();}

    /**
     * IsKeyExists - The function check if key exists in the map
     *
     * @param key - key to check
     * @return - true of if exists otherwise false
     */
    bool IsKeyExists(const T &key);
};

/**
 * Add - This function get a key and value to enter the map. create a new
 *       map element with the data and enter the element to the tree of
 *       elements in case the key not exists in the map. if the key exists
 *       throw exception.
 *
 * @param key - key to add
 * @param value - value to add
 * @return pointer to the node with the data
 */
template<class T,class K>
void* MapTree<T,K>::Add(const T &key,const K &value){

    if(IsKeyExists(key) ){
        throw KeyAlreadyExists();
    }

    MapElement<T,K> new_element(key,value);
    return this->map_tree.Insert(new_element);

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
const K& MapTree<T,K>::FindKey(const T &key){
    try {
        MapElement<T,K> new_element(key);

        void* node = this->map_tree.Find(new_element);
        return  this->map_tree.GetNodeData(node).GetValue();

    } catch (typename Tree<MapElement<T,K>>::DataNotFoundException&
    not_found ){
        throw MapTree<T,K>::DataNotFoundException();
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
void MapTree<T,K>::DeleteKey(const T &key){
    try {
        MapElement<T, K> new_element(key);
        this->map_tree.RemoveByData(new_element);
    } catch (typename Tree<MapElement<T,K>>::DataNotFoundException&
    not_found ){
        throw MapTree<T,K>::DataNotFoundException();
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
void MapTree<T,K>::DeleteByPointer(void* node){
    this->map_tree.Remove(node);
}

/**
 * GetMapSize - return the number of elements in the map
 *
 * @return the number of elements in the map
 */
template<class T,class K>
int MapTree<T,K>::GetMapSize(){
    return this->map_tree.GetSize();
}

/**
 * IsKeyExists - The function check if key exists in the map
 *
 * @param key - key to check
 * @return - true of if exists otherwise false
 */
template<class T,class K>
bool MapTree<T,K>::IsKeyExists(const T &key){
    MapElement<T, K> new_element(key);
    return this->map_tree.IsDataExists(new_element);
}

#endif //WETONE_MAPTREE_H
