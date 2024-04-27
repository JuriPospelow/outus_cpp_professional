#pragma once
#include <memory>
//modulFile

using XML = std::string;
/**
 * Адаптер делает интерфейс Адаптируемого класса совместимым с целевым
 * интерфейсом.
 */
class Adapter {
 private:
  std::unique_ptr<XML> document;

 public:
  Adapter(XML *adaptee) : document(adaptee) {}
  void converToJPEG() const {
    // save file as jpeg
  }
};

//modulFile
class JPEG : public IObserver{ // Observer, Subscriber
    public:
        JPEG(ISubject* subj) : _subj(subj){
            this->_subj->attach(this);
        }
        void create(){
            // convert to JPEG реализовать как адаптер
            _adapter->converToJPEG();
        }
        void removeFromList(){
            _subj->detach(this);
        }
    private:
        std::unique_ptr<ISubject> _subj;
        std::unique_ptr<Adapter>_adapter;
};
