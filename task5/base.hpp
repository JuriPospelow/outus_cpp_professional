#pragma once

//base
class IObserver{ // base Observer, Subscreiber
    public:
        virtual ~IObserver(){}
        virtual void create() = 0;
};

//base
class ISubject { //base Subject, Publisher
 public:
  virtual ~ISubject(){}
  virtual void attach(IObserver *observer) = 0;
  virtual void detach(IObserver *observer) = 0;
  virtual void notify() = 0;
};
