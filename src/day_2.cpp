#include<iostream>
#include<fstream>
#include<string>
#include<vector>

int check_validity(std::string report){
    // TODO add logic
    return true;
}

int main(int argc, char **argv){
    std::ifstream input;
    if(argc == 2){
        input.open(argv[1]);
    } else if(argc == 1){
        input.open("./data/day_1.txt");
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

    std::cout << valid_reports << std::endl;

    return 0;
}
