/* Вам нужно написать функцию CountValues, которая получает на вход блок байтов (через указатель на начало и размер). 
Предполагается, что в этих байтах последовательно записаны какие-то строки с помощью length-value-кодирования. 
Функция должна вернуть количество записанных строк. Если блок байтов неожиданно заканчивается, 
а очередное значение из него не прочитано до конца, то требуется сгенерировать исключение типа RangeError. */

#include <cstddef>  // for size_t
#include <iostream>

class RangeError {
};

size_t CountValues(const char * data, size_t size) {
    size_t amount = 0;
    size_t length = 0;
    int counter = 0;
    while (length != size) {
        ++amount;
        size_t additional = *reinterpret_cast<const size_t*>(data + length);
        if (length + sizeof(size_t) + additional > size) {
            throw RangeError();
        }
        length += (sizeof(size_t) + additional);
    }
    return amount;
}

