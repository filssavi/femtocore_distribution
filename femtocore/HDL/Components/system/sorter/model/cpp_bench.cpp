#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>

using namespace std;

double average(std::vector<double> const& v){
    if(v.empty()){
        return 0;
    }

    auto const count = static_cast<float>(v.size());
    return std::reduce(v.begin(), v.end()) / count;
}

double std_dev(std::vector<double> const& v){
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(),
                std::bind2nd(std::minus<double>(), mean));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size());
    return stdev;
}

int main()
{

    int n_sort = 222;
    // First create an instance of an engine.
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {0x0000, 0xffff};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };
    std::vector<double> results;

    vector<int> vec(n_sort);
    generate(begin(vec), end(vec), gen);


    for(int i = 0; i < 100e3; i++){
        auto t1 = std::chrono::high_resolution_clock::now();
        std::sort(vec.begin(), vec.end());
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
        double duration = ns.count()/1000.0f;
        results.push_back(duration);
    }

    double avg_sort = average(results);
    double stdev_sort = std_dev(results);

    std::cout << "std::sort on this machine sorted the numbers in: " << avg_sort << " µs." << "with a standard deviation of: " << stdev_sort << std::endl;
   
    results.clear();

    vector<int> vec_2(n_sort);
    generate(begin(vec_2), end(vec_2), gen);

    for(int i = 0; i < 100e3; i++){
        auto t1 = std::chrono::high_resolution_clock::now();
        std::stable_sort(vec_2.begin(), vec_2.end());
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
        double duration = ns.count()/1000.0f;
        results.push_back(duration);
    }
    
    double avg_stable_sort = average(results);
    double stdev_stable_sort = std_dev(results);

    std::cout << "std::stable_sort on this machine sorted the numbers in: " << avg_stable_sort << " µs." << "with a standard deviation of: " << stdev_stable_sort << std::endl;

    std::cout << "-------------------------------------------------------------------------" << std::endl;

    double cpu_freq = 4.183e9; // 4.183 GHz
    double fpga_clock = 200e6; // 100 MHz

    double sort_cycles = cpu_freq*avg_sort*1e-6;
    double stable_sort_cycles = cpu_freq*avg_stable_sort*1e-6;

    std::cout << "std::sort took " << sort_cycles << " cycles to sort " << n_sort << " numbers." << std::endl;
    std::cout << "std::stable_sort took " << stable_sort_cycles << " cycles to sort " << n_sort << " numbers." << std::endl;
    
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    double sort_clk_parity_duration = (sort_cycles/fpga_clock)*1e6;
    double stable_sort_clk_parity_duration = (stable_sort_cycles/fpga_clock)*1e6;

    std::cout << "At clock speed parity std::sort would take " << sort_clk_parity_duration << "µs." << std::endl;
    std::cout << "At clock speed parity std::stable_sort would take " << stable_sort_clk_parity_duration << "µs." << std::endl;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    
}
