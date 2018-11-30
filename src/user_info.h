#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "dds_io.h"
#include "tsn.h"
class user_info 
{       //couldn't get the auto to work to create a subscriber and publisher, but 
        // created a vector for each to hold to information 
        std::vector<TSN::user_information> user_info_sub; 
        std::vector<TSN::user_information> user_info_pub; 
    public: 
        TSN::user_information setup_user();
        int edit_user();
        int list_user();
        int sub();
        int pub();
        
};
   