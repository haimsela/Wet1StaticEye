#ifndef WETONE_TREE_H
#define WETONE_TREE_H

#include<stdexcept>
#include<iostream>

using namespace std;

/** List class and his fields */
/**
 * @tparam T - the class of the elements in the list
 */
template <class T>
class Tree {
private:

    class Node {
    private:

        static const int initial_height = 0;

        /** Node's private fields */
        Node* parent_node;
        Node* right_node;
        Node* left_node;
        int height;
        T data;
    public:
        static const int nullptr_height = -1;

        /** Node's public functions */
        /**
        * Node() - Node constructor without arguments. Ths use to make
        *          dummy node.
        */
        Node():right_node(nullptr),left_node(nullptr),parent_node(nullptr),
               height(initial_height){}

        /**
        * Node() - Node constructor with given data.
        */
        explicit Node(T data,Node* parent_node):parent_node(parent_node) ,
                                                right_node(nullptr),
                                                left_node(nullptr),
                                                height(initial_height),
                                                data(data){}

        /**
        * ~Node() - the destructor. destroy the Node
        */
        ~Node()=default;

        /**
         * delete copy c'tor
         */
        Node(const Node&)=delete;

        /**
         * delete operator =
         */
        Node& operator=(const Node&)=delete;

        /**
        * GetNodeData() - Get the node data
        * @return the node data
        */
        const T& GetNodeData() { return this->data; }

        /**
        * GetNextNode() - Get the next node
        * @return the next node
        */
        Node* GetRightNode() { return this->right_node; }


        /**
        * SetNextNode(Node* new_next)() - set the next node for new value
        */
        void SetRightNode(Node* new_next){ this->right_node=new_next; }

        /**
        * GetNextNode() - Get the next node
        * @return the next node
        */
        Node* GetLeftNode() { return this->left_node; }

        /**
        * SetNextNode(Node* new_next)() - set the next node for new value
        */
        void SetLeftNode (Node* new_next){ this->left_node=new_next; }

        Node* GetParentNode(){ return this->parent_node;};

        void SetParentNode(Node* parent_node){this->parent_node =
                                                                parent_node;}

        int GetHeight() { return this->height; }

        void SetHeight(int height) { this->height=height; }

        int GetBalance();
    };


    /** List's private fields */
    Node* root;
    int size;
    static const int maximum_abs_valid_balance_factor = 1;
    static const int left_tree_violated=2;

    /** List's private functions */
    void MakeEmpty(Node* node);
    void* FindInSubTree(const T& data_to_find, Node* node);
    Node* GetNextInOrder(Node* current_node);
    Node* insert_new_node(const T &data_to_insert);
    Node* remove_node(Node* node_to_remove);
    void UpdateNodeHeight(Node* node_to_update);
    bool BalanceFactorViolated(Node* root);
    void SwitchNodesPointers(Node* node1,Node* node2);
    bool RemoveOneOrLessSons(Node* node_to_remove,
                             Node** node_before_the_one_removed);
    void remove_leaf(Node* leaf_to_remove);
    void remove_only_one_son(Node* only_one_son, Node* son);
    Node* RollSubTree(Node* root);
    static int abs(int number){return number < 0 ? number*-1 : number;};
    Node* LLRoll(Node* root);
    Node* LRRoll(Node* root);
    Node* RRRoll(Node* root);
    Node* RLRoll(Node* root);
    static int GetNodeHeight(Node* node);
    static void SetParentNode(Node* node_to_set_to,Node* new_parent_node);

public:
    /**                    Exceptions                    */
    class DataNotFoundException : public std::exception {};

    /** List's public functions */

    /**
    * List() - List constructor without arguments. The constructor initialize
    *          the head and dummy head node.
    */
    Tree();

    /**
    * ~List() - the destructor. destroy all the nodes in the list and the head
    */
    ~Tree();

    /**
     * delete copy c'tor
     */
    Tree(const Tree&)=delete;

    /**
     * delete operator =
     */
    Tree& operator=(const Tree&)=delete;

    /**
     * find - This function get head node and data to find and returns the node
     *        with the data
     *
     * @param head - head to find from
     * @return the node with the data
     */

    void* find(const T& data_to_find);

    /**
     * insert - insert new data after a given node
     *
     * @param node_to_insert_after - node to insert the data after
     * @param data_to_insert - the data to insert
     */
    void* insert(const T &data_to_insert);

    /**
     * remove - delete node after a given node
     *
     * @param delete_after - node to delete the node after
     */
    void remove(void* node_of_a_tree_to_deleted);

    const T& GetNodeData(void* node) {return ((Node*)node)->GetNodeData();};

    /**
     * remove_by_data - delete node with given data
     *
     * @param data_to_delete - the data to delete
     */
    void remove_by_data(const T& data_to_delete) ;

    /**
    * getLength - return the list length
    *
    * @return the list length
    */
    int GetSize() const{return this->size;}

};

/**
 * Tree() - Tree constructor without arguments. The constructor initialize
 *         the head and dummy head node.
 *
 * @tparam T - the class of the elements in the list
 */
template <class T>
Tree<T>::Tree() : size(0) {
    this->root= nullptr;//dummy node
}

/**
 * ~List() - the destructor. destroy all the nodes in the list and the head
 *
 * @tparam T - the class of the elements in the list
 */
    template <class T>
    Tree<T>::~Tree() {
    MakeEmpty(this->root);
}

/**
 * find - This function get head node and data to find and returns the node
 *        with the data
 *
 * @param head - head to find from
 * @return the node with the data
 */
 template <class T>
void* Tree<T>::find(const T& data_to_find){
    void* node_with_date = FindInSubTree(data_to_find,root);

    if(node_with_date == nullptr){
        throw DataNotFoundException();
    }
    return node_with_date;
}

template <class T>
void* Tree<T>::FindInSubTree(const T& data_to_find, Node* node){
    if(node==nullptr) {
        return nullptr;
    }

    if(node->GetNodeData()==data_to_find) {
        return (void*)node;
    }
    else if(node->GetNodeData()<data_to_find){
        return FindInSubTree(data_to_find,node->GetLeftNode());
    } else {
        return FindInSubTree(data_to_find,node->GetRightNode());
    }
 }

/**
 * insert - insert new data after a given node
 *
 * @param node_to_insert_after - node to insert the data
 * @param data_to_insert - the data to insert
 */
template <class T>
void* Tree<T>::insert(const T &data_to_insert) {
    Node* new_node = this->insert_new_node(data_to_insert);
    Node* parent_node, *current_node;

    current_node = new_node;

    while (current_node != this->root){
        parent_node = current_node->GetParentNode();

        if(parent_node->GetHeight() >= current_node->GetHeight() + 1){
            this->size++;
            return (void*)new_node;
        }

        parent_node->SetHeight(parent_node->GetHeight()+1);

        if(BalanceFactorViolated(parent_node)){
            this->RollSubTree(parent_node);
            this->size++;
            return (void*)new_node;
        }

        current_node = parent_node;
    }

    this->size++;
    return new_node;
}

 /** List's private functions */
 template <class T>
 typename  Tree<T>::Node* Tree<T>::insert_new_node(const T &data_to_insert) {
     if(this->root == nullptr){
         Node *node_to_insert = new Node(data_to_insert, nullptr);
         this->root=node_to_insert;
         return node_to_insert;
     }

     Node *node_to_insert = new Node(data_to_insert, nullptr);

     Node *current_node, *parent_node;
     current_node = this->root;

     do {
         parent_node = current_node;

         if (current_node->GetNodeData() < data_to_insert) {
             current_node = parent_node->GetLeftNode();
             if(current_node == nullptr){
                 parent_node->SetLeftNode(node_to_insert);
             }
         } else {
             current_node = parent_node->GetRightNode();
             if(current_node == nullptr){
                 parent_node->SetRightNode(node_to_insert);
             }
         }
     } while(current_node != nullptr);

     SetParentNode(node_to_insert,parent_node);
     return node_to_insert;
}

template <class T>
typename  Tree<T>::Node* Tree<T>::RollSubTree(Node* root) {
    if(root->GetBalance()==left_tree_violated){
        if(root->GetLeftNode()->GetBalance()>=0){
            return this->LLRoll(root);
        } else {
            return this->LRRoll(root);
        }
    } else {
        if(root->GetRightNode()->GetBalance()<=0){
            return this->RRRoll(root);
        } else {
            return this->RLRoll(root);
        }
    }
}

template <class T>
typename  Tree<T>::Node* Tree<T>::LLRoll(Node* root){

    /**
    *     The Tree
    *       B
    *     A   B_l
    *   A_l A_r
    *  v
    */

    Node *A,*B,*A_right;

    B = root;
    A = B->GetLeftNode();
    A_right = A->GetRightNode();

    if(B->GetParentNode()!=nullptr){
        if(B->GetParentNode()->GetRightNode()==B){
            B->GetParentNode()->SetRightNode(A);
        } else {
            B->GetParentNode()->SetLeftNode(A);
        }

        SetParentNode(A,B->GetParentNode());

    } else {
        this->root=A;
        A->SetParentNode(nullptr);
    }

    B->SetLeftNode(A_right);
    SetParentNode(A_right,B);

    A->SetRightNode(B);
    SetParentNode(B,A);

    UpdateNodeHeight(B);
    UpdateNodeHeight(A);

    return A;
}

template <class T>
typename  Tree<T>::Node* Tree<T>::LRRoll(Node* root){
    Node *A,*B,*C,*B_left,*B_right;

     /**
     *     The Tree
     *       C
     *     A   C_r
     *  A_l B
     *    B_l B_r
     *    v or v
     */

    C = root;
    A = C->GetLeftNode();
    B = A->GetRightNode();
    B_left = B->GetLeftNode();
    B_right = B->GetRightNode();

    if(C->GetParentNode()!=nullptr){
        if(C->GetParentNode()->GetRightNode()==C){
            C->GetParentNode()->SetRightNode(B);
        } else {
            C->GetParentNode()->SetLeftNode(B);
        }

        SetParentNode(B,C->GetParentNode());

    } else {
        this->root=B;
        B->SetParentNode(nullptr);
    }

    B->SetLeftNode(A);
    SetParentNode(A,B);

    B->SetRightNode(C);
    SetParentNode(C,B);

    C->SetLeftNode(B_right);
    SetParentNode(B_right,C);

    A->SetRightNode(B_left);
    SetParentNode(B_left,A);

    UpdateNodeHeight(A);
    UpdateNodeHeight(C);
    UpdateNodeHeight(B);

    return B;
}

template <class T>
typename  Tree<T>::Node* Tree<T>::RRRoll(Node* root){

    /**
    *     The Tree
    *       B
    *   B_l   A
    *      A_l A_r
    *            v
    */

    Node *A,*B,*A_left;

    B = root;
    A = B->GetLeftNode();
    A_left = A->GetLeftNode();

    if(B->GetParentNode()!=nullptr){
        if(B->GetParentNode()->GetRightNode()==B){
            B->GetParentNode()->SetRightNode(A);
        } else {
            B->GetParentNode()->SetLeftNode(A);
        }

        SetParentNode(A,B->GetParentNode());

    } else {
        this->root=A;
        A->SetParentNode(nullptr);
    }

    B->SetRightNode(A_left);
    SetParentNode(A_left,B);

    A->SetLeftNode(B);
    SetParentNode(B,A);

    UpdateNodeHeight(B);
    UpdateNodeHeight(A);

    return A;
}

template <class T>
typename  Tree<T>::Node* Tree<T>::RLRoll(Node* root){
    Node *A,*B,*C,*B_left,*B_right;

    /**
    *     The Tree
    *         C
    *     C_l   A
    *          B A_r
    *      B_l B_r
    *      v or v
    */

    C = root;
    A = C->GetRightNode();
    B = A->GetLeftNode();
    B_left = B->GetLeftNode();
    B_right = B->GetRightNode();

    if(C->GetParentNode()!=nullptr){
        if(C->GetParentNode()->GetRightNode()==C){
            C->GetParentNode()->SetRightNode(B);
        } else {
            C->GetParentNode()->SetLeftNode(B);
        }

        SetParentNode(B,C->GetParentNode());

    } else {
        this->root=B;
        B->SetParentNode(nullptr);
    }

    B->SetRightNode(A);
    SetParentNode(A,B);

    B->SetLeftNode(C);
    SetParentNode(C,B);

    C->SetRightNode(B_left);
    SetParentNode(B_left,C);

    A->SetLeftNode(B_right);
    SetParentNode(B_right,A);

    UpdateNodeHeight(A);
    UpdateNodeHeight(C);
    UpdateNodeHeight(B);

    return B;
}


template <class T>
bool Tree<T>::BalanceFactorViolated(Node* root) {
    return abs(root->GetBalance()) > maximum_abs_valid_balance_factor;
}

/**
 * delete_after - delete node after a given node
 *
 * @param delete_after - node to delete the node after
 */
template<class T>
void Tree<T>::remove(void *node_of_a_tree_to_deleted) {
    Node *node_after_the_one_removed = remove_node((Node*)
                                                node_of_a_tree_to_deleted);

    while(node_after_the_one_removed != nullptr){
        int height_before=node_after_the_one_removed->GetHeight();
        UpdateNodeHeight(node_after_the_one_removed);

        if(BalanceFactorViolated(node_after_the_one_removed)){
            node_after_the_one_removed =
                                      RollSubTree(node_after_the_one_removed);
        }

        if(height_before == node_after_the_one_removed->GetHeight()){
            this->size--;
            return;
        }

        node_after_the_one_removed =
                         node_after_the_one_removed->GetParentNode();
    }

    this->size--;
}

template<class T>
typename  Tree<T>::Node* Tree<T>::remove_node(Node* node_to_remove){
    Node* node_after_the_one_removed;

    if(RemoveOneOrLessSons(node_to_remove,&node_after_the_one_removed)){
        return node_after_the_one_removed;
    }

    Node *next_inorder = GetNextInOrder(node_to_remove);
    SwitchNodesPointers(next_inorder,node_to_remove);

    RemoveOneOrLessSons(node_to_remove,&node_after_the_one_removed);
    return node_after_the_one_removed;
}

template<class T>
void Tree<T>::UpdateNodeHeight(Node* node_to_update){
    if(GetNodeHeight(node_to_update->GetRightNode()) >
                   GetNodeHeight(node_to_update->GetLeftNode()) ){
        node_to_update->SetHeight(GetNodeHeight(node_to_update->GetRightNode())
                                                                      +1);
    } else {
        node_to_update->SetHeight(GetNodeHeight(node_to_update->GetLeftNode())
                                  +1);
    }
}

template<class T>
void Tree<T>::SwitchNodesPointers(Node* node1,Node* node2){
    Node *temp_node;

    if(node1->GetParentNode()->GetRightNode()== node1){
        node1->GetParentNode()->SetRightNode(node2);
    } else {
        node1->GetParentNode()->SetLeftNode(node2);
    }

    if(node2->GetParentNode()->GetRightNode()== node2){
        node2->GetParentNode()->SetRightNode(node1);
    } else {
        node2->GetParentNode()->SetLeftNode(node1);
    }

    temp_node = node1->GetParentNode();
    SetParentNode(node1,node2->GetParentNode());
    SetParentNode(node2,temp_node);

    temp_node = node1->GetLeftNode();
    node1->SetLeftNode(node2->GetLeftNode());
    node2->SetLeftNode(temp_node);

    temp_node = node1->GetRightNode();
    node1->SetRightNode(node2->GetRightNode());
    node2->SetRightNode(temp_node);

    int temp = node1->GetHeight();
    node1->SetHeight(node2->GetHeight());
    node2->SetHeight(temp);
}

template<class T>
bool Tree<T>::RemoveOneOrLessSons(Node* node_to_remove,
                              Node** node_before_the_one_removed){
    *node_before_the_one_removed=node_to_remove->GetParentNode();

    if(node_to_remove->GetRightNode() == nullptr
       && node_to_remove->GetLeftNode() == nullptr){

        remove_leaf(node_to_remove);
        return true;

    } else if ( node_to_remove->GetRightNode() == nullptr
                && node_to_remove->GetLeftNode() != nullptr ) {

        remove_only_one_son(node_to_remove, node_to_remove->GetLeftNode());
        return true;

    } else if ( node_to_remove->GetRightNode() != nullptr
                && node_to_remove->GetLeftNode() == nullptr ) {

        remove_only_one_son(node_to_remove, node_to_remove->GetRightNode());
        return true;
    }
    return false;
}

template<class T>
void Tree<T>::remove_leaf(Node* leaf_to_remove){

    if(leaf_to_remove->GetParentNode()== nullptr){
        this->root= nullptr;
        delete leaf_to_remove;
        return;
    }

    if(leaf_to_remove->GetParentNode()->GetRightNode()== leaf_to_remove){
        leaf_to_remove->GetParentNode()->SetRightNode(nullptr);
        delete leaf_to_remove;
    } else {
        leaf_to_remove->GetParentNode()->SetLeftNode(nullptr);
        delete leaf_to_remove;
    }
}

template<class T>
void Tree<T>::remove_only_one_son(Node* only_one_son, Node* son){

    if(only_one_son->GetParentNode()== nullptr){
        this->root= son;
        SetParentNode(son,nullptr);
        delete only_one_son;
        return;
    }

    if(only_one_son->GetParentNode()->GetRightNode()== only_one_son){
        only_one_son->GetParentNode()->SetRightNode(son);
    } else {
        only_one_son->GetParentNode()->SetLeftNode(son);
    }

    SetParentNode(son,only_one_son->GetParentNode());
    delete only_one_son;
}

template<class T>
typename Tree<T>::Node* Tree<T>::GetNextInOrder(Node* current_node){
    if(current_node == nullptr){
        return nullptr;
    }

    if(current_node->GetRightNode() == nullptr){
        return nullptr;
    }

    Node* next_inorder = current_node->GetRightNode();

    while(next_inorder->GetLeftNode() != nullptr){
        next_inorder = next_inorder->GetLeftNode();
    }

    return next_inorder;
}

template<class T>
void Tree<T>::MakeEmpty(Node* node) {
    if(node== nullptr){
        return;
    }
    MakeEmpty(node->GetLeftNode());
    MakeEmpty(node->GetRightNode());
    delete node;
}

template <class T>
int Tree<T>::Node::GetBalance() {

        return (GetNodeHeight(this->GetLeftNode()) -
                                       GetNodeHeight(this->GetRightNode()));
}

/**
 * remove_by_data - delete node with given data
 *
 * @param data_to_delete - the data to delete
 */
template<class T>
void Tree<T>::remove_by_data(const T& data_to_delete) {
    void* node_to_delete = this->find(data_to_delete);
    this->remove(node_to_delete);
}

template<class T>
int Tree<T>::GetNodeHeight(Node* node){
    return node == nullptr ? Tree<T>::Node::nullptr_height : node->GetHeight();
}

template<class T>
void Tree<T>::SetParentNode(Node* node_to_set_to,Node* new_parent_node){
    if(node_to_set_to == nullptr){
        return;
    } else {
        node_to_set_to->SetParentNode(new_parent_node);
    }
}

#endif //WETONE_TREE_H

