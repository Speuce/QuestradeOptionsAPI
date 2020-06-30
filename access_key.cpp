//
// Created by Matthew Kwiatkowski on 2020-06-29.
//
#include <chrono>
#include "access_key.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

/**
 * Namespaces
 */
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;

access_key::access_key(std::string* key){
    orgKey = key;
    accessKey = nullptr;
    expiryTime = 0;
    server = nullptr;
}

long access_key::getCurrTimeSecs() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void access_key::setParams(std::string *accesskey, std::string *refreshkey, std::string *serveraddress) {
    accessKey = accesskey;
    refreshKey = refreshkey;
    server = serveraddress;
}

void access_key::setTimeExpiry(long timeleft) {
    expiryTime = access_key::getCurrTimeSecs() + timeleft;
}

std::string access_key::getOrgKey() {
    return *orgKey;
}

std::string access_key::getAccessKey() {
    return *accessKey;
}

std::string access_key::getRefreshKey() {
    return *refreshKey;
}

bool access_key::isExpired() {
    return getCurrTimeSecs() > expiryTime;
}

void access_key::accessReponse(http_response& response) {
    expiryTime = 0;
    cout<< "got response! " << response.status_code() << " with string: " << response.extract_string().get() << endl;
}

void access_key::attemptRefresh(){
    http_client client(U("https://login.questrade.com/"));
    uri_builder builder(U("oauth2/token"));
    builder.append_query(U("grant_type"), U("refresh_token"));
    builder.append_query(U("refresh_token"), getOrgKey());
    cout << "Builder: " << builder.to_string() << endl;
    client.request(methods::GET, builder.to_string()).then([=](http_response response){
        accessReponse(response);
    }).wait();
}





