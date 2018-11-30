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
        TSN::user_information load_user();
        TSN::user_information edit_user();
        void list_user();
        // shows only our user info
        void show_user();
        void store_sub(TSN::user_information a);
        //check is uuid is already saved. 
        bool check_user(TSN::user_information a);
        // delete everything from file
        void resync();
        
};
   