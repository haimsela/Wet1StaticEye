#ifndef WETONE_MAPELEMENT_H
#define WETONE_MAPELEMENT_H

/** MapElement class and his fields */
class MapElement {
private:

    /** MapElement's private fields */
    int key;
    void* value;
public:
    /** MapElement's public functions */

    /**
    * MapElement() - Node constructor without arguments. Ths use to make
    *          dummy node.
    */
    explicit MapElement() : value(nullptr) {}


    /** Node's public functions */
    /**
    * MapElement() - MapElement constructor
    */
    explicit MapElement(int key,void* value) : key(key),value(value) {}

    /**
    * ~Node() - the destructor. destroy the Node
    */
    ~MapElement() = default;

    /**
     * delete copy c'tor
     */
    MapElement(const MapElement & map){this->key=map.key;
                                       this->value=map.value;}

    /**
     * delete operator =
     */
    MapElement &operator=(const MapElement &)= delete;

    /**
     * getKey - return the element key
     *
     * @return the element key
     */
    int getKey() const{return this->key;}

    /**
     * getValue - return the element value
     *
     * @return the element value
     */
    void* getValue() const{return this->value;}

    /**
     * setKey - set the element key to new value
     */
    void setKey(int key){this->key=key;}

    /**
     * setKey - set the element value
     */
    void setValue(void* value){this->value=value;}

};

/**
 * bool operator== comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements share the same key - true
 *         else - false
 */
inline bool operator==(const MapElement& map_element1,const MapElement& map_element2){
    return map_element1.getKey()==map_element2.getKey();
}

/**
 * bool operator!= comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements share the same key - true
 *         else - false
 */
inline bool operator!=(const MapElement& map_element1,const MapElement& map_element2){
    return !(map_element1==map_element2);
}

/**
 * bool operator> comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements 1 has greater key - true
 *         else - false
 */
inline bool operator>(const MapElement& map_element1,const MapElement& map_element2){
    return map_element1.getKey()>map_element2.getKey();
}

/**
 * bool operator< comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements 2 has greater key - true
 *         else - false
 */
inline bool operator<(const MapElement& map_element1,const MapElement& map_element2){
    return map_element2>map_element1;
}

/**
 * bool operator>= comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements 1 has greater or equals key - true
 *         else - false
 */
inline bool operator>=(const MapElement& map_element1,const MapElement& map_element2){
    return !(map_element2>map_element1);
}

/**
 * bool operator>= comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements 2 has greater or equals key - true
 *         else - false
 */
inline bool operator<=(const MapElement& map_element1,const MapElement& map_element2){
    return map_element2>=map_element1;
}

#endif //WETONE_MAPELEMENT_H
