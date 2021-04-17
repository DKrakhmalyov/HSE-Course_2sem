#include <utility>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>

#ifndef HOMEWORK_2_STATIC_ARRAY_H
#define HOMEWORK_2_STATIC_ARRAY_H

template <typename T, std::size_t sz = 0>
class static_array {

    public:

        class iterator {

            friend class static_array;

            public:
            
                iterator(const iterator &);

                ~iterator();

                iterator &operator=(const iterator &);

                iterator &operator++();

                iterator &operator--();

                T *operator->();

                T &operator*();

                bool operator==(const iterator &);
                
                bool operator!=(const iterator &);

            private:

                iterator(T**, T**, T**);

                T **curr_iter;

                T **begin_iter;

                T **end_iter;
        };

        static_array();

        static_array(std::size_t size);

        ~static_array();

        std::size_t current_size() const;

        std::size_t size() const;

        void clear();

        static_array::iterator emplace(std::size_t pos, T &&obj);

        template<class... Args>
        static_array::iterator emplace(std::size_t pos, Args &&... args);

        void erase(static_array::iterator);

        T &at(std::size_t pos);

        static_array::iterator begin();

        static_array::iterator end();

    private:

        T **array;

        std::size_t elements_count;

        std::size_t total_count;

        void init_array();

        void delete_elements();

        static_array::iterator create_iter(std::size_t pos);

};

#endif //HOMEWORK_2_STATIC_ARRAY_H
