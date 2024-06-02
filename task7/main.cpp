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

    void printToConsole(Unit& cmd_bulk){
        cout << "bulk: ";
        for (auto ele : cmd_bulk.getData()){
            cout << ele <<" ";
        }
        cout << endl;
    }

    void saveToFile(Unit& cmd_bulk){
        std::ofstream log_file (ts + ".log", std::ofstream::app);
        for (auto ele : cmd_bulk.getData()){
            log_file << ele << endl;
        }
        log_file.close();
    }

};

int main(int argc, char** argv)
{
    if (argc >= 2) {
        unsigned input_cmd_cnt = std::stoi(argv[1]);
        cout << input_cmd_cnt << endl;


        Unit static_block(input_cmd_cnt);
        Unit dinamyc_block(10);

        Output action;

        string str;
        unsigned cnt = 0;

        bool dinamyc = false;
        unsigned cnt_dinamyc = 0;
        enum {START,STATIC, DINAMYC};
        unsigned state = START;
        // unsigned old_state = STATIC;
        while(!cin.fail()){
            switch(state)
            {
                case START:
                    // cout << "START" << endl;
                    state = STATIC;
                    break;
                case STATIC:
                    // cout << "STATIC" << endl;
                    // if (ts.size() == 0) ts = time();
                    action.ts_now();
                    if(str == "{"){
                        state = DINAMYC;
                        ++cnt_dinamyc;
                        // output(static_block);
                        action.printToConsole(static_block);
                        action.saveToFile(static_block);
                        static_block.clear();
                        // output(cmd_bulk);
                        break;
                    }
                    // cmd_bulk.push_back(str);
                    static_block.add(str);

                    ++cnt;
                    if (cnt == input_cmd_cnt && !dinamyc){
                        cout << endl << "------" << endl;
                        action.printToConsole(static_block);
                        action.saveToFile(static_block);
                        static_block.clear();
                        // return 0;
                        break;
                    }
                break;
                case DINAMYC:
                    // cout << "DINAMYC" << endl;
                    if(str == "}"){
                        --cnt_dinamyc;
                        if( cnt_dinamyc == 0 ){
                            action.printToConsole(dinamyc_block);
                            action.saveToFile(dinamyc_block);
                            dinamyc_block.clear();
                        }
                        break;
                    }
                    if(str == "{"){
                        ++cnt_dinamyc;
                    } else {
                        dinamyc_block.add(str);
                    }

                break;
            }
            getline(cin, str);
        }
        cout << "es war EOF"<<endl;
        if(static_block.size() != 0){
            action.printToConsole(static_block);
            action.saveToFile(static_block);
            // static_block.clear();
        }
    }
    return 0;
}