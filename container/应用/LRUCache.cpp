//LRUCache:
//1.插入时,若容量已满.删除最久未访问的元素
//2.若访问,则将该键值对设为最新
//该版本的get和put是O(n)级别的,需要遍历链表来找key

#include <iostream> 
#include <list>
#include <utility>
#include <unordered_map>
using std::cout;
using std::endl;
using std::list;
using std::pair;
using std::unordered_map;

class LRUCache {
public:
    LRUCache(int capacity)
    : _capacity(capacity)
    {
        
    }
    
    int get(int key) {
        for(auto it = _ls.begin(); it != _ls.end(); ++it){
            if(it->first == key){
                _ls.splice(_ls.begin(), _ls, it); //被访问的元素,要放到最前面
                return it->second;
            }
        }
        return -1;
    }
    
    void put(int key, int value){
        for(auto it = _ls.begin(); it != _ls.end(); ++it){
            if(it->first == key){
                it->second = value; //key已存在,则更新value
                _ls.splice(_ls.begin(), _ls, it); //被更新元素放到链表头
                return;
            }
        }

        //若容量已满,把链表尾,即最久未访问的元素删除
        if(_ls.size() == _capacity){
            _ls.pop_back();
        }
        //插入链表头
        _ls.push_front(pair<int,int>(key,value));
    }

    void display(){
        cout << "display: " << endl;
        for(auto &elem : _ls){
            cout << elem.first << " " << elem.second << endl;
        }
    }

private:
    size_t _capacity;
    list<pair<int,int>> _ls; //维护LRU的顺序
};

int main()
{
    /* Your LRUCache object will be instantiated and called as such: */
    /* LRUCache* obj = new LRUCache(capacity); */
    /* int param_1 = obj->get(key); */
    /* obj->put(key,value); */
    
    LRUCache lrucache(2);
    
    lrucache.put(1,10);
    lrucache.put(2,20);
    lrucache.display();
    
    cout << lrucache.get(1) << endl;
    lrucache.display();
    
    lrucache.put(3,30);
    lrucache.put(3,30);
    
    cout << lrucache.get(2) << endl;
    lrucache.put(4,40);
    lrucache.display();
    cout << lrucache.get(1) << endl;
    cout << lrucache.get(3) << endl;
    cout << lrucache.get(4) << endl;
    
    return 0;
}
