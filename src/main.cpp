#include <iostream>
#include <thread>
#include <fstream>
#include "ConsoleOutput.h"
#include "DataStore.h"
#include "user_info.h"

int main ( int argc, char* argv[] )
{
    
    std::cout << "TheSocialNetwork" << std::endl;
    //humor 
    std::cout << "welcome to the worst social media program ever produced!!" << std::endl;
    //open our save file 
    std::fstream file;
    file.open("save.tsn");
    //create user info class to access functions
    user_info user;
    //create subscriber
    auto UserInfo_sub = dds_io<user_information,
                          user_informationSeq,
                          user_informationTypeSupport_var,
                          user_informationTypeSupport,
                          user_informationDataWriter_var,
                          user_informationDataWriter,
                          user_informationDataReader_var,
                          user_informationDataReader>((char*) "user_information", false , true );
    //create publisher
    auto UserInfo_pub = dds_io<user_information,
                          user_informationSeq,
                          user_informationTypeSupport_var,
                          user_informationTypeSupport,
                          user_informationDataWriter_var,
                          user_informationDataWriter,
                          user_informationDataReader_var,
                          user_informationDataReader>((char*) "user_information", true , false );
    // create responce sub
    auto Response_sub = dds_io<response,
                          responseSeq,
                          responseTypeSupport_var,
                          responseTypeSupport,
                          responseDataWriter_var,
                          responseDataWriter,
                          responseDataReader_var,
                          responseDataReader>((char*) "response", false,true );
    // create responce pub
    auto Response_pub = dds_io<response,
                          responseSeq,
                          responseTypeSupport_var,
                          responseTypeSupport,
                          responseDataWriter_var,
                          responseDataWriter,
                          responseDataReader_var,
                          responseDataReader>((char*) "response", true,false);
    //create request sub 
    auto Request_sub = dds_io<request,
                          requestSeq,
                          requestTypeSupport_var,
                          requestTypeSupport,
                          requestDataWriter_var,
                          requestDataWriter,
                          requestDataReader_var,
                          requestDataReader>((char*) "request",false,true);
    //create request pub 
    auto Request_pub = dds_io<request,
                          requestSeq,
                          requestTypeSupport_var,
                          requestTypeSupport,
                          requestDataWriter_var,
                          requestDataWriter,
                          requestDataReader_var,
                          requestDataReader>((char*) "request",true,false);
    
    
    
    
    
    //we must check and see if the file has data 
    if(file.peek()== std::fstream::traits_type::eof())
    {
        //in if statement means the file is empty
        //we have to initialize first user. 
        UserInfo_pub.publish(user.setup_user());
    }
    else
    {
        UserInfo_pub.publish(user.load_user());
    }
    int menu=-1;
    while(menu!=0)
    {
        ///// adding menu
	std::cout << "=============================\n" 
             << "Welcome to THE SOCIAL NETWORK\n"
             << "=============================\n"
             << "(1) List Users\n"
             << "(2) Show User\n"
             << "(3) Edit\n"
             << "(4) Resync\n"
             << "(5) Add Posting\n"
             << "(6) Statistics\n"
             << "(0) Exit\n"
			 << std::endl;
			std::cin >>menu;

		switch(menu)
        {
            //This command will print out all of the users
            case 1:
            cout << "This will print out all the users" << endl;
				
            break;

            //This command will show us any users information
            case 2:
            cout << "This will show any users information" << endl;
            break; 

            case 3: 
            UserInfo_pub.publish(user.edit_user());
            cout << "This will allow a user to edit or enter in their information" << endl;
            break;

            case 4:
            cout << "This is a system test command where all the saved data is forgotten and sending of data is reset" << endl;
            break;

            case 5:
            cout << "Allow the user to add a new post" << endl;
            break;

            case 6:
            cout << "Prints how many other nodes are known and how much of the available content is in this node" << endl;
            break;

        }
    }
    file.close();
    return 0;
}
