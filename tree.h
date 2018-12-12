#ifndef WETONE_TREE_H
#define WETONE_TREE_H

#include<stdexcept>
#include<iostream>

using namespace std;

/** Tree class and his fields */
/**
 * @tparam T - the class of the elements in the tree
 */
template <class T>
class Tree {
private:

    /** Node class and his fields */
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
        * Node() - Node constructor without arguments.
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
         *
        * @return the node data
        */
        const T& GetNodeData() { return this->data; }

        /**
        * GetRightNode() - Get the right son node
         *
        * @return the right son node
        */
        Node* GetRightNode() { return this->right_node; }


        /**
         * SetNextNode(Node* new_next)() - set the right son node for new value
         *
         * @param new_right - the new right node
         */
        void SetRightNode(Node* new_right){ this->right_node=new_right; }

        /**
        * GetLeftNode() - Get the left son node
         *
        * @return the left son node
        */
        Node* GetLeftNode() { return this->left_node; }

        /**
         * SetNextNode(Node* new_next)() - set the right son node for new value
         *
         * @param new_left - the new left node
         */
        void SetLeftNode (Node* new_left){ this->left_node=new_left; }

        /**
         * GetParentNode - get the parent node
         *
         * @return the parent node
         */
        Node* GetParentNode(){ return this->parent_node;};

        /**
         * SetParentNode - set the parent node to new value
         *
         * @param parent_node - thee new parent node
         */
        void SetParentNode(Node* parent_node){this->parent_node =
                                                                parent_node;}

        /**
         * GetHeight - get the node's height
         *
         * @return the node height
         */
        int GetHeight() { return this->height; }

        /**
         * SetHeight - set the node's height to new value.
         *
         * @param height - the new height
         */
        void SetHeight(int height) { this->height=height; }

        /**
         * GetBalance - get the node's balance. the balance is the left node's
         *              height minus the right node's height.
         *
         * @return the node's balance
         */
        int GetBalance();
    };


    /** Tree's private fields */
    Node* root;
    int size;
    static const int MAXIMUM_ABS_VALID_BALANCE_FACTOR = 1;
    static const int LEFT_TREE_VIOLATED=2;

    /** Tree's private functions */

    /**
     * MakeEmpty - this function recursively delete all the nodes in the tree
     *
     * @param node - the root off the sub tree to delete
     */
    static void MakeEmpty(Node* node);

    /**
     * FindInSubTree - this function find node with given data recursively
     *
     * @param data_to_find - the data to find in the tree
     * @param node - the root off the sub tree to delete
     * @return the node with the given data
     */
    static void* FindInSubTree(const T& data_to_find, Node* node);

    /**
     * GetNextInOrder - get node and returns the next node in order if we
     *                  return the value of the tree in the inorder method
     *
     * @param current_node - the node to look the one after
     * @return the next node in order
     */
    static Node* GetNextInOrder(Node* current_node);

    /**
     * InsertNewNode - get data and insert new node with the data given to the
     *                 tree
     *
     * @param data_to_insert - the data to insert to the tree
     * @return the node new node that was created
     */
    Node* InsertNewNode(const T &data_to_insert);

    /**
     * RemoveNode - Remove Node
     * @param node_to_remove - node to remove
     * @return  node_after_the_one_removed - the node after the one removed
     *                                       to the way to the root
     */

    Node* RemoveNode(Node* node_to_remove);

     /**
      * UpdateNodeHeight - update node height of a node on the tree
      * @param node_to_update - node to update
      */

    void UpdateNodeHeight(Node* node_to_update);

     /**
      * BalanceFactorViolated - Balance factor violated
      * @param root - root of the tree
      * @return  true if the tree it need to rolled, false else
      */

    bool BalanceFactorViolated(Node* root);

    /**
     * SwitchNodesPointers - switch between nodes pointers
     * @param node1 - node one
     * @param node2 - node two
     */

    void SwitchNodesPointers(Node* node1,Node* node2);

    /**
     * RemoveOneOrLessSons - remove node when its case of one or less sons to
     *                       the node to be removed
     * @param node_to_remove - node to remove
     * @param node_before_the_one_removed - node before the one to be removed
     *                                      (the way to the leaf)
     */

    bool RemoveOneOrLessSons(Node* node_to_remove,
                             Node** node_before_the_one_removed);

    /**
    * RemoveLeaf - remove leaf
    * @param leaf_to_remove - leaf to be removed
    */

    void RemoveLeaf(Node* leaf_to_remove);

    /**
     * RemoveOnlyOneSon - remove when its the case of only one son of the
     *                      node to remove
     * @param only_one_son - the node with only one son
     * @param son - the son
     */

    void RemoveOnlyOneSon(Node* only_one_son, Node* son);

    /**
     * RollSubTree - roll the subtree with the fitting roll
     * @param root - the root to check from so on for a roll
     * @return root to roll the subtree
     */

    Node* RollSubTree(Node* root);

    /**
     * Abs - get absolute number
     * @param number - given number
     * @return absolute number
     */

    static int Abs(int number){return number < 0 ? number*-1 : number;};

    /**
     * LLRoll - Left Left Roll the tree
     * @param root root of the tree
     * @return the new root after the roll
     */

    Node* LLRoll(Node* root);

    /**
     * LRRoll - Left Right Roll the tree
     * @param root root of the tree
     * @return the new root after the roll
     */
    Node* LRRoll(Node* root);

    /**
     * RRRoll - Right Right Roll the tree
     * @param root root of the tree
     * @return the new root after the roll
     */
    Node* RRRoll(Node* root);

    /**
     * RLRoll - Right Left Roll the tree
     * @param root root of the tree
     * @return the new root after the roll

     */
    Node* RLRoll(Node* root);

    /**
     * GetNodeHeight - get the node height.
     * @param node - the data to delete
     * @return the node's height.
     */

    static int GetNodeHeight(Node* node);


    /**
     * SetParentNode - set the parent node.
     * @param node_to_set_to - the node to set the parent
     * @param new_parent_node - the parend node to set
     */

    static void SetParentNode(Node* node_to_set_to,Node* new_parent_node);

public:
    /**                    Exceptions                    */
    class DataNotFoundException : public std::exception {};

    /** Tree's public functions */

    /**
    * Tree() - Tree constructor without arguments. The constructor initialize
    *          the head and dummy head node.
    */
    Tree();

    /**
    * ~Tree) - the destructor. destroy all the nodes in the tree and the head
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
     * find - This function get the data to find and returns the node
     *        with the data
     *
     * @param data_to_find - data_to_find
     * @return the node with the data
     */

    void* Find(const T& data_to_find);

    /**
     * insert - insert new node with given data to the tree
     *
     * @param node_to_insert_after - node to insert the data after
     */
    void* Insert(const T &data_to_insert);

    /**
     * remove - delete node after a given node
     *
     * @param node_of_a_tree_to_deleted - node of the tree to be deleted
     */
    void Remove(void* node_of_a_tree_to_deleted);

    /**
     * GetNodeData - get data from given node
     *
     * @param node - given node
     */

    const T& GetNodeData(void* node) {return ((Node*)node)->GetNodeData();};

    /**
     * remove_by_data - delete node with given data
     *
     * @param data_to_delete - the data to delete
     */

    void RemoveByData(const T& data_to_delete) ;

    /**
    * getSize - return the tree length (number of given nodes)
    *
    * @return the tree size
    */
    int GetSize() const{return this->size;}

    /**
     * IsDataExists - This function gets data and check if the data exists in
     *                the tree
     *
     * @param data_to_find the data to find
     * @return true if exists else false
     */
    bool IsDataExists(const T &data_to_find);

    /**
     * GetRoot - return pointer to the root node
     *
     * @return pointer to the root node
     */
    void* GetRoot(){return (void*)this->root;};

    /**
     * GetLeft - return pointer to the left son of the node
     *
     * @param current_node - current node to find the lef son of
     * @return pointer to the left son of the node
     */
    void* GetLeft(void* current_node){return (void*)(((Node*)current_node)->
                                                            GetLeftNode());};

    /**
     * GetRight - return pointer to the left son of the node
     *
     * @param current_node - current node to find the lef son of
     * @return pointer to the left son of the node
     */
    void* GetRight(void* current_node){return (void*)(((Node*)current_node)->
                                                             GetRightNode());};
};

/**
 * Tree() - Tree constructor without arguments. The constructor initialize
 *         the head and dummy head node.
 *
 * @tparam T - the class of the elements in the tree
 */
template <class T>
Tree<T>::Tree() : size(0) {
    this->root= nullptr;//dummy node
}

/**
 * ~Tree() - the destructor. destroy all the nodes in the tree and the head
 *
 * @tparam T - the class of the elements in the tree
 */
    template <class T>
    Tree<T>::~Tree() {
    MakeEmpty(this->root);
}

/**
 * find - this function find node using FindInSubTree
 *
 * @param head - data to find
 * @return the node with the data
 */
 template <class T>
void* Tree<T>::Find(const T& data_to_find){
    void* node_with_date = FindInSubTree(data_to_find,root);

    if(node_with_date == nullptr){
        throw Tree<T>::DataNotFoundException();
    }
    return node_with_date;
}

/**
 * FindInSubTree - this function find node with given data recursively
 *
 * @param data_to_find - the data to find in the tree
 * @param node - the root off the sub tree to delete
 * @return the node with the given data
 */
template <class T>
void* Tree<T>::FindInSubTree(const T& data_to_find, Node* node){
    if(node==nullptr) {
        return nullptr;
    }

    if(node->GetNodeData()==data_to_find) {
        return (void*)node;
    }
    else if(node->GetNodeData()>data_to_find){
        return FindInSubTree(data_to_find,node->GetLeftNode());
    } else {
        return FindInSubTree(data_to_find,node->GetRightNode());
    }
 }

/**
 * insert - insert new data after a given node
 *
 * @param data_to_insert - the data to insert
 */
template <class T>
void* Tree<T>::Insert(const T &data_to_insert) {
    Node* new_node = this->InsertNewNode(data_to_insert);
    this->size++;

    Node* parent_node, *current_node;

    current_node = new_node;

    while (current_node != this->root){
        parent_node = current_node->GetParentNode();

        if(parent_node->GetHeight() >= current_node->GetHeight() + 1){
            return (void*)new_node;
        }

        parent_node->SetHeight(parent_node->GetHeight()+1);

        if(BalanceFactorViolated(parent_node)){
            this->RollSubTree(parent_node);
            return (void*)new_node;
        }

        current_node = parent_node;
    }

    return new_node;
}

/**
 * InsertNewNode - get data and insert new node with the data given to the
 *                 tree
 *
 * @param data_to_insert - the data to insert to the tree
 * @return the node new node that was created
 */
template <class T>
 typename  Tree<T>::Node* Tree<T>::InsertNewNode(const T &data_to_insert) {
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

         if (current_node->GetNodeData() > data_to_insert) {
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

/**
 * RollSubTree - roll the subtree with the fitting roll
 * @param root - the root to check from so on for a roll
 * @return root to roll the subtree
 */

template <class T>
typename  Tree<T>::Node* Tree<T>::RollSubTree(Node* root) {
    if(root->GetBalance()==LEFT_TREE_VIOLATED){
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

/**
 * LLRoll - Left Left Roll the tree
 * @param root root of the tree
 * @return the new root after the roll
 */

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

/**
 * LRRoll - Left Right Roll the tree
 * @param root - root of the tree
 * @return the new root after the roll
 */

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

/**
 * RRRoll - Right Right Roll the tree
 * @param root - root of the tree
 * @return the new root after the roll
 */

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
    A = B->GetRightNode();
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

/**
 * RRRoll - Right Left Roll the tree
 * @param root - root of the tree
 * @return the new root after the roll
 */

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

/**
 * BalanceFactorViolated - Balance factor violated
 * @param root - root of the tree
 * @return  true if the tree it need to rolled, false else
 */


template <class T>
bool Tree<T>::BalanceFactorViolated(Node* root) {
    return Abs(root->GetBalance()) > MAXIMUM_ABS_VALID_BALANCE_FACTOR;
}

/**
 * Remove - delete node after a given node
 *
 * @param delete_after - node to delete the node after
 */
template<class T>
void Tree<T>::Remove(void *node_of_a_tree_to_deleted) {
    Node *node_after_the_one_removed = RemoveNode((Node*)
                                                node_of_a_tree_to_deleted);
    this->size--;

    while(node_after_the_one_removed != nullptr){
        int height_before=node_after_the_one_removed->GetHeight();
        UpdateNodeHeight(node_after_the_one_removed);

        if(BalanceFactorViolated(node_after_the_one_removed)){
            node_after_the_one_removed =
                                      RollSubTree(node_after_the_one_removed);
        }

        if(height_before == node_after_the_one_removed->GetHeight()){
            return;
        }

        node_after_the_one_removed =
                         node_after_the_one_removed->GetParentNode();
    }

}


/**
 * RemoveNode - Remove Node
 * @param node_to_remove - node to remove
 * @return  node_after_the_one_removed - the node after the one removed
 *                                       to the way to the root
 */

template<class T>
typename  Tree<T>::Node* Tree<T>::RemoveNode(Node* node_to_remove){
    Node* node_after_the_one_removed;

    if(RemoveOneOrLessSons(node_to_remove,&node_after_the_one_removed)){
        return node_after_the_one_removed;
    }

    Node *next_inorder = GetNextInOrder(node_to_remove);
    SwitchNodesPointers(next_inorder,node_to_remove);

    RemoveOneOrLessSons(node_to_remove,&node_after_the_one_removed);
    return node_after_the_one_removed;
}

/**
 * UpdateNodeHeight - update node height of a node on the tree
 * @param node_to_update - node to update
 */

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

/**
 * SwitchNodesPointers - switch between nodes pointers
 * @param node1 - node one
 * @param node2 - node two
 */

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
    SetParentNode(node1->GetLeftNode(),node1);
    node2->SetLeftNode(temp_node);
    SetParentNode(node2->GetLeftNode(),node1);

    temp_node = node1->GetRightNode();
    node1->SetRightNode(node2->GetRightNode());
    SetParentNode(node1->GetRightNode(),node1);
    node2->SetRightNode(temp_node);
    SetParentNode(node2->GetRightNode(),node2);

    int temp = node1->GetHeight();
    node1->SetHeight(node2->GetHeight());
    node2->SetHeight(temp);
}

/**
 * RemoveOneOrLessSons - remove node when its case of one or less sons to
 *                       the node to be removed
 * @param node_to_remove - node to remove
 * @param node_before_the_one_removed - node before the one to be removed
 *                                      (the way to the leaf)
 */

template<class T>
bool Tree<T>::RemoveOneOrLessSons(Node* node_to_remove,
                              Node** node_before_the_one_removed){
    *node_before_the_one_removed=node_to_remove->GetParentNode();

    if(node_to_remove->GetRightNode() == nullptr
       && node_to_remove->GetLeftNode() == nullptr){

        RemoveLeaf(node_to_remove);
        return true;

    } else if ( node_to_remove->GetRightNode() == nullptr
                && node_to_remove->GetLeftNode() != nullptr ) {

        RemoveOnlyOneSon(node_to_remove, node_to_remove->GetLeftNode());
        return true;

    } else if ( node_to_remove->GetRightNode() != nullptr
                && node_to_remove->GetLeftNode() == nullptr ) {

        RemoveOnlyOneSon(node_to_remove, node_to_remove->GetRightNode());
        return true;
    }
    return false;
}


/**
 * RemoveLeaf - remove leaf
 * @param leaf_to_remove - leaf to be removed
 */

template<class T>
void Tree<T>::RemoveLeaf(Tree<T>::Node *leaf_to_remove) {

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


/**
 * RemoveOnlyOneSon - remove when its the case of only one son of the
 *                      node to remove
 * @param only_one_son - the node with only one son
 * @param son - the son
 */

template<class T>
void Tree<T>::RemoveOnlyOneSon(Node* only_one_son, Node* son){

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

/**
 * GetNextInOrder - get node and returns the next node in order if we
 *                  return the value of the tree in the inorder method
 *
 * @param current_node - the node to look the one after
 * @return the next node in order
 */
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

/**
 * MakeEmpty - this function recursively delete all the nodes in the tree
 *
 * @param node the root off sun node to delete
 */
template<class T>
void Tree<T>::MakeEmpty(Node* node) {
    if(node== nullptr){
        return;
    }
    MakeEmpty(node->GetLeftNode());
    MakeEmpty(node->GetRightNode());
    delete node;
}

/**
 * GetBalance - get the node's balance. the balance is the left node's
 *              height minus the right node's height.
 *
 * @return the node's balance
 */
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
void Tree<T>::RemoveByData(const T &data_to_delete) {
    void* node_to_delete = this->Find(data_to_delete);
    this->Remove(node_to_delete);
}

/**
 * GetNodeHeight - get the node height.
 * @param node - the data to delete
 * @return the node's height.
 */

template<class T>
int Tree<T>::GetNodeHeight(Node* node){
    return node == nullptr ? Tree<T>::Node::nullptr_height : node->GetHeight();
}


/**
 * SetParentNode - set the parent node.
 * @param node_to_set_to - the node to set the parent
 * @param new_parent_node - the parend node to set
 */
template<class T>
void Tree<T>::SetParentNode(Node* node_to_set_to,Node* new_parent_node){
    if(node_to_set_to == nullptr){
        return;
    } else {
        node_to_set_to->SetParentNode(new_parent_node);
    }
}

/**
 * IsDataExists - This function gets data and check if the data exists in
 *                the list
 *
 * @param data_to_find the data to find
 * @return true if exists else false
 */
template<class T>
bool Tree<T>::IsDataExists(const T &data_to_find){
    return FindInSubTree(data_to_find,this->root) != nullptr;
}

#endif //WETONE_TREE_H

