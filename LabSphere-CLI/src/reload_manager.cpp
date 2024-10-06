#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <thread>

// Function to monitor file changes and trigger recompilation
void monitor_directory(const std::string& directory_path, boost::asio::io_service& io_service) {
    boost::filesystem::path path(directory_path);
    std::map<std::string, std::time_t> file_map;

    // Initialize the map with the current file modification times
    for (const auto& entry : boost::filesystem::recursive_directory_iterator(path)) {
        if (boost::filesystem::is_regular_file(entry.path())) {
            file_map[entry.path().string()] = boost::filesystem::last_write_time(entry.path());
        }
    }

    // Monitor file changes every 2 seconds
    boost::asio::steady_timer timer(io_service, std::chrono::seconds(2));

    timer.async_wait([&, directory_path](const boost::system::error_code& /*e*/) {
        for (const auto& entry : boost::filesystem::recursive_directory_iterator(path)) {
            if (boost::filesystem::is_regular_file(entry.path())) {
                std::string filepath = entry.path().string();
                std::time_t new_mod_time = boost::filesystem::last_write_time(entry.path());

                // Check if the file has been modified
                if (file_map[filepath] != new_mod_time) {
                    std::cout << "\nFile modified: " << filepath << "\nTriggering rebuild...\n";

                    // Trigger rebuild
                    system("make");  // Use make, or change to appropriate build command
                    std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for build

                    // Restart CLI after recompilation
                    system("bin/LabSphereCLI.exe &");

                    // Update the last modification time
                    file_map[filepath] = new_mod_time;

                    // Optionally, create a git commit
                    system(("git add " + filepath).c_str());
                    system("git commit -m 'Auto-update on file change'");
                }
            }
        }

        // Set the timer again for continuous monitoring
        timer.expires_from_now(std::chrono::seconds(2));
        timer.async_wait([&](const boost::system::error_code& /*e*/) {
            monitor_directory(directory_path, io_service);
        });
    });
}

int main() {
    boost::asio::io_service io_service;
    std::string src_directory = "../src";
    std::string include_directory = "../include";

    std::cout << "Monitoring directories for changes...\n";

    // Start monitoring both src and include directories
    monitor_directory(src_directory, io_service);
    monitor_directory(include_directory, io_service);

    io_service.run();

    return 0;
}
