//
// Created by Matthew Kwiatkowski on 2020-06-29.
//
#include <chrono>
#include "access_key.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#define access_token_field "access_token"
#define access_token_type "Bearer"
#define access_token_type_field "token_type"
#define expires_in_field "expires_in"
#define refresh_token_field "refresh_token"
#define api_server_field "api_server"

//static const char * = U("token_type");
//static const char *access_token_type = U();
//static const char *expires_in_field = U();
//static const char *refresh_token_field = U("refresh_token");
//static const char *api_server_field = U("api_server");

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

void access_key::setParams(std::string* accesskey, std::string* refreshkey, std::string* serveraddress) {
    accessKey = accesskey;
    refreshKey = refreshkey;
    server = serveraddress;
}

void access_key::setTimeExpiry(long timeleft) {
    expiryTime = access_key::getCurrTimeSecs() + timeleft;
}

std::string* access_key::getOrgKey() {
    return orgKey;
}

std::string* access_key::getAccessKey() {
    return accessKey;
}

std::string* access_key::getServerAddress() {
    return server;
}

std::string* access_key::getRefreshKey() {
    return refreshKey;
}

bool access_key::isExpired() {
    return getCurrTimeSecs() > expiryTime;
}

void access_key::readJson(json::value val){
    auto access_token = new string(val.at(U(access_token_field)).as_string());
    auto refresh_token = new string(val.at(U(refresh_token_field)).as_string());
    auto api_serer = new string(val.at(U(api_server_field)).as_string());
    setParams(access_token, refresh_token, api_serer);
}

void access_key::attemptRefresh(){
    http_client client(U("https://login.questrade.com/"));
    uri_builder builder(U("oauth2/token"));
    builder.append_query(U("grant_type"), refresh_token_field);
    builder.append_query(refresh_token_field, *getOrgKey());

    cout << "Builder: " << builder.to_string() << endl;

    client.request(methods::GET, builder.to_string()).then([this](http_response response){
        if(response.status_code() == status_codes::OK){
            response.headers().set_content_type(U("application/json"));
            cout << "connected to questrade! " << endl;
            readJson(response.extract_json().get());
        }else{
            cout << "error!: got response: " << response.status_code() << endl;
        }
    })
    .wait();
}

void access_key::printOut() {
    cout << "access token: " << *getAccessKey() << endl
    << "api server: " << *getServerAddress() << endl
    << "refresh key: " << *getRefreshKey() << endl;
}





