//Davydov Danil
//the code was tested on samples from:
#include<iostream>

using namespace std;
/*
 * Structure to represent node in Doubly Linked List
 */
template<typename T>
struct link{
    link* prev;
    T obj;
    link* next;
};
/**
 * Abstract class for implementation a list.
 * @tparam T data type that is to be kept in a list.
 */
template<typename T>
class LinkedList{
public:
    virtual bool empty() = 0;
    virtual void push_back(T) = 0;
    virtual T pop() = 0;
    virtual void peek() = 0;
    virtual unsigned long long length()=0;
    virtual T elAt(int) = 0;
};
/**
 * Implementation of a data structure Doubly Linked List.
 * @tparam T data type that is to be kept in a list.
 */
template<typename T>
class List: public LinkedList<T>{
public:
    List(){ // constructor
        ptr->prev = ptr;
        ptr->next = ptr;
        size = 0;
    }
    /**
     * Destructor. Worst case time complexity is O(n).
     */
    ~List(){// destructor to free all data
        while(ptr != ptr->next){
            link<T>* t = ptr->next;
            ptr->next = t->next;
            delete t;
        }
        delete ptr;
    }
    /**
     * Checking if list is empty.
     * Worst case time complexity is O(1).
     * @return true if list is empty, false otherwise.
     */
    bool empty() override{
        return size == 0;
    }
    /**
     * Pushing element in a list.
     * Worst case time complexity is O(1).
     * @param obj element to be pushed.
     */
    void push_back(T obj) override{
        link<T>* top = ptr->prev;
        link<T>* node = new link<T>;
        node->prev = top;
        node->next = ptr;
        ptr->prev = node;
        top->next = node;
        node->obj = obj;
        size++;
    }
    /**
     * Read the element from the top of list.
     * Worst case time complexity is O(1).
     * @return element on a top of list.
     */
    T pop() override{
        return ptr->prev->obj;
    }
    /**
     * Delete element at the top of the list.
     * Worst case time complexity is O(1).
     */
    void peek()override{
        if(!empty()){
            link<T>* top = ptr->prev;
            top->prev->next = ptr;
            ptr->prev = top->prev;
            delete top;
        }
        size--;
    }
    /**
     * Length of the list.
     * Worst case time complexity is O(1).
     * @return the length.
     */
    unsigned long long length() override{
        return this->size;
    }
    /**
     * Read the element at position <index>.
     * Worst case time complexity is O(n).
     * @param index the position in the list.
     * @return element at current position.
     */
    T elAt(int index) override{
        link<T>* current = ptr;
        for(int i = 0; i < index+1; ++i){
            current=current->next;
        }
        return current->obj;
    }

private:
    unsigned long long size;
    link<T>* ptr = new link<T>;
};

/**
 * Abstract class of the Linked Stack.
 * @tparam T
 */
template<typename T>
class LinkedStack{
    virtual T pop() = 0;
    virtual void peek() = 0;
    virtual void push(T) = 0;
    virtual bool empty() = 0;
};
/**
 * Implementation of the Linked Stack.
 * @tparam T data type that is to be used in stack.
 */
template<typename T>
class Stack: public LinkedStack<T>{
public:
    /**
     * Reading the element at the top of stack.
     * Worst case time complexity is O(1).
     * @return the element at the top.
     */
    T pop() override{
        return newList.pop();
    }
    /**
     * Deleting element from the top.
     * Worst case time complexity is O(1).
     */
    void peek() override{
        newList.peek();
    }
    /**
     * Pushing an element to the stack.
     * Worst case time complexity is O(1).
     * @param obj element to be pushed.
     */
    void push(T obj) override{
        newList.push_back(obj);
    }
    /**
     * Checking if the stack is empty.
     * Worst case time complexity is O(1).
     * @return true if empty, false otherwise.
     */
    bool empty() override{
        return newList.empty();
    }
private:
    List<T> newList;
};
/**
 * Structure of two elements, not obliged to the same type.
 * @tparam T type of the first element.
 * @tparam K type of the second element.
 */
template<typename T, typename K>
struct pairOf{
    T obj1;
    K obj2;
};
/**
 * Function to make pair of two objects.
 * @tparam T type of the first element.
 * @tparam K type of the second element.
 * @param one first object.
 * @param two second object.
 * @return pair of given objects.
 */
template<typename T, typename K>
pairOf<T,K> makePair(T one, K two){
    pairOf<T,K> pair;
    pair.obj1 = one;
    pair.obj2 = two;
    return pair;
}
int main(){
    int numberOfDeliminators, numberOfLines;
    cin >> numberOfDeliminators >> numberOfLines;
    List<pairOf<string,string>> deliminators;
    Stack<string> deliminatorsStack;
    //pushing pairs of deliminators to the list of deliminators
    for(int i = 0; i < numberOfDeliminators; ++i){
        string dopen, dclose;
        cin >> dopen >> dclose;
        deliminators.push_back(makePair(dopen, dclose));
    }
    string line;
    getline(cin, line);
    //column counter to print in error messages
    int column = 0;
    for(int i = 0; i < numberOfLines; ++i){
        string temp;
        getline(cin, line);
        line += " ";
        column = 0;
        //running through the string line char by char
        for(auto l: line){
            if(l != ' '){
                column++;
                temp+=l;
            } else {
                //bool variables to detect if string temp is deliminator and
                //if it is the opening deliminator respectively.
                bool isDel = false;
                bool obj1 = false;
                //opposite token to the string temp.
                string opToken;
                //checking the temp to be deliminator.
                for(int e = 0; e < deliminators.length(); ++e){
                    if(temp == deliminators.elAt(e).obj1){
                        isDel = true;
                        obj1 = true;
                        opToken = deliminators.elAt(e).obj2;
                        break;
                    } else if(temp == deliminators.elAt(e).obj2){
                        isDel = true;
                        obj1 = false;
                        opToken = deliminators.elAt(e).obj1;
                        break;
                    }
                }
                if(isDel){
                    //if temp is opening deliminator then push it to stack.
                    if(obj1){
                        deliminatorsStack.push(temp);
                    } else {
                        //if temp is closing deliminator two errors may occur.
                        if(deliminatorsStack.empty()){
                            cout << "Error in line "<<i+1<<", column "<<column-temp.length()+1<<": unexpected closing token "<<temp<<".";
                            return 0;
                        } else if(deliminatorsStack.pop() != opToken){
                            string opTokenPrev;
                            string popped = deliminatorsStack.pop();
                            for(int e = 0; e < deliminators.length(); ++e){
                                if(popped == deliminators.elAt(e).obj1){
                                    opTokenPrev = deliminators.elAt(e).obj2;
                                    break;
                                }
                            }
                            cout << "Error in line "<<i+1<<", column "<<column-temp.length()+1<<": expected "<<opTokenPrev<<" but got "<<temp<<".";
                            return 0;
                        } else { //if no of two errors occurred then deleting the top element in stack.
                            deliminatorsStack.peek();
                        }
                    }
                }
                temp = "";
                column++;
            }
        }
        column+=1;
    }
    if(deliminatorsStack.empty()){
        cout << "The input is properly balanced.";
    } else { //if stack is not empty outputting the error.
        string temp = deliminatorsStack.pop();
        string opToken;
        for(int e = 0; e < deliminators.length(); ++e){
            if(temp == deliminators.elAt(e).obj1){
                opToken = deliminators.elAt(e).obj2;
                break;
            }
        }
        cout << "Error in line "<< numberOfLines << ", column "<< column <<": expected "<< opToken << " but got end of input.";
    }

    return 0;
}
