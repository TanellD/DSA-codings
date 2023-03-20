//Davydov Danil
#include<iostream>
#include <list>
#include <vector>
#include <iterator>
#include <cmath>

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
        myVector.resize(31);
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
        return key.length();
    }
};

vector<pairOfObjects> quickSort(vector<pairOfObjects>& myVector, int s, int e){
    if(s < e){
        int q = part(myVector, s, e);
        quickSort(myVector, s, q-1);
        quickSort(myVector, q+1, e);
    }
    return myVector;


}
int part(vector<pairOfObjects>& myVector, int s, int e){
    int x = myVector[e].secondObject ;
    int i = s-1;
    for (int j = s; j < e; ++j){
        if(myVector[j].secondObject > x){
            i++;
            swap(myVector[j], myVector[i]);
        } else if (myVector[j].secondObject == x && myVector[j].firstObject.compare(myVector[e].firstObject) < 0){
            i++;
            swap(myVector[j], myVector[i]);
        }


    }
    swap(myVector[e], myVector[i+1]);


    return i+1;
}


int main() {
    int n;
    cin >> n;
    string temp;
    Map myMap;
    vector<pairOfObjects> entries;
    for (int i = 0; i < n; ++i){
        cin >> temp;
        int value = myMap.get(temp);
        if(value == -1){
            myMap.put(temp, 1);
        } else {
            myMap.put(temp, value+1);
        }
    }
    entries = myMap.entries();
    entries = quickSort(entries, 0, entries.size()-1);
    for(auto o: entries){
        cout << o.firstObject << " " << o.secondObject<<endl;
    }

    return 0;
}

