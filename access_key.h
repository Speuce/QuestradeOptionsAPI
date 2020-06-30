//
// Created by Matthew Kwiatkowski on 2020-06-29.
//
#pragma once

#include <string>
#include <cpprest/http_msg.h>

/**
 * Object for storing details of an access key
 */

class access_key{

    private:
        std::string* orgKey; //the original key provided.
        std::string* accessKey; //the most recent access key provided
        std::string* refreshKey; //the refresh key provided.
        std::string* server; //the server url provided.
        long expiryTime; //the time that this

        /**
         * @return the current epoch time (in seconds);
         */
        static long getCurrTimeSecs();

    public:
        /**
         * Construct a new access key
         * @param key the key provided by the questrade interface.
         */
        access_key(std::string* key);

        void setParams(std::string* accesskey, std::string* refreshkey, std::string* serveraddress);

        /**
         * Sets the time left for expiry
         * @param timeleft the time left (in seconds) from NOW.
         */
        void setTimeExpiry(long timeleft);

        /**
         * Get the key provided to the service.
         */
        std::string getOrgKey();

        /**
         * @return the current provided access key, derived from the original/last key
         */
        std::string getAccessKey();

        /**
         * @return the current provided refresh key, derived frm the original/last key.
         */
        std::string getRefreshKey();

        /**
         * Whether or no the current key is expired
         * @return {@code true} if the current key is expired, false otherwise.
         */
        bool isExpired();

        void attemptRefresh();

        void accessReponse(web::http::http_response& response);

};
