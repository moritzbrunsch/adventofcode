#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>

std::array<int,2> parse(std::string line){
    std::array<int,2> res = {0,0};
    std::stringstream line_stream(line);
    std::string number_str;
    bool first = true;
    while(line_stream >> number_str){
        if(number_str != ""){
            if(first){
                res[0] = std::stoi(number_str);
                first = false;
            }else {
                res[1] = std::stoi(number_str);
            }
        }
    }
    return res;
}


int main (int argc, char **argv) {
    std::cout << argc << " " << argv[0] << std::endl;
    int res = 0;
    std::vector<int> list1 {};
    std::vector<int> list2 {};

    /*
    std::vector<int> list1 {3,4,2,1,3,3};
    std::vector<int> list2 {4,3,5,3,9,3};

    std::string example_line = "30001   10003";
    std::array<int,2> res_2 = parse(example_line);

    std::cout << res_2[0] << " " << res_2[1] << std::endl;
    */

    std::ifstream input;
    std::string line;
    if(argc == 2){
        input.open(argv[1]);
    } else if(argc == 1){
        input.open("./data/day_1.txt");
    } else{
        std::cerr << "Invalid amount of command line arguments. Aborting." << std::endl;
    }

    std::cout << "tried to open file" << std::endl;
    if(input.is_open()){
        std::cout << "opened file" << std::endl;
        while(std::getline(input, line)){
            std::array<int,2> values = parse(line);
            list1.push_back(values[0]);
            list2.push_back(values[1]);
        }
    } else{
        std::cerr << "Failed to open file." << std::endl;
    }
    input.close();

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    // difference
    for(int i = 0; i < list1.size(); i++) {
        int diff = 0;
        if (list1[i] > list2[i]){
            diff = list1[i] - list2[i];
        }else {
            diff = list2[i] - list1[i];
        }
        res += diff;
    }

    std::cout << "Distance: " << res << std::endl;

    // similarity
    int similarity = 0;
    auto list1_iter = list1.begin();
    auto list2_iter = list2.begin();
    auto list2_end = list2.end();
    int current_num = -1;
    int current_num_amount = 0;
    for(int list1_item: list1){
        if(list1_item == current_num){
            similarity += current_num_amount * current_num;
            // std::cout << "already there! " << current_num << " " << similarity << " " << current_num_amount << std::endl;
        } else{
            current_num = list1_item;
            current_num_amount = 0;

            while (list2_iter != list2_end && *list2_iter < current_num){
                list2_iter++;
            }
            // std::cout << "we moved! " << current_num << " " << similarity << std::endl;
            /*if(*list2_iter != current_num) {
                continue;
            }*/

            if(*list2_iter > current_num) {
                continue;
            } else if (list2_iter == list2_end){
                break;
            }

            // count occurences in list 2
            while (*list2_iter == current_num){
                current_num_amount++;
                list2_iter++;
            }

            similarity += current_num_amount * current_num;
            // std::cout << "we moved and found! " << current_num << " " << similarity << " " << current_num_amount << std::endl;
        }
    }
    // delete iterators?

    std::cout << "Similarity: " << similarity << std::endl;

    return 0;
}

