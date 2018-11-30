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
        
    }
    file.close();
    return 0;
}
