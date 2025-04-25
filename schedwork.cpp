#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftsPerWorker, size_t day, size_t slot);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t n = avail.size(); // num days
    size_t k = avail[0].size(); // num workers

    sched = DailySchedule(n, std::vector<Worker_T>(dailyNeed, INVALID_ID));

    std::vector<size_t> shiftsPerWorker(k, 0);

    return schedHelper(avail, dailyNeed, maxShifts, sched, shiftsPerWorker, 0, 0);

}

// recursive helper
bool schedHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftsPerWorker, size_t day, size_t slot) {
    size_t n = avail.size();
    size_t k = avail[0].size();

    // all days schedeuled
    if (day == n){
      return true;
    }

    for (size_t worker = 0; worker < k; ++worker) {
      if(avail[day][worker] && shiftsPerWorker[worker] < maxShifts && find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()) {
        sched[day][slot] = worker;
        shiftsPerWorker[worker]++;

        if (slot + 1 == dailyNeed){
          if (schedHelper(avail, dailyNeed, maxShifts, sched, shiftsPerWorker, day + 1, 0)){
            return true;
          }
        }
        else {
          if(schedHelper(avail, dailyNeed, maxShifts, sched, shiftsPerWorker, day, slot + 1)){
            return true;
          }
        }

        // backtrack
        sched[day][slot] = INVALID_ID;
        shiftsPerWorker[worker]--;
      }
    }

    // if no valid worker can be assgined
    return false;
}

