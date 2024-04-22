#pragma once
#include "base.hpp"

//modulShape
class Circle : public IObserver{ // Observer, Subscriber
    public:
        Circle(ISubject* subj) : _subj(subj){
            this->_subj->attach(this);
        }
        void create(){
            // create Circle
        }
        void removeFromList(){
            _subj->detach(this);
        }
    private:
        ISubject* _subj;
};
//modulShape
class Triangle : public IObserver{ // Observer, Subscriber
    public:
        Triangle(ISubject* subj) : _subj(subj){
            this->_subj->attach(this);
        }
        void create(){
            // create Circle
        }
        void removeFromList(){
            _subj->detach(this);
        }
    private:
        ISubject* _subj;
};
