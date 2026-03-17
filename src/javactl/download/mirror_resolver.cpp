#include "javactl/download/mirror_resolver.hpp"
#include <curl/curl.h>

namespace javactl::download {

    size_t WriteCallback(void* content, const size_t size, size_t nmemb, std::string* s) {
        const size_t newLength = size * nmemb;
        try {
            s -> append(static_cast<char *>(content), newLength);
        } catch (std::bad_alloc& e) {
            return 0;
        }
        return newLength;
    }

    std::string MirrorResolver::execute(const std::string &url) {
        CURL* curl = curl_easy_init();

        std::string html;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        return html;
    }
}
