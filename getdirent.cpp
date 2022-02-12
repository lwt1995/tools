#include<dirent.h>
#include<errno.h>
#include<vector>
#include<cstring>
#include<iostream>
using namespace std;

//linux扫描文件夹，获得文件夹下的文件名
void scanFiles(vector<string> &filelist, string intputDirectory)
{
   DIR *p_dir;
   const char * str = intputDirectory.c_str();
   
   p_dir = opendir(str);
   if(p_dir == NULL)
   {
      cout << "can't open :" << intputDirectory << endl;
      return;
   }

   struct dirent *p_dirent;

   while (p_dirent = readdir(p_dir))
   {
      string tmpFileName = p_dirent->d_name;
      string path;
      if (tmpFileName == "." || tmpFileName == "..")
      {
         continue;
      }
      else if(p_dirent->d_type == 8)
      {

         filelist.emplace_back(path.assign(intputDirectory).append("/").append(tmpFileName));
      }
      else
      {
         scanFiles(filelist, path.assign(intputDirectory).append("/").append(tmpFileName));
      }
      
   }
   closedir(p_dir);
}

int main(int argc, char * arg[])
{
   vector<string> v;
   cout << argc << endl;
   if (argc == 1)
   {
     scanFiles(v, "/opt");
   }
   else
   {
     scanFiles(v, arg[1]);
   }
   for(const auto &filename : v)
   {
      cout << filename << endl;
   }
   return 0;
}