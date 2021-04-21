//
// Created by Denis on 12.03.2021.
//

#include "static_array.h"

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(T** arr, size_t ind, size_t size) {
    /*
     * Конструирует итератор, указывающий на index
     */
    _arr = arr;
    index = ind;
    _size = size;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator=(const static_array::iterator &oth) {
    /*
     * Присваивание итератору значения другого итератора
     */
    if (this == &oth) {
        return *this;
    }
    index = oth.index;
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator++() {
    /*
     * Инкремент итератора
     * переводит итератор в следующий существующий
     * если такового не существует, итератор становится равным end()
     */
    for (size_t i = index + 1; i < _size; ++i) {
        if (_arr[i] != nullptr) {
            index = i;
            return *this;
        }
    }
//    Дедаем равным end()
    index = _size;
    return *this;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator &static_array<T, sz>::iterator::operator--() {
    /*
     * Декремент итератора
     * переводит итератор в предыдущий существующий
     * если такового не сушествует, никаких гарантий на этот случай
     * не предоставляется
     */
    for (int i = static_cast<int>(index) - 1; i >= 0; --i) {
        if (_arr[i]) {
            index = i;
            return *this;
        }
    }
//    Если предыдущего значения нет, ставим первый несуществующий индекс
    index = -1;
    return *this;
}

template<typename T, size_t sz>
T &static_array<T, sz>::iterator::operator*() const {
    /*
     * Возвращает элемент, на который указывает итератор по ссылке
     */
    return *_arr[index];
}

template<typename T, size_t sz>
T *static_array<T, sz>::iterator::operator->() const {
    /*
     * Возвращает элемент, на который указывает итератор по значению
     */
    return _arr[index];
}

template<typename T, size_t sz>
static_array<T, sz>::iterator::iterator(const static_array::iterator &oth) {
    /*
     * Конструктор копирования
     */
    _arr = oth._arr;
    index = oth.index;
    _size = oth._size;
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator==(const static_array::iterator &oth) {
    /*
     * Проверяет два итератора на равенство
     * сравнение итераторов из разных инстансов static_array
     * либо не производится (не рекомендуется),
     * либо результат сравнения определяется равенством индексов итераторов
     */
    return index == oth.index;
}

template<typename T, size_t sz>
bool static_array<T, sz>::iterator::operator!=(const static_array::iterator &oth) {
    /*
     * Проверяет два итератора на неравенство
     * реализуется как отрицание равенства
     */
    return index != oth.index;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::size() {
    /*
     * Метод для определения максимально допустимого количества элементов
     */
    return _size;
}

template<typename T, size_t sz>
size_t static_array<T, sz>::current_size() {
    /*
     * Метод для определения сохраненного количества
     * элементов. Сохраненным элементом считается не равный nullptr
     */
    return _real_size;
}

template<typename T, size_t sz>
static_array<T, sz>::static_array(size_t n) {
    /*
     * Конструирует static_array размера в точности n
     */
    _size = n;
    _data = new T*[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = 0;
    }
}

template<typename T, size_t sz>
static_array<T, sz>::static_array() {
    /*
     * Конструирует static_array<T, sz> размера в точности n
     */
    _size = sz;
    _data = new T*[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = nullptr;
    }
}

template<typename T, size_t sz>
void static_array<T, sz>::clear() {
    /*
     * Метод удаляет элементы массива, вызывая для них деструкторы
     */
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i]) {
            delete _data[i];
            _data[i] = nullptr;
        }
    }
    _real_size = 0;
}

template<typename T, size_t sz>
void static_array<T, sz>::erase(static_array::iterator it) {
    /*
     * Удаляет элемент, на который указывает итератор it
     */
//    Если элемент существовал, уменьшим число хранимых элементов
    if (_data[it.index] != nullptr) {
        _real_size -= 1;
    }
    if (_data[it.index] != nullptr) {
        delete _data[it.index];
    }
    _data[it.index] = nullptr;
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, T &&obj) {
    /*
     * Помещает obj в static_array на позицию ind
     */
//    Если элемент существовал, чистим память и уменьшаем реальное количество элементов
    if (_data[ind] != nullptr) {
        delete _data[ind];
        _data[ind] = nullptr;
        _real_size -= 1;
    }
//    Увеличиваем реальное количество элементов
    _real_size += 1;
//    Перемещаем объект
    _data[ind] = new T(std::forward<T>(obj));
    return static_array<T, sz>::iterator(_data, ind, _size);
}

template<typename T, size_t sz>
template<class... Args>
typename static_array<T, sz>::iterator static_array<T, sz>::emplace(size_t ind, Args &&... args) {
//  Если элемент существовал, чистим память и уменьшаем реальное количество элементов
    if (_data[ind] != nullptr) {
        delete _data[ind];
        _data[ind] = nullptr;
        _real_size -= 1;
    }
    _real_size += 1;
    _data[ind] = new T(std::forward<Args>(args)...);
//    создадим и вернем итератор, указывающий на элемент с индексом ind
    return static_array<T, sz>::iterator(_data, ind, _size);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::begin() {
    /*
     * Метод получения begin()-итератора
     * возвращает итератор, указывающий на первый элемент static_array
     */
    return static_array<T, sz>::iterator(_data, 0, _size);
}

template<typename T, size_t sz>
typename static_array<T, sz>::iterator static_array<T, sz>::end() {
    /*
     * Метод получения end()-итератора
     * возвращает итератор, указывающий на фиктивный элемент static_array,
     * следующий за последним
     */
    return static_array<T, sz>::iterator(_data, _size, _size);
}

template<typename T, size_t sz>
T &static_array<T, sz>::at(size_t ind) {
    /*
     * Метод индексации, получения элемента static_array
     */
    return *_data[ind];
}

template<typename T, size_t sz>
static_array<T, sz>::~static_array() {
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] != nullptr) {
            delete _data[i];
        }
    }
    delete[] _data;
}
