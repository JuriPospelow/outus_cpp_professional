#include <string>
#include <iostream>
#include <vector>
#include <ios>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

auto time()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(start_time.time_since_epoch()).count();

    std::ostringstream oss;
    oss << timestamp;
    std::string str = oss.str();

    // std::cout << "seconds since epoch: " << time << '\n';
    return str;
}

string ts;

void output(vector<string>& cmd_bulk)
{
    std::ofstream log_file (ts + ".log", std::ofstream::app);
    cout << "bulk: ";
    for (auto ele : cmd_bulk){
        cout << ele <<" ";
        log_file << ele << endl;
    }
    cout << endl;
    log_file.close();
    cmd_bulk.clear();
}


int main(int argc, char** argv)
{
    if (argc >= 2) {
        unsigned input_cmd_cnt = std::stoi(argv[1]);
        cout << input_cmd_cnt << endl;

        string str;
        unsigned cnt = 0;
        vector<string> cmd_bulk;
        cmd_bulk.reserve(input_cmd_cnt);
        vector<string> cmd_bulk_dinamyc;
        cmd_bulk_dinamyc.reserve(10);
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
                    if (ts.size() == 0) ts = time();
                    if(str == "{"){
                        state = DINAMYC;
                        ++cnt_dinamyc;
                        output(cmd_bulk);
                        break;
                    }
                    cmd_bulk.push_back(str);

                    ++cnt;
                    if (cnt == input_cmd_cnt && !dinamyc){
                        cout << endl << "------" << endl;
                        output(cmd_bulk);
                        return 0;
                    }
                break;
                case DINAMYC:
                    // cout << "DINAMYC" << endl;
                    if(str == "}"){
                        --cnt_dinamyc;
                        if( cnt_dinamyc == 0 ) output(cmd_bulk_dinamyc);
                        break;
                    }
                    if(str == "{"){
                        ++cnt_dinamyc;
                    } else {
                        cmd_bulk_dinamyc.push_back(str);
                    }

                break;
            }
            getline(cin, str);
        }
        cout << "es war EOF"<<endl;
        if(cmd_bulk.size() > 0)output(cmd_bulk);
    }
    return 0;
}