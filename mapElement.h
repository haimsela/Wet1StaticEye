#ifndef WETONE_MAPELEMENT_H
#define WETONE_MAPELEMENT_H

/** MapElement class and his fields */
/**
 * @tparam T - the class of the key
 * @tparam K - the class of the value
 *
 */
template<class T,class K>
class MapElement {
private:

    /** MapElement's private fields */
    T key;
    K value;
public:
    /** MapElement's public functions */

    /**
    * MapElement() - Node constructor without arguments default.
    */
    explicit MapElement() = default ;


    /** Node's public functions */
    /**
    * MapElement() - MapElement constructor
    */
    explicit MapElement(const T& key, const K& value) : key(key),value(value) {}

    /**
    * MapElement() - MapElement constructor
    */
    explicit MapElement(T key) : key(key),value() {}

    /**
    * ~Node() - the destructor. destroy the Node
    */
    ~MapElement() = default;

    /**
     * MapElement(const MapElement & map) - copy destructor dependent on T,K
     *                                      operator=.
     * @param map_element map element to copy
     */
    MapElement(const MapElement & map_element){this->key=map_element.key;
        this->value=map_element.value;}

    /**
     * delete operator =
     */
    MapElement &operator=(const MapElement &)= delete;

    /**
     * GetKey - return the element key
     *
     * @return the element key
     */
    const T& GetKey() const{return this->key;}

    /**
     * GetValue - return the element value
     *
     * @return the element value
     */
    const K& GetValue() const{return this->value;}

    /**
     * SetKey - set the element key to new value. dependent in T operator=
     */
    void SetKey(T key){this->key=key;}

    /**
     * SetValue - set the element value. dependent in K operator=
     */
    void SetValue(K value){this->value=value;}

};

/**
 * bool operator== comparison operator by mapElement's key. dependent on T
 *                 operator=
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements share the same key - true
 *         else - false
 */
template<class T,class K>
inline bool operator==(const MapElement<T,K>& map_element1,
                       const MapElement<T,K>& map_element2){
    return map_element1.GetKey()==map_element2.GetKey();
}

/**
 * bool operator!= comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements share the same key - true
 *         else - false
 */
template<class T,class K>
inline bool operator!=(const MapElement<T,K>& map_element1,
                       const MapElement<T,K>& map_element2){
    return !(map_element1==map_element2);
}

/**
 * bool operator> comparison operator by mapElement's key. dependent on T
 *                 operator>
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements 1 has greater key - true
 *         else - false
 */
template<class T,class K>
inline bool operator>(const MapElement<T,K>& map_element1,
                      const MapElement<T,K>& map_element2){
    return map_element1.GetKey()>map_element2.GetKey();
}

/**
 * bool operator< comparison operator by mapElement's key
 *
 * @param map_element1 - first mapElement to compare
 * @param map_element2  - second mapElement to compare
 * @return if the mapElements 2 has greater key - true
 *         else - false
 */
template <class T,class K>
inline bool operator<(const MapElement<T,K>& map_element1,
                      const MapElement<T,K>& map_element2){
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
template<class T,class K>
inline bool operator>=(const MapElement<T,K>& map_element1,
                       const MapElement<T,K>& map_element2){
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
template<class T,class K>
inline bool operator<=(const MapElement<T,K>& map_element1,
                       const MapElement<T,K>& map_element2){
    return map_element2>=map_element1;
}

#endif //WETONE_MAPELEMENT_H
