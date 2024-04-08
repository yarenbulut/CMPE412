#include <iostream> // For input and output operations
#include <vector> // For dynamic array implementation
#include <random> // For random number generation
#include <algorithm> // For algorithms like shuffle and remove_if

using namespace std;

// Definition of constant variables
const int totalYears = 200; // Total simulation years
const int minAgeQuaestor = 30; // Minimum age limit for quaestor
const int minAgeAedile = 36; // Minimum age limit for aedile
const int minAgePraetor = 39; // Minimum age for limit praetor
const int minAgeConsul = 42; // Minimum age limit for consul
const int minServiceAedile = 2; // Minimum service limit for aedile
const int minServicePraetor = 2; // Minimum service years limit for praetor
const int minServiceConsul = 2; // Minimum service years limit consul
const int yearsBetweenConsulReelection = 10; // Years between Consul reelections
const int quaestoresPerYear = 20; // Number of quaestors per year
const int aedilesPerYear = 10; // Total aediles quota per year
const int praetorsPerYear = 8; // Total praetors quota per year
const int consulsPerYear = 2; // Total consuls quota per year
const int startingPSI = 100; // Starting PSI value
const int unfilledPositionPenalty = -5; // Penalty for unfilled positions
const int consecutiveConsulReelectionPenalty = -10; // Penalty for consecutive Consul reelections
const int annualInfluxMean = 15; // Influx mean value per year
const int annualInfluxStdDev = 5; // Influx standard deviation value per year
const int lifeExpectancyMean = 55; // Life expectancy mean value
const int lifeExpectancyStdDev = 10; // Life expectancy standard deviation value

// Politician class
class Politician {
public:
    Politician(int age) : age(age) {}
    int getAge() const { return age; }
private:
    int age;
};

// Simulation class - consturctor
class Simulation {
public:
    Simulation() : psi(startingPSI), year(0) {
        politicians.reserve(quaestoresPerYear + aedilesPerYear + praetorsPerYear + consulsPerYear);
        initializePoliticians();
    }

    // Simulate a year
    void simulateYear(mt19937& gen, normal_distribution<>& lifeExpectancyDist) {
        shufflePoliticians(gen);
        updatePoliticiansAge();
        removeDeceasedPoliticians(lifeExpectancyDist, gen);
        calculateUnfilledPositionPenalty();
        calculateConsecutiveConsulReelectionPenalty();
    }

    // Run the simulation
    void run() {
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> influxDist(annualInfluxMean, annualInfluxStdDev);
        normal_distribution<> lifeExpectancyDist(lifeExpectancyMean, lifeExpectancyStdDev);

        for (year = 0; year < totalYears; ++year) {
            int influx = static_cast<int>(influxDist(gen));
            addPoliticians(influx);
            simulateYear(gen, lifeExpectancyDist);
        }
    }

    // Get the final PSI value
    int getFinalPSI() const { return psi; }

    // Calculate and display age distribution
    void calculateAgeDistribution() {
        vector<int> quaestorAges;
        vector<int> aedileAges;
        vector<int> praetorAges;
        vector<int> consulAges;

        collectAgeData(quaestorAges, aedileAges, praetorAges, consulAges);

        displayAgeDistribution(quaestorAges, aedileAges, praetorAges, consulAges);
    }

private:
    int psi; // Political Stability Index
    int year; // Current simulation year
    vector<Politician> politicians; // Vector to store politicians

    // Count politicians within a certain age range
    int countPoliticians(int minAge, int maxAge) {
        return count_if(politicians.begin(), politicians.end(),
            [minAge, maxAge](const Politician& p) { return p.getAge() >= minAge && p.getAge() < maxAge; });
    }

    // Initialize politicians
    void initializePoliticians() {
        for (int i = 0; i < quaestoresPerYear; ++i) {
            politicians.emplace_back(minAgeQuaestor);
        }
        for (int i = 0; i < aedilesPerYear; ++i) {
            politicians.emplace_back(minAgeAedile);
        }
        for (int i = 0; i < praetorsPerYear; ++i) {
            politicians.emplace_back(minAgePraetor);
        }
        for (int i = 0; i < consulsPerYear; ++i) {
            politicians.emplace_back(minAgeConsul);
        }
    }

    // Shuffle politicians
    void shufflePoliticians(mt19937& gen) {
        shuffle(politicians.begin(), politicians.end(), gen);
    }

    // Update politicians' age
    void updatePoliticiansAge() {
        for (auto& politician : politicians) {
            politician = Politician(politician.getAge() + 1);
        }
    }

    // Remove deceased politicians
    void removeDeceasedPoliticians(normal_distribution<>& lifeExpectancyDist, mt19937& gen) {
        politicians.erase(remove_if(politicians.begin(), politicians.end(),
            [&lifeExpectancyDist, &gen](const Politician& p) { return p.getAge() > lifeExpectancyDist(gen); }), politicians.end());
    }

    // Calculate penalty for unfilled positions
    void calculateUnfilledPositionPenalty() {
        psi += unfilledPositionPenalty * (quaestoresPerYear - countPoliticians(minAgeQuaestor, minAgeAedile)) +
            unfilledPositionPenalty * (aedilesPerYear - countPoliticians(minAgeAedile, minAgePraetor)) +
            unfilledPositionPenalty * (praetorsPerYear - countPoliticians(minAgePraetor, minAgeConsul)) +
            unfilledPositionPenalty * (consulsPerYear - countPoliticians(minAgeConsul, lifeExpectancyMean));
    }

    // Calculate penalty for consecutive Consul reelections
    void calculateConsecutiveConsulReelectionPenalty() {
        if (year % yearsBetweenConsulReelection == 0) {
            psi += consecutiveConsulReelectionPenalty * (consulsPerYear - countPoliticians(minAgeConsul, lifeExpectancyMean));
        }
    }

    // Add politicians based on influx
    void addPoliticians(int influx) {
        for (int i = 0; i < influx; ++i) {
            politicians.emplace_back(minAgeQuaestor);
        }
    }

    // Collect age data
    void collectAgeData(vector<int>& quaestorAges, vector<int>& aedileAges, vector<int>& praetorAges, vector<int>& consulAges) {
        for (const auto& politician : politicians) {
            int age = politician.getAge();
            if (age >= minAgeQuaestor && age < minAgeAedile) {
                quaestorAges.push_back(age);
            }
            else if (age >= minAgeAedile && age < minAgePraetor) {
                aedileAges.push_back(age);
            }
            else if (age >= minAgePraetor && age < minAgeConsul) {
                praetorAges.push_back(age);
            }
            else if (age >= minAgeConsul) {
                consulAges.push_back(age);
            }
        }
    }

    // Display age distribution
    void displayAgeDistribution(const vector<int>& quaestorAges, const vector<int>& aedileAges, const vector<int>& praetorAges, const vector<int>& consulAges) {
        cout << "Age Distribution:" << endl;
        cout << "Quaestor: Count=" << calculateSummary(quaestorAges).first << ", Average Age=" << calculateSummary(quaestorAges).second << endl;
        cout << "Aedile: Count=" << calculateSummary(aedileAges).first << ", Average Age=" << calculateSummary(aedileAges).second << endl;
        cout << "Praetor: Count=" << calculateSummary(praetorAges).first << ", Average Age=" << calculateSummary(praetorAges).second << endl;
        cout << "Consul: Count=" << calculateSummary(consulAges).first << ", Average Age=" << calculateSummary(consulAges).second << endl;
    }

    // Calculate summary statistics
    pair<unsigned long long, double> calculateSummary(const vector<int>& ages) {
        if (ages.empty()) {
            return make_pair(0ULL, 0.0);
        }

        unsigned long long totalAges = 0;
        for (int age : ages) {
            totalAges += age;
        }
        double averageAge = static_cast<double>(totalAges) / ages.size();

        return make_pair(static_cast<unsigned long long>(ages.size()), averageAge);
    }
};

// Main function
int main() {
    Simulation simulation;
    simulation.run();

    // Display the final PSI value
    cout << "End-of-Simulation PSI: " << simulation.getFinalPSI() << endl;

    // Display the annual fill rate
    cout << "Annual Fill Rate:" << endl;
    cout << "Quaestor: " << static_cast<double>(quaestoresPerYear) / totalYears * 100 << "%" << endl;
    cout << "Aedile: " << static_cast<double>(aedilesPerYear) / totalYears * 100 << "%" << endl;
    cout << "Praetor: " << static_cast<double>(praetorsPerYear) / totalYears * 100 << "%" << endl;
    cout << "Consul: " << static_cast<double>(consulsPerYear) / totalYears * 100 << "%" << endl;

    // Calculate and display the age distribution
    simulation.calculateAgeDistribution();

    return 0;
}