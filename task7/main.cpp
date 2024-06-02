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
        enum {START,STATIC, DINAMYC};
        unsigned state = START;
        unsigned _block_size;

        StateMachine(unsigned input_cmd_cnt): _block_size(input_cmd_cnt) {};

    void state_machine(string str){
            switch(state)
            {
                case START:
                    // cout << "START" << endl;
                    state = STATIC;
                    ++cnt;
                    break;
                case STATIC:
                    // cout << "STATIC" << endl;
                    if(str == "{"){
                        state = DINAMYC;
                        ++cnt_dinamyc;
                        break;
                    }
                    ++cnt;
                break;
                case DINAMYC:
                    // cout << "DINAMYC" << endl;
                    if(str == "}"){
                        --cnt_dinamyc;
                        break;
                    }
                    if(str == "{"){
                        ++cnt_dinamyc;
                    }
                break;
            }
}

};

int main(int argc, char** argv)
{
    if (argc >= 2) {
        unsigned input_cmd_cnt = std::stoi(argv[1]);
        // cout << input_cmd_cnt << endl;

        StateMachine st(input_cmd_cnt);
        Unit static_block(input_cmd_cnt);
        Unit dinamyc_block(10);

        Print console;
        Log logging;

        string str;

        while(true){
        // while(!cin.fail()){
            if(getline(cin, str)){
                st.state_machine(str);

                if(st.state == StateMachine::STATIC){
                    logging.ts_now();
                    static_block.add(str);
                }
                else if(st.state == StateMachine::DINAMYC && str != "{" && str != "}"){
                    dinamyc_block.add(str);
                }

                if(((st.state == StateMachine::DINAMYC && str == "{" && st.cnt_dinamyc == 1 )&& static_block.size() != 0) || (st.state == StateMachine::STATIC && st.cnt == st._block_size)){
                    console.printToConsole(static_block);
                    logging.saveToFile(static_block);
                    static_block.clear();
                }
                else if(st.state == StateMachine::DINAMYC && str == "}" && st.cnt_dinamyc == 0 ){
                    console.printToConsole(dinamyc_block);
                    logging.saveToFile(dinamyc_block);
                    dinamyc_block.clear();
                }
            } else {
                // cout << "es war EOF"<<endl;
                if(static_block.size() != 0){
                    console.printToConsole(static_block);
                    logging.saveToFile(static_block);
                }
                break;
            }
        }

    }
    return 0;
}