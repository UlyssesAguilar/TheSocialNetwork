#include "user_info.h"
#include <vector>
#include <time.h>
#include <string.h>
#include <fstream>
TSN::user_information user_info::setup_user()
{   //this will store the info and add it the private userinfo vector 
    TSN::user_information a;
    char uuid[37];
    //open file
    std::ofstream infile;
    infile.open("save.tsn");
    //seed rand
    srand(time(NULL));
    //create char array with possible values
    static const char ab[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    //create unique uuid
    for(int i =0;i<36;i++)
    {
        uuid[i] = ab[rand() %36];
    }
    uuid[36]= '\0';
    string struuid(uuid);
    std::string first_name;
    std::string last_name;
    int birth;
    int num_inter=0;
    std::vector<std::string> interest;
    //this is to hold the interest 
    std::string temp;
    //since this is first time being created post must equal 0
    int num_post=0;
    std::cout << "please enter your first name" << endl;
    cin >> first_name;
    std::cout << "please enter your last name" << endl;
    cin >> last_name;
    std::cout << "please enter your date of birth in seconds must be > 0" << endl;
    cin >> birth;
    std::cout << "please enter number of interest: " << endl;
    cin.ignore();
    cin >> num_inter;
    cin.ignore();
    //ask for each interest
    for(int i =0;i<num_inter;i++)
    {
        std::cout << "please enter interest " << i+1<<":" <<endl;
        cin>> temp;
        interest.push_back(temp);
    }
    std::cout << "uuid " << uuid<<endl;
    std::cout << "first name:" << first_name << "  last name: " << last_name << "birth date: "<<birth <<endl;
    std::cout << "number of interest:" << num_inter<<endl;
    // copy to file 
    infile << struuid << endl;
    infile << first_name<<endl;
    infile << last_name<<endl;
    infile << birth<<endl;
    infile << num_inter<<endl;
    for(int i =0;i<num_inter;i++)
    {
        infile << interest[i]<<endl;
    }
    infile << num_post <<endl; 
    // copy gathered user info into TSN::
    strncpy (a.uuid,struuid.c_str(),sizeof(a.uuid));
    a.first_name = DDS::string_dup(first_name.c_str());
    a.last_name = DDS::string_dup(last_name.c_str());
    a.date_of_birth = birth; 
    a.interests.length(num_inter);
    for(int i =0;i<num_inter;i++)
    {
        a.interests[i] = DDS::string_dup(interest[i].c_str());
    }
    a.number_of_highest_post = 0;
    user_info_pub.push_back(a);
    infile.close();
    return a;
};
