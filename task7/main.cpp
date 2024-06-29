#include <string>
#include <iostream>
#include <vector>
#include <ios>
#include <chrono>
#include <fstream>
#include <sstream>
#include <memory>
#include <list>

// using namespace std;

class Unit{
private:
    std::vector<std::string> _cmd_bulk;
public:
    explicit Unit(int input_cmd_cnt) {
        _cmd_bulk.reserve(input_cmd_cnt);
    }

    std::vector<std::string>& getData(){
        return _cmd_bulk;
    }
    void add(std::string cmd)
    {
        _cmd_bulk.push_back(cmd);
    }

    void clear()
    {
        _cmd_bulk.clear();
    }

    size_t size()
    {
        return _cmd_bulk.size();
    }
};

class Output{
private:
    std::ostream& _stream;
public:
    Output(std::ostream& stream_):_stream(stream_){}

    void out(std::shared_ptr <Unit> cmd_bulk){
        _stream << "bulk: ";
        std::string separator = "";
        for (auto ele : cmd_bulk->getData()){
            _stream << separator << ele;
            separator = ", ";
        }
        _stream << std::endl;
    }
};

class Logger {
public:
    virtual void log(std::shared_ptr <Unit> cmd_bulk) = 0;
    virtual void ts_now() {};
    virtual ~Logger(){};
};


class StateMachine{
public:
        enum class State {START, STATIC, DINAMYC, END_OF_BLOCK};
        enum class Event {NEW_CMD, OPEN_BLOCK, CLOSE_BLOCK};
private:
        unsigned _cnt = 0;
        unsigned _cnt_block_symbols = 0;

        State _state = State::START;

    void stateMachine(Event event){
            switch(_state)
            {
                case State::START:
                    // cout << "START" << std::endl;
                    _state = State::STATIC;
                    ++_cnt;
                    break;
                case State::STATIC:
                    // cout << "STATIC" << std::endl;
                    if(event == Event::OPEN_BLOCK){
                        _state = State::END_OF_BLOCK;
                        ++_cnt_block_symbols;
                        _cnt = 0;
                        break;
                    }
                    else if(event == Event::NEW_CMD){
                        ++_cnt;
                    }
                break;

                case State::DINAMYC:
                    // cout << "DINAMYC" << std::endl;
                    if(event == Event::CLOSE_BLOCK){
                        --_cnt_block_symbols;
                        if(_cnt_block_symbols == 0) _state = State::END_OF_BLOCK;
                        break;
                    }
                    if(event == Event::OPEN_BLOCK){
                        ++_cnt_block_symbols;
                    }
                    else if(event == Event::NEW_CMD){
                        // ++cnt;
                    }
                break;

                case State::END_OF_BLOCK:
                    _state = State::DINAMYC;
                    if(event == Event::CLOSE_BLOCK){
                        std::cout << "ERROR in State::END_OF_BLOCK: unit was yet finished" << std::endl;
                    }
                    if(event == Event::OPEN_BLOCK){
                        ++_cnt_block_symbols;
                    }
                    else if(event == Event::NEW_CMD){
                        // ++cnt;
                    }
                break;
            }
    }

public:
    void stateMachineHandler(std::string str){
        Event evnt;
        if(str == "{") evnt = Event::OPEN_BLOCK;
        else if(str == "}") evnt = Event::CLOSE_BLOCK;
        else evnt = Event::NEW_CMD;

        stateMachine(evnt);
    }

    bool bulkEOB(){
        return _state == State::END_OF_BLOCK;
    }
    unsigned cmdCnt(){
        return _cnt;
    }
    bool eof(){
        return _state == StateMachine::State::STATIC;
    }

};

class Process{
private:
    std::list <Logger*> _logger;
    std::shared_ptr <StateMachine> _fsm;
public:
    Process(std::shared_ptr <StateMachine> sm):_fsm(sm) {
    }

    void attach(Logger* logg){
        _logger.push_back(logg);
    }

    void detach(Logger* logg){
        _logger.remove(logg);
    }

    void notify(std::shared_ptr<Unit> cmd_bulk = nullptr){
        for(Logger* lp : _logger){
             if(cmd_bulk != nullptr){
                lp->log(cmd_bulk);
            } else {
                lp->ts_now();
            }
        }
    }

    void actionEOB(std::shared_ptr <Unit> static_block){
        notify(static_block);
        static_block->clear();
    }

    void handler(std::string str, std::shared_ptr <Unit> static_block, unsigned input_cmd_cnt){
        if(str != "{" && str != "}"){
            notify();
            static_block->add(str);
        }
        if( _fsm->bulkEOB() || _fsm->cmdCnt() == input_cmd_cnt){
            actionEOB(static_block);
        }
    }

};

class ConsoleLog : public Logger {
public:
    ConsoleLog(std::shared_ptr <Process> pro) : _process(pro){
        this->_process->attach(this);
    }
    void log(std::shared_ptr <Unit> cmd_bulk) override {
        Output output(std::cout);
        output.out(cmd_bulk);
    }
private:
  std::shared_ptr<Process> _process;
};

class FileLog : public Logger {
private:
    std::string _ts;
    std::shared_ptr<Process> _process;
public:
    FileLog(std::shared_ptr <Process> pro) : _process(pro){
        this->_process->attach(this);
    }
    void ts_now() override {
        if (_ts.size() == 0) {
            auto start_time = std::chrono::high_resolution_clock::now();
            auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(start_time.time_since_epoch()).count();

            std::ostringstream oss;
            oss << timestamp;
            _ts = oss.str();
        }
    }

    void log(std::shared_ptr <Unit> cmd_bulk) override {
        std::ofstream log_file (_ts + ".log");
        Output output(log_file);
        output.out(cmd_bulk);
        log_file.close();
    }

};

int main(int argc, char** argv)
{
    if (argc >= 2) {
        unsigned input_cmd_cnt = std::stoi(argv[1]);
        // cout << input_cmd_cnt << std::endl;

        auto st = std::make_shared<StateMachine>();
        auto process = std::make_shared<Process>(st);

        auto static_block = std::make_shared<Unit>(input_cmd_cnt);
        auto console = std::make_shared<ConsoleLog>(process);
        auto logging = std::make_shared<FileLog>(process);

        std::string str;

        while(true){
            if(getline(std::cin, str)){
                st->stateMachineHandler(str);
                process->handler(str, static_block, input_cmd_cnt);

            } else {
                // cout << "es war EOF"<<std::endl;
                if(st->eof()){
                    process->actionEOB(static_block);
                }
                break;
            }
        }

    }
    return 0;
}
