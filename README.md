# **Roman Empire Political Hierarchy Simulation**

## **Overview**
This project simulates the political hierarchy of the Roman Empire over 200 years, managing various political positions such as **Quaestors, Aediles, Praetors, and Consuls**. The simulation tracks the **Political Stability Index (PSI)** based on different penalties and incentives and monitors age distribution among politicians.

---

## 📌 **Features**
- **Political System Management**: Handles the appointment and aging of Quaestors, Aediles, Praetors, and Consuls.
- **Stress Testing**: Simulates system stress with random politician influx and life expectancy.
- **Penalty Calculation**: Applies penalties for unfilled positions and consecutive Consul reelections.
- **Resource Monitoring**: Tracks and displays age distribution for different political positions.

---

## ⚙️ **Code Description**
### **🔢 Constants**
- **totalYears**: Total simulation years (200).
- **minAgeQuaestor**: Minimum age for Quaestors (30).
- **minAgeAedile**: Minimum age for Aediles (36).
- **minAgePraetor**: Minimum age for Praetors (39).
- **minAgeConsul**: Minimum age for Consuls (42).
- **minServiceAedile**: Minimum service years for Aediles (2).
- **minServicePraetor**: Minimum service years for Praetors (2).
- **minServiceConsul**: Minimum service years for Consuls (2).
- **yearsBetweenConsulReelection**: Years between Consul reelections (10).
- **quaestoresPerYear**: Number of Quaestors per year (20).
- **aedilesPerYear**: Number of Aediles per year (10).
- **praetorsPerYear**: Number of Praetors per year (8).
- **consulsPerYear**: Number of Consuls per year (2).
- **startingPSI**: Starting PSI value (100).
- **unfilledPositionPenalty**: Penalty for unfilled positions (-5).
- **consecutiveConsulReelectionPenalty**: Penalty for consecutive Consul reelections (-10).
- **annualInfluxMean**: Mean value for annual influx (15).
- **annualInfluxStdDev**: Standard deviation for annual influx (5).
- **lifeExpectancyMean**: Mean life expectancy (55).
- **lifeExpectancyStdDev**: Standard deviation for life expectancy (10).

### **🧑‍🏫 Classes**
#### **👤 Politician**
- **Constructor**: Initializes a politician with a given age.
- **Methods**:
  - `getAge()`: Returns the age of the politician.

#### **🏛️ Simulation**
- **Constructor**: Initializes the simulation with starting PSI and year.
- **Methods**:
  - `simulateYear(mt19937& gen, normal_distribution<>& lifeExpectancyDist)`: Simulates one year of the political system.
  - `run()`: Runs the simulation for the total number of years.
  - `getFinalPSI()`: Returns the final PSI value after simulation.
  - `calculateAgeDistribution()`: Calculates and displays the age distribution of politicians.

### **🔧 Functions**
- `initializePoliticians()`: Initializes politicians with specified age limits.
- `shufflePoliticians(mt19937& gen)`: Shuffles the list of politicians.
- `updatePoliticiansAge()`: Increases the age of all politicians by one year.
- `removeDeceasedPoliticians(normal_distribution<>& lifeExpectancyDist, mt19937& gen)`: Removes politicians who have exceeded their life expectancy.
- `calculateUnfilledPositionPenalty()`: Calculates and applies the penalty for unfilled positions.
- `calculateConsecutiveConsulReelectionPenalty()`: Calculates and applies the penalty for consecutive Consul reelections.
- `addPoliticians(int influx)`: Adds new politicians based on annual influx.
- `collectAgeData(vector<int>& quaestorAges, vector<int>& aedileAges, vector<int>& praetorAges, vector<int>& consulAges)`: Collects age data for different political positions.
- `displayAgeDistribution(const vector<int>& quaestorAges, const vector<int>& aedileAges, const vector<int>& praetorAges, const vector<int>& consulAges)`: Displays the age distribution of politicians.
- `calculateSummary(const vector<int>& ages)`: Calculates summary statistics (count and average age) for a given age vector.

---

## 🚀 **Usage**
1. **Compile the Code**: Use a C++ compiler to compile the code.
2. **Run the Simulation**: Execute the compiled program to start the simulation.
3. **View Results**: The program will output the final PSI value, annual fill rates, and age distribution of politicians.

---

## 📝 **License**
This project is licensed under the **MIT License** - see the LICENSE file for details.
