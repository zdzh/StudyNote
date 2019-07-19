#include<iostream>
#include<string>
#include <unistd.h>
#include<pthread.h>

using namespace std;

void* printmsg(void* arg){
    char* str = static_cast<char*>(arg);
    for(int i = 0; i < 5; ++i  ){
    cout<<str<<endl;
    sleep(1);
    }
    return NULL;
}


int main(){
    pthread_t p1, p2;
    pthread_create(&p1, NULL, printmsg, (void*)"thread1");
    pthread_create(&p2, NULL, printmsg, (void*)"thread2");
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    printmsg((void*)"thread test");
}

