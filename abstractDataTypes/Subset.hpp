/*
 * Subset.hpp
 *
 *  Created on: 12.05.2017
 *      Author: frbe5612
 */

#ifndef SUBSET_HPP_
#define SUBSET_HPP_

#include <memory>
#include <vector>
#include <utility>
#include "Bag.hpp"

template<class T, class ...U>
class Subset : virtual public Bag<T> {
private:
  Subset() {
  }
protected:
    std::tuple<std::shared_ptr<Union<U> > ...> tuple_;

public:

    Subset(std::shared_ptr<Union<U> > ...v) :
            Bag<T>() {
        tuple_ = std::tuple<std::shared_ptr<Union<U> > ...>(v...);
    }



    virtual void add(std::shared_ptr<T> el) {
        Bag<T>::add(el);
        call_addEl_with_tuple(el, tuple_, std::index_sequence_for<std::shared_ptr<Union<U> > ...>());

    }

    virtual void erase(std::shared_ptr<T> el) {
        Bag<T>::erase(el);
        call_deleteEl_with_tuple(el, tuple_, std::index_sequence_for<std::shared_ptr<Union<U> > ...>());
    }

    virtual ~Subset() {
        unsigned int i = 0;
        unsigned int size = this->m_bag.size();
        for (i = 0; i < size; i++) {
            erase(this->m_bag[i]);
        }
    }

protected:

    /// ADD ///
    //The helper call add method.
    template<std::size_t ... Is>
    void call_addEl_with_tuple(std::shared_ptr<T> el, const std::tuple<std::shared_ptr<Union<U> > ...> &tuple,
                               std::index_sequence<Is...>) {
        addEll(el, std::get<Is>(tuple)...);
    }

    template<class FirstU, class ...RestU>
    void addEll(std::shared_ptr<T> el, std::shared_ptr<Union<FirstU>> obj, std::shared_ptr<Union<RestU>> ... rest) {
        addEll(el, rest...);
        obj->add(el);
    }

    template<class FirstU, class ...RestU>
    void addEll(std::shared_ptr<T> el, std::shared_ptr<Union<FirstU>> obj) {
        obj->add(el);
    }

    template<std::size_t ... Is>
    void call_deleteEl_with_tuple(std::shared_ptr<T> el, const std::tuple<std::shared_ptr<Union<U> > ...> &tuple,
                                  std::index_sequence<Is...>) {
        deleteEll(el, std::get<Is>(tuple)...);
    }

    template<class FirstU, class ...RestU>
    void deleteEll(std::shared_ptr<T> el, std::shared_ptr<Union<FirstU>> obj, std::shared_ptr<Union<RestU>> ... rest) {
        deleteEll(el, rest...);
        obj->erase(el);
    }

    template<class FirstU, class ...RestU>
    void deleteEll(std::shared_ptr<T> el, std::shared_ptr<Union<FirstU>> obj) {
        obj->erase(el);
    }
};

#endif /* SUBSET_HPP_ */