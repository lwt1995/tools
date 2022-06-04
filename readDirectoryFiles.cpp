//
// Created by LWTLKMD on 2022/1/14.
//
#include <iostream>
#include <string>
#include <vector>
//注意这个头文件
#include <io.h>
#include<direct.h>
#include<algorithm>
//#include "thread_pool.hpp"

using namespace std;

//核心函数
void getFileNames(string path, vector<string> *files);
bool my_create_dir(std::string path);
void fun()
{
    cout << "fun" << endl;
}
int main(){
//   vector<string> fileNames;
//    string path1("D:\\BaiduNetdiskDownload"); 	//自己选择目录测试
//    string path2("D:\\迅雷下载"); 	//自己选择目录测试
//    thread t1(getFileNames, path1, &fileNames);
//    ThreadPool tp(3);
//    tp.start();
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//    tp.appendTask(std::bind(getFileNames, path1, &fileNames));
//    //tp.appendTask(std::bind(getFileNames, path2, &fileNames));
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//
//    tp.stop();
//    for (const auto &ph : fileNames) {
//        std::cout << ph << "\n";
//    }

    using A = function<void()>;

    A a(fun);
    a();
    return 0;

}

//核心代码
void getFileNames(string path, vector<string> *files)
{
    //文件句柄
    //注意：我发现有些文章代码此处是long类型，实测运行中会报错访问异常
    intptr_t hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果是目录,递归查找
            //如果不是,把文件绝对路径存入vector中
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
            {
                files->push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

//创建多级目录
bool my_create_dir(std::string path)
{
    int m = 0, n;
    string str1, str2;

    str1 = path;
    str2 = str1.substr(0, 2);
    str1 = str1.substr(3, str1.size());

    while (m >= 0)
    {

        m = str1.find("\\");

        str2 += '\\' + str1.substr(0, m);
        n = _access(str2.c_str(), 0); //判断该目录是否存在
        if (n == -1)
        {
            if (_mkdir(str2.c_str()) != 0)     //创建目录
            {
                return false;
            }
        }

        str1 = str1.substr(m + 1, str1.size());
    }

    return true;
}

