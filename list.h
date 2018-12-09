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
        * GetNodeData() - Get the node data
        *
        * @return the node data
        */
        const T& GetNodeData() { return this->data; };

        /**
        * getNextNode() - Get the next node
        *
        * @return the next node
        */
        Node *GetNextNode() { return this->next_node; };

        /**
        * GetPreviousNode() - Get the previous node
        *
        * @return the previous node
        */
        Node *GetPreviousNode() { return this->previous_node; };


        /**
         * SetNextNode - set the next node for new value
         *
         * @param new_next - the new next node
         */
        void SetNextNode(Node *new_next) { this->next_node = new_next; };

        /**
         * SetPreviousNode - set the previous node for new value
         *
         * @param new_previous the new previous node
         */
        void SetPreviousNode(Node *new_previous) {
                                          this->previous_node = new_previous; };

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
    List &operator=(const List &)= delete;

    /**
     * Find - This function get head node and data to find and returns the node
     *        with the data
     *
     * @param head - head to find from
     * @return the node with the data
     */
    void* Find(const T &data_to_find);

    /**
     * InsertFirst - insert new data as the first in the list
     *
     * @param data_to_insert - the data to insert
     */
    void* InsertFirst(const T &data_to_insert);

    /**
     * Insert - insert new data after a given node
     *
     * @param node_to_insert_after - node to insert the data after
     * @param data_to_insert - the data to insert
     */
    void* Insert(void *node_to_insert_after, const T &data_to_insert);

    /**
     * Remove - delete given node
     *
     * @param node_to_delete - the node to delete
     */
    void Remove(void *node_to_delete) ;

    /**
     * RemoveByData - delete node with given data
     *
     * @param data_to_delete - the data to delete
     */
    void RemoveByData(const T& data_to_delete) ;

    /**
     * ListGetFirst - this function return the first non dummy node
     *
     * @return the first non dummy node
     */
    void* ListGetFirst() const{return this->head->GetNextNode();}

    /**
     * ListGetNextNode - this function get node and returns the next node
     *
     * @param current_node - current node
     * @return the next node
     */
    void* ListGetNextNode(void* current_node) const{
                                return ((Node*)current_node)->GetNextNode();}

    /**
    * GetNodeData - get node and returns the data of the node
    *
    * @param current_node - current node
    * @return the next node
    */
    const T& GetNodeData(void* node) {return ((Node*)node)->GetNodeData();}

    /**
     * GetLength - return the list length
     *
     * @return the list length
     */
    int GetLength() const{return this->length;}

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
    this->head->SetNextNode(this->tail);
    this->tail->SetPreviousNode(this->head);
}

/**
 * ~List() - the destructor. destroy all the nodes in the list and the head
 *
 * @tparam T - the class of the elements in the list
 */
template<class T>
List<T>::~List() {

    while (this->head->GetNextNode() != this->tail) {
        this->Remove(this->head->GetNextNode());
    }

    delete head;
    delete tail;
}

/**
 * Find - This function get head node and data to find and returns the node
 *        with the data
 *
 * @param head - head to find from
 * @return the node with the data
 */
template<class T>
void* List<T>::Find(const T &data_to_find) {
    Node *current_node = this->head->GetNextNode();

    while (current_node != this->tail &&
           current_node->GetNodeData() != data_to_find) {
        current_node = current_node->GetNextNode();
    }

    if (current_node == this->tail){
        throw List::DataNotFoundException();
    }

    return current_node;
}

/**
 * Insert - insert new data after a given node
 *
 * @param node_to_insert_after - node to insert the data after
 * @param data_to_insert - the data to insert
 */
template<class T>
void* List<T>::Insert(void *node_to_insert_after, const T &data_to_insert) {
    Node *new_node;
    if (node_to_insert_after == NULL) {
        return nullptr;
    }
    new_node = new Node(data_to_insert);

    new_node->SetNextNode(((Node*)node_to_insert_after)->GetNextNode());
    ((Node*)node_to_insert_after)->GetNextNode()->SetPreviousNode(new_node);

    ((Node*)node_to_insert_after)->SetNextNode(new_node);
    new_node->SetPreviousNode(((Node*)node_to_insert_after));

    this->length++;
    return new_node;
}

/**
 * InsertFirst - insert new data as the first in the list
 *
 * @param data_to_insert - the data to insert
 */
template<class T>
void* List<T>::InsertFirst(const T &data_to_insert){
    void* new_node = this->Insert(this->head,data_to_insert);
    return new_node;
}

/**
 * Remove - delete given node
 *
 * @param node_to_delete - the node to delete
 */
template<class T>
void List<T>::Remove(void *node_to_delete) {

    Node *temp_node;
    temp_node = ((Node*)node_to_delete);

    temp_node->GetPreviousNode()->SetNextNode(temp_node->GetNextNode());
    temp_node->GetNextNode()->SetPreviousNode(temp_node->GetPreviousNode());

    delete temp_node;

    this->length--;
}

/**
 * RemoveByData - delete node with given data
 *
 * @param data_to_delete - the data to delete
 */
template<class T>
void List<T>::RemoveByData(const T &data_to_delete) {
    void* node_to_delete = this->Find(data_to_delete);
    this->Remove(node_to_delete);
}

#endif //WETONE_LIST_H
