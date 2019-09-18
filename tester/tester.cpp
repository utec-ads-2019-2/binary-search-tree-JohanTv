#include "tester.h"

void Tester::execute() {
    Mocker mocker;

    for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
        unsigned int size = mocker.generateRandomInt(10);
        int* elements = mocker.generateRandomArray<int>(size);
        testBSFTree<int>(mocker, vector<int>(elements, elements + size));
    }
}

template <typename T>
void Tester::testBSFTree(Mocker mocker, vector<T> elements) {
    BSTree<T> *test = new BSTree<T>;
    for (int j = 0; j < elements.size(); ++j) {
        test->insert(elements[j]);
        ASSERT(test->find(elements[j]), "There is a problem with the insert or find");
    }

    sortAndPrune(elements);

    ASSERT(elements.size() == test->size(), "There is a problem with the insert or size");

    unsigned int toRemove = mocker.generateRandomInt(1, elements.size());
    for (int j = 0; j < toRemove; ++j) {
        unsigned int index = mocker.generateRandomInt(0, elements.size() - 1);
        T temp = elements.at(index);
        elements.erase(elements.begin() + index);
        test->remove(temp);
        ASSERT(!test->find(temp), "There is a problem with the remove or find");
    }

    ASSERT(elements.size() == test->size(), "There is a problem with the remove or size");

    auto it = test->begin();
    for (int j = 0; j < elements.size() && it != test->end(); ++j) {
        ASSERT(elements.at(j) == *it, "There is a problem with the iterator (++)");
        ++it;
    }

    for (int j = elements.size() - 1; j >= 0; --j) {
        --it;
        ASSERT(elements.at(j) == *it, "There is a problem with the iterator (--)");
    }
}

template <typename T>
void Tester::sortAndPrune(vector<T>& array) {
    sort(array.begin(), array.end());
    auto last = unique(array.begin(), array.end());
    array.erase(last, array.end()); 
}