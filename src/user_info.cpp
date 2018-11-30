#include "user_info.h"
#include <vector>
#include <time.h>
#include <string.h>
#include <fstream>
TSN::user_information user_info::setup_user()
{   //this will store the info and add it the userinfo vector 
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
    //this is just testing input
    //std::cout << "uuid " << uuid<<endl;
    //std::cout << "first name:" << first_name << "  last name: " << last_name << "birth date: "<<birth <<endl;
    //std::cout << "number of interest:" << num_inter<<endl;
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
TSN::user_information user_info::load_user()
{   //this will store the info and add it the userinfo vector 
    //std::cout << "loading info" << endl; 
    TSN::user_information a;
    std::ifstream file;
    string temp;
    file.open("save.tsn");
    string struuid;
    std::string first_name;
    std::string last_name;
    int birth;
    int num_inter=0;
    std::vector<std::string> interest;
    int num_post=0;
    //std::cout << "before reading file" << endl;
    file >> struuid;
    //std::cout << "uuid " << struuid<<endl;
    file >> first_name;

    file >> last_name;
    file >> birth;
    //std::cout << "first name:" << first_name << "  last name: " << last_name << "birth date: "<<birth <<endl;
    file >> num_inter;
    //std::cout << "number of interest:" << num_inter<<endl;
    for(int i =0;i<num_inter;i++)
    {
        file >> temp;
        interest.push_back(temp);
        //std::cout << "interest:" << interest[i]<<endl;
    }
    file >> num_post;
    // copy user info into TSN from file
    strncpy (a.uuid,struuid.c_str(),sizeof(a.uuid));
    a.first_name = DDS::string_dup(first_name.c_str());
    a.last_name = DDS::string_dup(last_name.c_str());
    a.date_of_birth = birth; 
    a.interests.length(num_inter);
    for(int i =0;i<num_inter;i++)
    {
        a.interests[i] = DDS::string_dup(interest[i].c_str());
    }
    a.number_of_highest_post = num_post;
    user_info_pub.push_back(a);
    file.close();
    return a;

};
TSN::user_information user_info::edit_user()
{   //this will store the info and add it the userinfo vector 
    //std::cout << "loading info" << endl; 
    TSN::user_information a;
    std::ifstream file;
    string temp;
    file.open("save.tsn");
    //since we have to delete the entire file to edit user 
    //we have to copy our values first
    //but only if the size is greater then 1
    int size;
    size = static_cast<int>(user_info_pub.size());
    size = size + static_cast<int>(user_info_sub.size());
    //create arrays to easily store eatch user 
    string struuid[size];
    std::string first_name[size];
    std::string last_name[size];
    int birth[size];
    int num_inter[size];
    std::vector<std::string> interest[size];
    int num_post[size];
    // save the things that wont change 
    file >> struuid[0];
    file >> num_post[0];

    if(size>1)
    {   //copy all user info into arrays 
        for(int i=0;i<size;i++)
        {
            //std::cout << "before reading file" << endl;
            file >> struuid[i];
            //std::cout << "uuid " << struuid<<endl;
            file >> first_name[i];

            file >> last_name[i];
            file >> birth[i];
            //std::cout << "first name:" << first_name << "  last name: " << last_name << "birth date: "<<birth <<endl;
            file >> num_inter[i];
            //std::cout << "number of interest:" << num_inter<<endl;
            for(int j =0;j<num_inter[i];j++)
            {
                file >> temp;
                interest[j].push_back(temp);
                std::cout << "interest:" << interest[i][j]<<endl;
            }
            file >> num_post[i];
        }
        file.close();
        //once copied we delete the old file an replace with edited 
        //open file truncate
        std::ofstream infile;
        infile.open("save.tsn",ios::trunc);
        //get edited info
        std::string f_name;
        std::string l_name;
        //birth date
        int b;
        int num_i;
        std::vector<std::string> inter;
        //get edit info from user 
        std::cout << "please edit your first name" << endl;
        cin >> f_name;
        std::cout << "please edit your last name" << endl;
        cin >> l_name;
        std::cout << "please edit your date of birth in seconds must be > 0" << endl;
        cin >> b;
        std::cout << "please edit number of interest: " << endl;
        cin.ignore();
        cin >> num_i;
        cin.ignore();
        //ask for each edited interest
        for(int i =0;i<num_i;i++)
        {
            std::cout << "please edit interest " << i+1<<":" <<endl;
            cin>> temp;
            inter.push_back(temp);
        }
        //uuid wont change on edit 
        infile << struuid[0] << endl;
        infile << f_name<<endl;
        infile << l_name<<endl;
        infile << b<<endl;
        infile << num_i<<endl;
        for(int i =0;i<num_i;i++)
        {
            infile << inter[i]<<endl;
        }
        //number of post wont change on edit;
        infile << num_post[0] <<endl; 
        //restore the rest of the information starting at next index 
        for(int i =1;i<size;i++)
        {
            infile << struuid[i] << endl;
            infile << first_name[i]<<endl;
            infile << last_name[i]<<endl;
            infile << birth[i] <<endl;
            infile << num_inter[i] <<endl;
            for(int j =0;j<num_inter[i];j++)
            {
                infile << interest[i][j]<<endl;
            }
            infile << num_post[i] <<endl;
        }
        infile.close();
        // copy edited user info 
        strncpy (a.uuid,struuid[0].c_str(),sizeof(a.uuid));
        a.first_name = DDS::string_dup(f_name.c_str());
        a.last_name = DDS::string_dup(l_name.c_str());
        a.date_of_birth = b; 
        a.interests.length(num_i);
        for(int i =0;i<num_i;i++)
        {
            a.interests[i] = DDS::string_dup(inter[i].c_str());
        }
        a.number_of_highest_post = num_post[0];
        user_info_pub.push_back(a);
    }
    else
    {   file.close();
        //open file truncate
        std::ofstream infile;
        infile.open("save.tsn",ios::trunc);
        //get edited info
        std::string f_name;
        std::string l_name;
        //birth date
        int b;
        int num_i;
        std::vector<std::string> inter;
        //get edit info from user 
        std::cout << "please edit your first name" << endl;
        cin >> f_name;
        std::cout << "please edit your last name" << endl;
        cin >> l_name;
        std::cout << "please edit your date of birth in seconds must be > 0" << endl;
        cin >> b;
        std::cout << "please edit number of interest: " << endl;
        cin.ignore();
        cin >> num_i;
        cin.ignore();
        //ask for each edited interest
        for(int i =0;i<num_i;i++)
        {
            std::cout << "please edit interest " << i+1<<":" <<endl;
            cin>> temp;
            inter.push_back(temp);
        }
        //uuid wont change on edit 
        infile << struuid[0] << endl;
        infile << f_name<<endl;
        infile << l_name<<endl;
        infile << b<<endl;
        infile << num_i<<endl;
        for(int i =0;i<num_i;i++)
        {
            infile << inter[i]<<endl;
        }
        //number of post wont change on edit;
        infile << num_post[0] <<endl;
        // copy edited user info 
        strncpy (a.uuid,struuid[0].c_str(),sizeof(a.uuid));
        a.first_name = DDS::string_dup(f_name.c_str());
        a.last_name = DDS::string_dup(l_name.c_str());
        a.date_of_birth = b; 
        a.interests.length(num_i);
        for(int i =0;i<num_i;i++)
        {
            a.interests[i] = DDS::string_dup(inter[i].c_str());
        }
        a.number_of_highest_post = num_post[0];
        user_info_pub.push_back(a);




        infile.close();
    }
    
    
    return a;
};
void user_info::show_user()
{   //open file 
    std::ifstream file;
    file.open("save.tsn");
    string struuid;
    std::string first_name;
    std::string last_name;
    int birth;
    int num_inter=0;
    std::vector<std::string> interest;
    int num_post=0;
    std::string temp;
    //std::cout << "before reading file" << endl;
    file >> struuid;
    
    file >> first_name;

    file >> last_name;
    file >> birth;
    
    file >> num_inter;
    //std::cout << "number of interest:" << num_inter<<endl;
    for(int i =0;i<num_inter;i++)
    {
        file >> temp;
        interest.push_back(temp);
    }
    file >> num_post;
    std::cout << "uuid " << struuid << endl;
    std::cout << "first name: " << first_name << endl;
    std::cout << "last name: " << last_name << endl;
    std::cout << "birth date: "<< birth << endl;
    std::cout << "number of interest: " << num_inter << endl;
    for(int i =0;i<num_inter;i++)
    {
        std::cout << "interest " << i+1 << " : " << interest[i] << endl;
    }
    std::cout << "number of highest post: " << num_post << endl;
    file.close();
};
void user_info::store_sub(TSN::user_information a)
{   //cout << "in store_sub function"<<endl;
        if(check_user(a))
        {
        //open file
        std::ofstream infile;
        infile.open("save.tsn",ios::app);
        // copy to file 
        infile << a.uuid << endl;
        infile << a.first_name << endl;
        infile << a.last_name << endl;
        infile << a.date_of_birth << endl;
        infile << a.interests.length() << endl;
        for(int i =0;(unsigned)i<a.interests.length();i++)
        {
            infile << a.interests[i] << endl;
        }
        infile << a.number_of_highest_post << endl;
        infile.close();
        user_info_sub.push_back(a);
        }
};
void user_info::list_user()
{   int size;
    size = static_cast<int>(user_info_sub.size());
    std::cout << "Received : user_information" << std::endl;
    std::cout << "               " << user_info_pub[0].uuid << " "
                                << user_info_pub[0].first_name << " "
                                << user_info_pub[0].last_name  << " "
                                << " date of birth " 
                                << user_info_pub[0].date_of_birth << std::endl;
    std::cout << "               " 
                                << "number of posts " 
                                << user_info_pub[0].number_of_highest_post << std::endl;
    std::cout << "               ";
    for (unsigned int i=0;i<user_info_pub[0].interests.length ();i++)
    {
        std::cout << "(" << user_info_pub[0].interests[i] << ") "; 
    }
    std::cout << std::endl;
    //print users found in sub vector
    for(int j =0;j<size;j++)
    {
    std::cout << "Received : user_information" << std::endl;
    std::cout << "               " << user_info_sub[j].uuid << " "
                                << user_info_sub[j].first_name << " "
                                << user_info_sub[j].last_name  << " "
                                << " date of birth " 
                                << user_info_sub[j].date_of_birth << std::endl;
    std::cout << "               " 
                                << "number of posts " 
                                << user_info_sub[j].number_of_highest_post << std::endl;
    std::cout << "               ";
    for (unsigned int i=0;i<user_info_sub[j].interests.length ();i++)
    {
        std::cout << "(" << user_info_sub[j].interests[i] << ") "; 
    }
    std::cout << std::endl;
    }
};
bool user_info::check_user(TSN::user_information a)
{
    int size;
    size = static_cast<int>(user_info_sub.size());
        
    if(a.uuid == user_info_pub[0].uuid)
    {   
        return false;
    }
    if(size>0)
    {
        for(int i = 0;i<size;i++)
        {
            if(a.uuid == user_info_sub[i].uuid)
            {
                return false;
            }
        }
    }
    return true;

};
void user_info::resync()
{
    std::ofstream infile;
    infile.open("save.tsn",ios::trunc);
    infile.close();
    user_info_sub.clear();
    user_info_pub.clear();
}
