#include "sensor_data.hpp"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>

void fetch_nasa_radar_data() {
    web::http::client::http_client client(U("https://api.nasa.gov/radar/"));

    web::http::uri_builder builder(U("/data"));
    builder.append_query(U("api_key"), U("DEMO_KEY"));  // Substitute with actual API key

    client.request(web::http::methods::GET, builder.to_string())
        .then([](web::http::http_response response) {
            if (response.status_code() == web::http::status_codes::OK) {
                std::cout << "Radar Data: " << response.extract_json().get().serialize() << std::endl;
            }
        }).wait();
}
