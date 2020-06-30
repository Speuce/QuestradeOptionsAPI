
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "access_key.h"

/**
 * Namespaces
 */
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;

void handleIn(http_response response){
    cout << "Got response code: " << response.status_code();
}

void accessGranted(access_key* key){

}



int main() {
   std::string in;
   cout << "Enter the questrade provided key: " << endl;
   cin >> in;
   access_key key(&in);
   key.attemptRefresh();
   while(true){}
}
