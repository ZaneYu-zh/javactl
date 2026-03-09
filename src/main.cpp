#include <iostream>
#include <string>
#include <curl/curl.h>

// 回调函数：将接收到的数据追加到字符串中
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // 设置目标 URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
        // 设置回调函数，接收响应数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        // 跟随重定向
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // 设置超时（可选）
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        // 执行请求
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Request successful! Received " << response.size() << " bytes.\n";
            std::cout << "--- Response content (first 500 chars) ---\n";
            std::cout << response.substr(0, 500) << std::endl;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize curl." << std::endl;
        return 1;
    }

    curl_global_cleanup();
    return 0;
}