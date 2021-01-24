// https://leetcode.com/problems/task-scheduler
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>


int getTaskScheduleTime(std::string tasks, int coolDown) {
    int totalTime = 0;
    std::map<char,int> tasksCount; // keeps track of how many of each task type we have
    std::vector<char> tasksOrder;  // keeps each kind of task ordered smallest to largest.

    // build up counts of each task type in tasksCount as well as  make the tasksOrder list.
    for (char const &task: tasks) {
        if (!tasksCount.count(task)) {
            tasksCount[task] = 0;
            tasksOrder.push_back(task);
        }
        tasksCount[task] = tasksCount[task] + 1;
    }

    // sorts the tasksOrders list smallest to largest.
    std::sort(tasksOrder.begin(), tasksOrder.end(), [tasksCount](const char & a, const char & b) -> bool {
        return tasksCount.find(a)->second < tasksCount.find(b)->second;
    });

    // while we still have tasks to do
    while (tasksOrder.size() != 0) {
        char headTask = tasksOrder.back();
        tasksOrder.pop_back();

        // and the current headTask has tasks left
        while (tasksCount[headTask] != 0) {
            // execute the first head task
            tasksCount[headTask] = tasksCount[headTask] - 1;
            ++totalTime;

            int tasksOrderSize = tasksOrder.size();
            int coolStep = 1;

            // achieve idle time by executing other tasks or just being idle.
            while (coolStep <= coolDown)
            {
                // we might have tasks to do so try to execute them
                if (tasksOrderSize != 0) {
                    char & nextTask = tasksOrder[tasksOrderSize == 1 ? 0 : tasksOrderSize - coolStep];
                    // we've exhausted all nextTasks, so remove it from tasksOrder.
                    if (tasksCount[nextTask] == 0) {
                        tasksOrder.pop_back();
                        tasksOrderSize = tasksOrder.size();

                        // if that was the last tasks then break from this while loop.
                        // we're done at this point.
                        if (tasksOrderSize == 0)
                            break;

                        continue;
                    }

                    // if we aren't about to step outside the bounds of our
                    // tasksOrder list, execute nextTask
                    if (coolStep <= tasksOrderSize)
                        tasksCount[nextTask] = tasksCount[nextTask] - 1;
                }
                // always accumulate total time and a coolDown step.
                // this happens when we actually run our next task or if we are just
                // staying idle.
                ++totalTime;
                ++coolStep;
            }
        }
    }

    return totalTime;
}

int taskSchedulerMain()
{
    std::cout << "[CHALLENGE] tasks [A,A,A,B,B,B] where n=2 takes 8 unit of time." << std::endl;
    assert(getTaskScheduleTime(std::string("AAABBB"), 2) == 8);
    std::cout << "[CHALLENGE] tasks [A,A,A,B,B,B] where n=0 takes 6 unit of time." << std::endl;
    assert(getTaskScheduleTime(std::string("AAABBB"), 0) == 6);
    std::cout << "[CHALLENGE] tasks [A,A,A,A,A,A,B,C,D,E,F,G] where n=2 takes 16 unit of time." << std::endl;
    assert(getTaskScheduleTime(std::string("AAAAAABCDEFG"), 2) == 16);
    return 0;
}

int main()
{
    taskSchedulerMain();
    return 0;
}
