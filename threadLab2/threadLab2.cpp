#include <iostream>
#include "SafeQueue.h"
int main()
{
    SafeQueue<size_t> queue;
    std::thread fillingThread([&]()
        {
        for (unsigned int i = 0; i < 1000; i++)
        {
            queue.push(i);
        }
        });
    std::thread readingThread([&]()
        {
        while (!queue.empty()) {
            std::cout << queue.front() << ' '; 
            queue.pop();
        }
        });
    if (fillingThread.joinable())
        fillingThread.join();

    if (readingThread.joinable())
        readingThread.join();
    std::cout << std::endl;

    return 0;
}

