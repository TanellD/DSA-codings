//Davydov Danil
//the code was tested on samples from:
#include<iostream>
#include<vector>

using namespace std;

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

/**
 * Abstract class for HashMap.
 * @tparam K key data type.
 * @tparam V value data type.
 */
template<typename K, typename V>
class HashMap{
public:
    virtual void put(K, V) = 0;
    virtual V get(K) = 0;
    virtual int search(K) = 0;
    virtual vector<pairOf<K,V>> getNodes() = 0;
protected:
    virtual void resize() = 0;
    virtual int hashFunc(K) = 0;
};

/**
 * Implementation of a HashMap.
 * @tparam K key data type.
 * @tparam V value data type.
 */
template<typename K, typename V>
class Map: public HashMap<K, V>{
public:
    Map(){
        nodes = 0;
        slots = 2;
        mapVector.resize(2);
    }
    /**
     * The function puts key-value pair into Map.
     * Average time complexity is O(1/(1-loadfactor)).
     * @param key key.
     * @param value value.
     */
    void put(K key, V value) override{
        int index = hashFunc(key);
        /**
         * Searching for the vacant place which is empty or has the same key. Linear probing in open addressing.
         */
        while(mapVector[index].obj1!= "" && (mapVector[index]).obj1!=key){
            index++;
            index %= slots;
        };
        if(mapVector[index].obj1 == ""){
            if((double)(nodes+1)/slots > loadFactor){
                resize();
                //recalculate index after the resizing
                index = hashFunc(key);
                while(mapVector[index].obj1!= ""){
                    index++;
                    index %= slots;
                };
            }
            nodes++;
        }

        mapVector[index].obj1 = key;
        mapVector[index].obj2 = value;
    }
    /**
     * Function that searches for the presence of the key in a Map.
     * Worst time complexity is O(n).
     * @param key key.
     * @return index index in hash table or -1 if not present.
     */
    int search(K key) override{
        int index = hashFunc(key);
        while(mapVector[index].obj1 != "" && (mapVector[index]).obj1!=key){
            index++;
            index %= slots;
        };
        if(mapVector[index].obj1 == ""){
            return -1;
        } else{
            return index;
        }
    }
    /**
     * Gets the value for a certain key in a Map.
     * Average time complexity is O(1/(1-loadfactor)).
     * @param key key.
     * @return value.
     */
    V get(K key) override{
        int index = search(key);
        return mapVector[index].obj2;
    }
    /**
     * Gets all entries in Map.
     * Worst time complexity is O(n).
     * @return vector of entries.
     */
    vector<pairOf<K, V>> getNodes() override{
        vector<pairOf<K, V>> nodesVect;
        for(auto i: mapVector){
            if(i.obj1 != ""){
                nodesVect.push_back(i);
            }
        }
        return nodesVect;
    }
    /**
     * Overloaded operator =.
     * @param newMap Map that to be copied.
     * @return reference of a current Map.
     */
    Map<K, V>& operator= (Map<K, V> newMap){
        this->mapVector = newMap.mapVector;
        this->slots = newMap.slots;
        this->nodes = newMap.nodes;
        return *this;
    }

protected:
    hash<string> hashCode;
    double const loadFactor = 0.75;
    int hashFunc(K key) override{
        return hashCode(key)%slots;
    }
    vector<pairOf<K, V>> mapVector;
    int slots;
    int nodes;
    //resize of a Map if actual load factor is greater or equal than needed load factor.
    void resize() override{
        vector<pairOf<K, V>> vect = getNodes();
        mapVector.clear();
        mapVector.resize(2*slots);
        slots *= 2;
        nodes = 0;
        for(auto i: vect){
            put(i.obj1, i.obj2);
        }
    }

};

/**
 * Method that separates the string by spaces.
 * @param line that is to separate.
 * @return vector of substrings.
 */
vector<string> separate(const string& line){
    vector<string> separated;
    string temp;
    for(auto i: line){
        if(i != ' ' && i!='$'){
            temp+=i;
        } else if(i==' '){
            separated.push_back(temp);
            temp = "";
        }
    }
    return separated;
}
int main(){
    //Map that contains key-value pair, where key is string and value is another Map of string and double.
    Map<string, Map<string, double>> datesMap;
    int numberOfLines;
    cin >> numberOfLines;
    string line;
    getline(cin, line);
    for(int i = 0; i < numberOfLines; ++i){
        getline(cin, line);
        //dividing the line to substrings
        vector<string> substring = separate(line);
        string date = substring[0];
        string customer = substring[2];
        double cost = stod(substring[3]);
        Map<string, double> tMap;
        //check if such date presents in Map.
        if(datesMap.search(date) != -1){
            tMap = datesMap.get(date);
            double value = cost;
            //check if such customer id presents in tMap.
            if(tMap.search(customer)!=-1){
                value += tMap.get(customer);
                tMap.put(customer, value);
            } else {
                tMap.put(customer, value);
            }
            datesMap.put(date, tMap);
        } else {
            tMap.put(customer, cost);
            datesMap.put(date, tMap);
        }

    }
    //get all entries in Map.
    vector<pairOf<string, Map<string, double>>> allPurchases = datesMap.getNodes();
    for(auto i: allPurchases){
        vector<pairOf<string, double>> customers = i.obj2.getNodes();
        double sum = 0;
        for(const auto& a: customers){
            sum+=a.obj2;
        }
        cout << i.obj1 << " " << "$" << sum << " " << customers.size()<<endl;
    }

    return 0;
}
