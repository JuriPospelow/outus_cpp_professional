#include <string>
#include <iostream>
#include <vector>
#include <ios>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

struct Unit{
    vector<string> cmd_bulk;

    explicit Unit(int input_cmd_cnt) {
        cmd_bulk.reserve(input_cmd_cnt);
    }

    vector<string> getData(){
        return cmd_bulk;
    }
    void add(string cmd)
    {
        cmd_bulk.push_back(cmd);
    }

    void clear()
    {
        cmd_bulk.clear();
    }

    size_t size()
    {
        return cmd_bulk.size();
    }
};

struct Output{
    std::ostream& m_stream;

    Output(std::ostream& stream_):m_stream(stream_){}

    void out(Unit& cmd_bulk){
        m_stream << "bulk: ";
        string separator = "";
        for (auto ele : cmd_bulk.getData()){
            m_stream << separator << ele;
            separator = ", ";
        }
        m_stream << endl;
    }
};

struct Print{
    void printToConsole(Unit& cmd_bulk){
        Output _output(std::cout);
        _output.out(cmd_bulk);
    }

};

struct Log{
    string ts;

    void ts_now(){
        if (ts.size() == 0) {
            auto start_time = std::chrono::high_resolution_clock::now();
            auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(start_time.time_since_epoch()).count();

            std::ostringstream oss;
            oss << timestamp;
            ts = oss.str();
        }
    }

    void saveToFile(Unit& cmd_bulk){
        std::ofstream log_file (ts + ".log");
        Output _output(log_file);
        _output.out(cmd_bulk);
        log_file.close();
    }

};

struct StateMachine{
        unsigned cnt = 0;

        unsigned cnt_dinamyc = 0;
        enum class State {START, STATIC, DINAMYC, END_OF_BLOCK};
        enum class Event {NEW_CMD, OPEN_BLOCK, CLOSE_BLOCK};

        State state = State::START;

    void state_machine(Event event){
            switch(state)
            {
                case State::START:
                    // cout << "START" << endl;
                    state = State::STATIC;
                    ++cnt;
                    break;
                case State::STATIC:
                    // cout << "STATIC" << endl;
                    if(event == Event::OPEN_BLOCK){
                        state = State::END_OF_BLOCK;
                        ++cnt_dinamyc;
                        cnt = 0;
                        break;
                    }
                    else if(event == Event::NEW_CMD){
                        ++cnt;
                    }
                break;

                case State::DINAMYC:
                    // cout << "DINAMYC" << endl;
                    if(event == Event::CLOSE_BLOCK){
                        --cnt_dinamyc;
                        if(cnt_dinamyc == 0) state = State::END_OF_BLOCK;
                        break;
                    }
                    if(event == Event::OPEN_BLOCK){
                        ++cnt_dinamyc;
                    }
                    else if(event == Event::NEW_CMD){
                        // ++cnt;
                    }
                break;

                case State::END_OF_BLOCK:
                    state = State::DINAMYC;
                    if(event == Event::CLOSE_BLOCK){
                        cout << "ERROR in State::END_OF_BLOCK: unit was yet finished" << endl;
                    }
                    if(event == Event::OPEN_BLOCK){
                        ++cnt_dinamyc;
                    }
                    else if(event == Event::NEW_CMD){
                        // ++cnt;
                    }
                break;
            }
    }

    void state_machine_handler(string str){
        Event evnt;
        if(str == "{") evnt = Event::OPEN_BLOCK;
        else if(str == "}") evnt = Event::CLOSE_BLOCK;
        else evnt = Event::NEW_CMD;

        state_machine(evnt);

    }

    bool BulkEOB(){
        return state == State::END_OF_BLOCK;
    }
};

struct Process{
    Print* console;
    Log* logging;
    StateMachine* fsm;

    Process(Print* con, Log* log, StateMachine* sm):console(con), logging(log), fsm(sm) {}

    void EOBactions(Unit* static_block){
        console->printToConsole(*static_block);
        logging->saveToFile(*static_block);
        static_block->clear();
    }

    void handler(string str, Unit* static_block, unsigned input_cmd_cnt){
        if(str != "{" && str != "}"){
            logging->ts_now();
            static_block->add(str);
        }
        if( fsm->BulkEOB() || fsm->cnt == input_cmd_cnt){
            EOBactions(static_block);
        }
    }

};


int main(int argc, char** argv)
{
    if (argc >= 2) {
        unsigned input_cmd_cnt = std::stoi(argv[1]);
        // cout << input_cmd_cnt << endl;

        StateMachine st;
        Unit static_block(input_cmd_cnt);

        Print console;
        Log logging;
        Process process(&console, &logging, &st);

        string str;

        while(true){
            if(getline(cin, str)){
                st.state_machine_handler(str);
                process.handler(str, &static_block, input_cmd_cnt);

            } else {
                // cout << "es war EOF"<<endl;
                if(st.state == StateMachine::State::STATIC){
                    process.EOBactions(&static_block);
                }
                break;
            }
        }

    }
    return 0;
}
