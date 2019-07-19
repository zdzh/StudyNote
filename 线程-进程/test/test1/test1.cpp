//条件变量
#include<iostream>
#include<string>
#include <unistd.h>
#include<pthread.h>

using namespace std;

    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;


void* printmsg(void* arg){
    char* str = static_cast<char*>(arg);
    for(int i = 0; i < 5; ++i  ){
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond,&lock);
    cout<<str<<endl;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    }
    return NULL;
}


int main(){

    pthread_t p1, p2;
    pthread_mutex_lock(&lock);
    pthread_create(&p1, NULL, printmsg, (void*)"thread1");
    pthread_create(&p2, NULL, printmsg, (void*)"thread2");
    pthread_mutex_unlock(&lock);
    sleep(1);
    pthread_cond_signal(&cond);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    printmsg((void*)"thread test");
}

