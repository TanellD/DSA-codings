//Davydov Danil
#include<iostream>
#include <list>
#include <vector>
#include <iterator>

using namespace std;



struct pairOfObjects{
public:
 string firstObject;
 int secondObject{};
 bool operator==(const pairOfObjects& a)const {
     return this->firstObject==a.firstObject && this->secondObject==a.secondObject;
 }
 bool operator!=(const pairOfObjects& a) const{
     return !(*this==a);
 }
 pairOfObjects& operator=(const pairOfObjects& a) = default;
};


pairOfObjects makePair(string objOne, int objTwo){
    pairOfObjects myPair;
    myPair.firstObject = objOne;
    myPair.secondObject = objTwo;
    return myPair;
}

int part(vector<pairOfObjects>&, int, int);

class MapInterface{
public:
    virtual void put(string key, int value) = 0;
    virtual int get(string key) = 0;
    virtual void remove(string key) = 0;
    virtual vector<pairOfObjects> entries() = 0;
};


class Map : MapInterface{
public:
    Map()  {
        myVector.resize(14990);
    }
   void put(string key, int value) override{
        int index = hashFunction(key);
        int keyIndex = -1;
        auto it = myVector[index].begin();
        for(int i = 0; i < myVector[index].size(); ++i){
            if(it->firstObject == key){
                keyIndex = i;
                it->secondObject = value;
                break;
            };
            it++;
        }
        if(keyIndex == -1){
            myVector[index].push_back(makePair(key, value));
        }
   }
   int get(string key) override{
       int index = hashFunction(key);
       int keyIndex = -1;
       auto it = myVector[index].begin();
       if(myVector[index].empty()){
           return -1;
       }
       for(int i = 0; i < myVector[index].size(); ++i){
           pairOfObjects pair = *it;
           if(it->firstObject == key){
               return it->secondObject;
               break;
           };

           ++it;
       }
       return -1;
   };

   void remove(string key) override{
       int index = hashFunction(key);
       int value = get(key);
       myVector[index].remove(makePair(key, value));
   };
   vector<pairOfObjects> entries() override{
       vector<pairOfObjects> entries;
       for (int i = 1; i < 31; ++i){
           if(!myVector[i].empty()) {
               for (const auto &it: myVector[i]) {
                   entries.push_back(it);
               }
           }
       }
       return entries;
   }
private:
    vector <list<pairOfObjects>> myVector;
    static unsigned long long hashFunction(const string& key){
        int sum = 0;
        for (auto i: key){
            sum += i;
        }

        return sum%14990;
    }
};



int main() {
    int n;
    int m;
    cin >> n;
    string temp;
    Map myMap;
    vector<string> entries;
    for (int i = 0; i < n; ++i){
        cin >> temp;
        int value = myMap.get(temp);
        if(value == -1){
            myMap.put(temp, 1);
        }
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> temp;
        int value = myMap.get(temp);
        if (value == -1) {
            entries.push_back(temp);
            myMap.put(temp, 0);
        }
    }
    cout << entries.size() << endl;
    for(auto i: entries){
        cout << i << endl;
    }

    return 0;
}

