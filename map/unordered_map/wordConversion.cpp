//单词替换

#include <iostream> 
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;
using std::unordered_map;
using std::istringstream;
using std::vector;

//读取文件并修改
void read(const string &filename1, const string &filename2, vector<string> &newtxt){
    //打开规则文件
    ifstream ifs2(filename2);
    if(!ifs2.good()){
        cerr << "ifstream open" << filename2 << "failed." << endl;
        return;
    }
    //将规则文件的转换关系存入map中
    unordered_map<string,string> conversionMap;
    string line2;
    while(getline(ifs2, line2)){
        istringstream iss(line2);
        string key, value;
        iss >> key >> value;
        conversionMap[key] = value;
    }
    ifs2.close();
    
    //读取目标文件进行替换
    //打开要修改的文件
    ifstream ifs(filename1);
    if(!ifs.good()){
        cerr << "ifstream open" << filename1 << "failed." << endl;
        return;
    }
    
    string line;
    while(getline(ifs, line)){
        istringstream iss(line);
        string word;
        string newline;
        while(iss >> word){
            if(conversionMap.find(word) != conversionMap.end()){
                word = conversionMap[word];
            }
            newline += word + " ";
        }
        newtxt.push_back(newline);
    }
    ifs.close();
}

//输出文件
void store(const string &filename, vector<string> &newtxt){
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "ofstream open" << filename << "failed." << endl;
        return;
    }

    for(auto &elem : newtxt){
        ofs << elem << endl;
    }
}

int main()
{
    vector<string> newtxt; //存储更改后的文件的每一行
    read("file.txt", "map.txt", newtxt);
    store("file_change.txt", newtxt);
    return 0;
}
