#ifndef SABERTASK_TASK3_H
#define SABERTASK_TASK3_H

#include <string>

namespace SaberTask
{
    struct ListNode {
        ListNode *prev = nullptr;
        ListNode *next = nullptr;
        ListNode *rand = nullptr;
        std::string data;
    };

    class List {
    public:
        class ListIterator
        {
        public:
            ListIterator(ListNode* node);
            ListIterator& operator ++();
            ListIterator operator++(int);
            ListNode& operator*();
            bool operator==(const ListIterator& other);
            bool operator!=(const ListIterator& other);

        private:
            ListNode* _it;
        };

        using iterator= ListIterator;


        ListNode& pushFront(const std::string& data);
        ListNode& pushBack(const std::string& data);
        ListNode& find(const std::string& data);

        iterator begin();
        iterator end();

        void serialize(std::FILE *file);
        void deserialize(std::FILE *file);

    private:
        ListNode *head = nullptr;
        ListNode *tail = nullptr;
        int count = 0;
    };
}

#endif //SABERTASK_TASK3_H