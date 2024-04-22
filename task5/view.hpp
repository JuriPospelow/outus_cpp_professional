#pragma once

#include <list>

#include "base.hpp"

//view
class Button: public ISubject { //Subject, Publisher
    public:
        void attach(IObserver *observer) override {
            _list_observer.push_back(observer);
        }
        void detach(IObserver *observer) override {
            _list_observer.remove(observer);
        }
        void notify() override {
            std::list<IObserver *>::iterator iterator = _list_observer.begin();

            while (iterator != _list_observer.end()) {
            (*iterator)->create();
            ++iterator;
            }
        }
        void click(){
            notify();
        }
        void render() {} // ? реализовать как мост к классу форм

    private:
        std::list<IObserver*> _list_observer;
};
