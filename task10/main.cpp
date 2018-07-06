#include<iostream>
#include<algorithm>
#include<vector>

#include <ctime>
//         ...
using namespace std;

int do_work(int val) {
    for(int i = 0; i < 10000; i++) 
        val = (val / 7 * 15 + 3) / 4 * 7 * val /44 * 300;
    return val;
}


int main() {
    cout << 123 << endl;
    vector<unsigned int> run_times;
    for(int i  = 0; i < 100000; ++i) {
        unsigned int start_time =  clock(); // начальное время
        int ret = do_work(i);
        unsigned int end_time = clock(); // конечное время
        unsigned int search_time = end_time - start_time; // искомое время
        run_times.push_back(search_time);
    }
    int max_time =  *(max_element(run_times.begin(), run_times.end()));
    cout  << "MAX TIME: " << max_time << endl;

    int min_time = *(min_element(run_times.begin(), run_times.end()));
    cout  << "MIN TIME: " << min_time << endl;
    

    int s;
    for (auto &rTime : run_times) 
        s += rTime;
    
    int avr_time = s/run_times.size();
    cout << "AVR TIME: " <<  avr_time << endl;
    
    cout << "HIST" << endl;
    const int step =  (max_time - min_time) / 50;
    cout << "STEP: " <<  step << endl;
    vector<int> hist;
    for (int cur = min_time; cur <= max_time; cur = cur + step) {
        int count = 0;
        for (auto &rTime : run_times) 
            if (rTime >= cur && rTime < cur + step) count++;    
        hist.push_back(count);
        cout << "|" << cur << "|" <<  count << "|\t\t\t";
        if(count != 0 ) {
            int percent = (count * 100) /run_times.size() ;
            if (percent == 0) cout << "|";
            for(int j = 0; j < percent; j++) cout << "|";
        }
        cout << endl;
        
    }
    return 0;

   
}
