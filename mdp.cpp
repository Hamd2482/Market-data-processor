#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
using namespace std;

struct Order {
    int id;
    string side;
    int price;
    int qty;
};

class MarketDataProcessor {
public:
    map<int, int, greater<int>> bids;
    map<int, int> asks;

    unordered_map<int, Order> orderMap;

    ofstream logFile;

    MarketDataProcessor() {
        logFile.open("mdp_output.csv");
    }

    void addOrder(int id, string side, int price, int qty) {
        Order o = {id, side, price, qty};
        orderMap[id] = o;

        if (side == "BUY") bids[price] += qty;
        else asks[price] += qty;
    }

    void cancelOrder(int id) {
        if (orderMap.find(id) == orderMap.end()) return;

        Order o = orderMap[id];

        if (o.side == "BUY") {
            bids[o.price] -= o.qty;
            if (bids[o.price] == 0) bids.erase(o.price);
        } else {
            asks[o.price] -= o.qty;
            if (asks[o.price] == 0) asks.erase(o.price);
        }

        orderMap.erase(id);
    }

    void modifyOrder(int id, int newPrice, int newQty) {
        if (orderMap.find(id) == orderMap.end()) return;

        cancelOrder(id);
        addOrder(id, orderMap[id].side, newPrice, newQty);
    }

    void match() {
        while (!bids.empty() && !asks.empty()) {
            auto bestBid = bids.begin();
            auto bestAsk = asks.begin();

            if (bestBid->first >= bestAsk->first) {
                int tradeQty = min(bestBid->second, bestAsk->second);

                bestBid->second -= tradeQty;
                bestAsk->second -= tradeQty;

                if (bestBid->second == 0) bids.erase(bestBid);
                if (bestAsk->second == 0) asks.erase(bestAsk);
            } else break;
        }
    }

    void logMetrics() {
        if (!bids.empty() && !asks.empty()) {
            int bestBid = bids.begin()->first;
            int bestAsk = asks.begin()->first;

            double mid = (bestBid + bestAsk) / 2.0;
            int spread = bestAsk - bestBid;

            cout << "Bid: " << bestBid
                 << " | Ask: " << bestAsk
                 << " | Spread: " << spread
                 << " | Mid: " << mid << endl;

            logFile << bestBid << "," << bestAsk << "," << spread << "," << mid << "\n";
        }
    }

    void process(string action, ifstream &file) {
        if (action == "ADD") {
            int id, price, qty;
            string side;
            file >> id >> side >> price >> qty;
            addOrder(id, side, price, qty);
        }
        else if (action == "CANCEL") {
            int id;
            file >> id;
            cancelOrder(id);
        }
        else if (action == "MODIFY") {
            int id, price, qty;
            file >> id >> price >> qty;
            modifyOrder(id, price, qty);
        }

        match();
        logMetrics();
    }

    ~MarketDataProcessor() {
        logFile.close();
    }
};

int main() {
    MarketDataProcessor mdp;
    ifstream file("data.txt");

    string action;

    while (file >> action) {
        mdp.process(action, file);
    }

    file.close();
    return 0;
}