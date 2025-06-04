#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

int abs_dist(int num_1, int num_2){
    return num_1 < num_2 ? num_2 - num_1 : num_1 - num_2;
}


int check_validity(std::string report){
    // parse string
    std::stringstream line_stream(report);
    std::string number_str;
    std::vector<int> report_nums;
    while(line_stream >> number_str){
        report_nums.push_back(std::stoi(number_str));
    }

    //check report safety
    int last_num = -1;
    bool asc_set = false;
    bool asc;
    for(int num: report_nums){
        if(last_num == -1){
            last_num = num;
        } else{
            // ascencion criterion
            if(asc_set == true){
                if((asc && !(last_num < num)) || (!asc && (last_num < num))){
                    std::cout << "asc " << last_num << " " << num << " " << asc << std::endl;
                    return 0;
                }
            } else{
                asc = last_num < num ? true : false;
                asc_set = true;
            }
            // jump distance criterion
            int dist = abs_dist(last_num, num);
            if(!(dist < 4 && dist > 0)){
                std::cout << "dist " << last_num << " " << num << std::endl;
                return 0;
            }
            last_num = num;
        }
    }
    std::cout << "done " << last_num << std::endl;
    return 1;
}

int main(int argc, char **argv){
    std::ifstream input;
    if(argc == 2){
        input.open(argv[1]);
    } else if(argc == 1){
        input.open("./data/day_2.txt");
    } else{
        std::cerr << "Invalid amount of command line arguments. Aborting." << std::endl;
        return 1;
    }
    std::cout << "Tried to open file." << std::endl;


    std::string line;
    int valid_reports = 0;
    if(input.is_open()){
        std::cout << "Opened file." << std::endl;
        while(std::getline(input, line)){
            valid_reports += check_validity(line);
        }
    } else{
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    input.close();

    std::cout << "Valid reports: " << valid_reports << std::endl;

    return 0;
}
