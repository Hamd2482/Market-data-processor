# Market Data Processor (C++ + Streamlit Dashboard)

## Overview

A high-performance market data processing system simulating real-time order flow and order book updates.

## Features

* Event-driven architecture (ADD / CANCEL / MODIFY)
* Order book management using efficient data structures
* Matching logic implementation
* Real-time computation of:

  * Best Bid / Ask
  * Spread
  * Mid Price
* Metrics logging to CSV

## Dashboard

Interactive dashboard built using Streamlit:

* Bid vs Ask visualization
* Spread analysis
* Real-time metrics

## Tech Stack

* C++
* Python (Streamlit, Pandas, Matplotlib)

## How to Run

### C++ Engine

```bash
g++ -std=c++17 mdp.cpp -o mdp
./mdp
```

### Dashboard

```bash
pip install -r requirements.txt
streamlit run app.py
```

## Learnings

* Market microstructure and order flow
* Event-driven system design
* Efficient data handling in C++
* Visualization of trading metrics

## Author

Hamd
