#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <vector>

struct Station {
    int id;
    std::string name;
    int totalEntries{0};
    int totalExits{0};
};

struct BookingRecord {
    int startID;
    int endID;
    int numberOfTickets;
};

class StationBookingSystem {
  public:
    StationBookingSystem(const std::string &stationFileName, const std::string &bookingFileName, const std::string &summaryFileName) {
        openFiles(stationFileName, bookingFileName, summaryFileName);
        loadStations();
        loadBookings();
        writeSummary();
    }

  private:
    std::map<int, Station> stationMap;
    std::vector<BookingRecord> bookingRecords;
    std::vector<Station> stationList;
    std::ifstream stationFile, bookingFile;
    std::ofstream summaryFile;

    void openFiles(const std::string &stationFileName, const std::string &bookingFileName, const std::string &summaryFileName) {
        stationFile.open(stationFileName);
        if (!stationFile) {
            throw std::runtime_error("Error opening station file: " + stationFileName);
        }

        bookingFile.open(bookingFileName);
        if (!bookingFile) {
            throw std::runtime_error("Error opening booking file: " + bookingFileName);
        }

        summaryFile.open(summaryFileName);
        if (!summaryFile) {
            throw std::runtime_error("Error opening summary file: " + summaryFileName);
        }
    }

    void loadStations() {
        std::string line;
        while (std::getline(stationFile, line)) {
            std::istringstream ss(line);
            int id;
            std::string name;
            ss >> id >> name;

            Station station = {id, name, 0, 0};
            stationMap[id] = station;
            stationList.push_back(station);
        }
    }

    void loadBookings() {
        std::string line;
        while (std::getline(bookingFile, line)) {
            std::istringstream ss(line);
            int startID, endID, numberOfTickets;
            ss >> startID >> endID >> numberOfTickets;

            BookingRecord record = {startID, endID, numberOfTickets};
            bookingRecords.push_back(record);

            updateStationEntryExitCounts(startID, endID, numberOfTickets);
        }
    }

    void updateStationEntryExitCounts(int startID, int endID, int numberOfTickets) {
        if (stationMap.find(startID) != stationMap.end()) {
            stationMap[startID].totalEntries += numberOfTickets;
        }

        if (stationMap.find(endID) != stationMap.end()) {
            stationMap[endID].totalExits += numberOfTickets;
        }
    }

    void writeSummary() {
        writeEntrySummary();
        summaryFile << std::endl;

        writeExitSummary();
        summaryFile << std::endl;

        writeSourceDestinationSummary();

        std::cout << "Summary file generation completed successfully!" << std::endl;
    }

    void writeEntrySummary() {
        std::sort(stationList.begin(), stationList.end(), [](const Station &a, const Station &b) {
            return a.name < b.name;
        });

        for (const Station &station : stationList) {
            summaryFile << station.id << " " << station.name << " " << station.totalEntries << std::endl;
        }
    }

    void writeExitSummary() {
        std::sort(stationList.begin(), stationList.end(), [](const Station &a, const Station &b) {
            return a.totalExits < b.totalExits;
        });

        for (const Station &station : stationList) {
            summaryFile << station.id << " " << station.name << " " << station.totalExits << std::endl;
        }
    }

    void writeSourceDestinationSummary() {
        const std::map<std::pair<std::string, std::string>, int> &sourceDestinationMap{computeSourceDestinationPassengerCounts()};

        for (const std::pair<const std::pair<std::string, std::string>, int> &pair : sourceDestinationMap) {
            summaryFile << pair.first.first << " " << pair.first.second << " " << pair.second << std::endl;
        }
    }

    std::map<std::pair<std::string, std::string>, int> computeSourceDestinationPassengerCounts() {
        std::map<std::pair<std::string, std::string>, int> sourceDestinationMap;

        for (const BookingRecord &record : bookingRecords) {
            const std::string &sourceName{stationMap.at(record.startID).name};
            const std::string &destName{stationMap.at(record.endID).name};
            std::pair<std::string, std::string> route = {sourceName, destName};

            sourceDestinationMap[route] += record.numberOfTickets;
        }

        return sourceDestinationMap;
    }
};

int main(void) {
    try {
        StationBookingSystem system("station_name.txt", "booking_record.txt", "summary.txt");
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
