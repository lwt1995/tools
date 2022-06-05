#include <iostream>
#include <thread>
#include <future>
using namespace std;

void wirteFile(FILE *f)
{
    for (size_t i =100; i < 500; i++)
    {
        fprintf(f,"func: %s(), line: %d  current time: %s, index: %d, threadId:%d\n",
            __func__, __LINE__, __TIME__, i, this_thread::get_id()); 
    }
}

void syncWirteFile(FILE *f, int index)
{
    
    for (size_t i = 0; i < index; i++)
    {
       std::async(launch::async, [&]() {  
            for (size_t j = i * 20; j < (i + 1) * 100 ; j++)
            {
                fprintf(f,"func: %s(),line: %d, current time: %s, index: %d, threadId:%d\n",
                    __func__, __LINE__, __TIME__,
                    j, this_thread::get_id()); 
            }
       });
    }
}

void readFileContent()
{
    FILE *f = fopen("d://a.txt", "r+");
     char s[1024] = { 0 };   
    while(fgets(s, sizeof(s), f) != nullptr) {
        printf("%s\n",s);
    }
    fclose(f);
}
int main() {
    
    FILE * f = fopen("d://a.txt", "w");
    if (f == nullptr)
    {
       printf("file open error");
       return 0;
    }
    // syncWirteFile(f, 5);
    wirteFile(f); 
    fclose(f);
    readFileContent();
    return 0;
}
