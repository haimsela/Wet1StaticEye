#ifndef WETONE_LIST_H
#define WETONE_LIST_H

#include <stdexcept>

/** List class and his fields */
/**
 * @tparam T - the class of the elements in the list
 */
template<class T>
class List {
private:

    /** Node class and his fields */
    class Node {
    private:
        /** Node's private fields */
        Node *next_node;
        Node *previous_node;
        T data;
    public:
        /** Node's public functions */
        /**
        * Node() - Node constructor without arguments. Ths use to make
        *          dummy node.
        */
        Node() : next_node(nullptr),previous_node(nullptr) {};

        /**
        * Node() - Node constructor with given data.
        */
        explicit Node(T data) : next_node(nullptr),previous_node(nullptr),
                                data(data) {};

        /**
        * ~Node() - the destructor. destroy the Node
        */
        ~Node() = default;

        /**
         * delete copy c'tor
         */
        Node(const Node &) = delete;

        /**
         * delete operator =
         */
        Node &operator=(const Node &)= delete;


        /**
        * getNodeData() - Get the node data
        * @return the node data
        */
        T getNodeData() const&{ return this->data; };

        /**
        * getNextNode() - Get the next node
        * @return the next node
        */
        Node *getNextNode() const{ return this->next_node; };

        /**
        * getPreviousNode() - Get the previous node
        * @return the previous node
        */
        Node *getPreviousNode() const{ return this->previous_node; };


        /**
        * setNextNode - set the next node for new value
        */
        void setNextNode(Node *new_next) { this->next_node = new_next; };

        /**
        * setPreviousNode - set the previous node for new value
        */
        void setPreviousNode(Node *new_next) {
                                          this->previous_node = new_next; };

    };

    /** List's private fields */
    int length;
    Node *head;
    Node *tail;

public:
    /**                    Exceptions                    */
    class DataNotFoundException : public std::exception {};

    /** List's public functions */

    /**
    * List() - List constructor without arguments. The constructor initialize
    *          the head and dummy head node.
    */
    List();

    /**
    * ~List() - the destructor. destroy all the nodes in the list and the head
    */
    ~List();

    /**
     * delete copy c'tor
     */
    List(const List &) = delete;

    /**
     * delete operator =
     */
    List &operator=(const List &)=delete;

    /**
     * find - This function get head node and data to find and returns the node
     *        with the data
     *
     * @param head - head to find from
     * @return the node with the data
     */
    void* find(const T &data_to_find);

    /**
     * insert_first - insert new data as the first in the list
     *
     * @param data_to_insert - the data to insert
     */
    void* insert_first(const T &data_to_insert);

    /**
     * insert - insert new data after a given node
     *
     * @param node_to_insert_after - node to insert the data after
     * @param data_to_insert - the data to insert
     */
    void* insert(void *node_to_insert_after, const T &data_to_insert);

    /**
     * remove - delete given node
     *
     * @param node_to_delete - the node to delete
     */
    void remove(void *node_to_delete) ;

    /**
     * remove_by_data - delete node with given data
     *
     * @param data_to_delete - the data to delete
     */
    void remove_by_data(const T& data_to_delete) ;

    /**
     * listGetFirst - this function return the first non dummy node
     *
     * @return the first non dummy node
     */
    void* listGetFirst() const{return this->head->getNextNode();};

    /**
     * listGetNextNode - this function get node and returns the next node
     *
     * @param current_node - current node
     * @return the next node
     */
    void* listGetNextNode(void* current_node) const{
                                return ((Node*)current_node)->getNextNode();};

    /**
    * getNodeData - get node and returns the data of the node
    *
    * @param current_node - current node
    * @return the next node
    */
    T getNodeData(void* node) const{return ((Node*)node)->getNodeData();};

    /**
     * getLength - return the list length
     *
     * @return the list length
     */
    int getLength() const{return this->length;}

};

/**
 * List() - List constructor without arguments. The constructor initialize
 *         the head and dummy head node.
 *
 * @tparam T - the class of the elements in the list
 */
template<class T>
List<T>::List() :
        length(0) {
    this->head = new Node();//dummy node
    this->tail = new Node();//dummy node
    this->head->setNextNode(this->tail);
    this->tail->setPreviousNode(this->head);
}

/**
 * ~List() - the destructor. destroy all the nodes in the list and the head
 *
 * @tparam T - the class of the elements in the list
 */
template<class T>
List<T>::~List() {

    while (this->head->getNextNode() != this->tail) {
        this->remove(this->head->getNextNode());
    }

    delete head;
    delete tail;
}

/**
 * find - This function get head node and data to find and returns the node
 *        with the data
 *
 * @param head - head to find from
 * @return the node with the data
 */
template<class T>
void* List<T>::find(const T &data_to_find) {
    Node *current_node = this->head->getNextNode();

    while (current_node != this->tail &&
           current_node->getNodeData() != data_to_find) {
        current_node = current_node->getNextNode();
    }

    if (current_node == this->tail){
        throw List::DataNotFoundException();
    }

    return current_node;
}

/**
 * insert - insert new data after a given node
 *
 * @param node_to_insert_after - node to insert the data after
 * @param data_to_insert - the data to insert
 */
template<class T>
void* List<T>::insert(void *node_to_insert_after, const T &data_to_insert) {
    Node *new_node;
    if (node_to_insert_after == NULL) {
        return nullptr;
    }
    new_node = new Node(data_to_insert);

    new_node->setNextNode(((Node*)node_to_insert_after)->getNextNode());
    ((Node*)node_to_insert_after)->getNextNode()->setPreviousNode(new_node);

    ((Node*)node_to_insert_after)->setNextNode(new_node);
    new_node->setPreviousNode(((Node*)node_to_insert_after));

    this->length++;
    return new_node;
}

/**
 * insert_first - insert new data as the first in the list
 *
 * @param data_to_insert - the data to insert
 */
template<class T>
void* List<T>::insert_first(const T &data_to_insert){
    void* new_node = this->insert(this->head,data_to_insert);
    return new_node;
}

/**
 * remove - delete given node
 *
 * @param node_to_delete - the node to delete
 */
template<class T>
void List<T>::remove(void *node_to_delete) {

    Node *temp_node;
    temp_node = ((Node*)node_to_delete);

    temp_node->getPreviousNode()->setNextNode(temp_node->getNextNode());
    temp_node->getNextNode()->setPreviousNode(temp_node->getPreviousNode());

    delete temp_node;

    this->length--;
}

/**
 * remove_by_data - delete node with given data
 *
 * @param data_to_delete - the data to delete
 */
template<class T>
void List<T>::remove_by_data(const T& data_to_delete) {
    void* node_to_delete = this->find(data_to_delete);
    this->remove(node_to_delete);
}

#endif //WETONE_LIST_H
