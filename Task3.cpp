#include "Task3.h"

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace SaberTask;

struct SerializeNode
{
    int64_t prevIdx = -1;
    int64_t nextIdx = -1;
    int64_t randIdx = -1;

    int64_t dataSize = -1;
};

void List::serialize(std::FILE *file)
{
    if(!file)
        return;

    std::vector<SerializeNode> nodes(count);
    std::unordered_map<intptr_t, size_t> indexMap;
    indexMap[0] = -1;

    // create item address to index association
    auto listPtr = head;
    for(size_t i = 0; i < count; i++, listPtr = listPtr->next)
    {
        auto key = reinterpret_cast<intptr_t>(listPtr);
        indexMap[key] = i;
    }

    // write elements count first
    std::fwrite(&count, sizeof(count), 1 , file);

    // fill nodes with indexes instead of item addresses of source list
    // and write them to a file
    listPtr = head;
    for(size_t i = 0; i < count; i++, listPtr = listPtr->next)
    {
        nodes[i].prevIdx = i - 1;
        nodes[i].nextIdx = i + 1;
        nodes[i].dataSize = listPtr->data.size();

        auto randKey = reinterpret_cast<intptr_t>(listPtr->rand);
        nodes[i].randIdx = indexMap[randKey];

        std::fwrite(&nodes[i],sizeof(SerializeNode), 1, file);
        std::fwrite(listPtr->data.c_str(), listPtr->data.size(), 1, file);
    }
}

void List::deserialize(std::FILE *file)
{
    std::fread(&count, sizeof(count), 1, file);

    auto* nodes = new ListNode[count];
    SerializeNode serializedNode;
    for(int i = 0; i < count; i++)
    {
        std::fread(&serializedNode, sizeof(SerializeNode), 1, file);
        std::vector<char> buffer(serializedNode.dataSize);
        std::fread(buffer.data(), buffer.size(), 1, file);

        nodes[i].prev = i - 1 < 0 ? nullptr : &nodes[i - 1];
        nodes[i].next = i == count - 1 ? nullptr : &nodes[i + 1];
        nodes[i].rand = serializedNode.randIdx == -1 ? nullptr : &nodes[serializedNode.randIdx];
        nodes[i].data = std::string(buffer.data(), buffer.size());
    }

    head = nodes;
    tail = nodes + count - 1;
}

ListNode& List::pushFront(const std::string &data) {
    auto it = new ListNode();
    it->data = data;
    it->prev = nullptr;
    it->next = head;

    if(!head)
    {
        head = it;
        tail = it;
    }
    else
    {
        head->prev = it;
        head = it;
    }

    ++count;

    return *it;
}

ListNode& List::pushBack(const std::string &data)
{
    auto it = new ListNode();
    it->data = data;
    it->prev = tail;
    it->next = nullptr;

    if(!tail)
    {
        tail = it;
        head = it;
    }
    else
    {
        tail->next = it;
        tail = it;
    }

    ++count;

    return *it;
}

ListNode& List::find(const std::string &data) {
    return *std::find_if(this->begin(), this->end(), [&](const ListNode& node)
    {
        return data == node.data;
    });
}

List::iterator List::begin() {
    return { this->head };
}

List::iterator List::end() {
    return {nullptr };
}

List::ListIterator::ListIterator(ListNode *node)
{
    _it = node;
}

List::ListIterator& List::ListIterator::operator++()
{
    _it = _it->next;
    return *this;
}

ListNode& List::ListIterator::operator*() {
    return *_it;
}

List::ListIterator List::ListIterator::operator++(int) {
    auto retval = *this;
    ++(*this);
    return retval;
}

bool List::ListIterator::operator==(const ListIterator& other) {
    return _it == other._it;
}

bool List::ListIterator::operator!=(const List::ListIterator &other) {
    return !(*this == other);
}
