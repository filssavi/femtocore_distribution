//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <vector>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <thread>
#include <semaphore>

#include "dev_server/rest_handler.hpp"

std::binary_semaphore exit_requested{0};


void wait_for_input(){
    std::cout<< "Press ENTER to exit."<< std::endl;
    std::getchar();
    exit_requested.release();

}


int main(int argc, char **argv) {

    rest_handler handler;


    auto bound_get = [&](auto m){handler.handle_get(m);};
    auto bound_post = [&](auto m){handler.handle_post(m);};
    auto bound_opt = [&](auto m){handler.handle_option(m);};

    web::http::experimental::listener::http_listener listener(U("http://localhost:8080"));
    listener.support(web::http::methods::GET,bound_get);
    listener.support(web::http::methods::POST,bound_post);
    listener.support(web::http::methods::OPTIONS,bound_opt);

    try{
        listener.open()
                .then([&listener](){printf("\nStarting server at: http://localhost:8080\n");})
                .wait();

        std::thread exit_thread(wait_for_input);

        exit_requested.acquire();

        listener.close().wait();
        exit_thread.join();

    }
    catch (const std::exception & e) {
        printf("Error exception:%s\n", e.what());
    }
    return 0;
}

