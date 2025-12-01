#include <iostream>
#include "action_step.h"

int main() {
    // Create an action step
    ActionStep step("Update my CV");

    // Test initial state
    std::cout << "Step text: " << step.text() << '\n';
    std::cout << "Is complete? " << (step.is_complete() ? "yes" : "no") << '\n';

    // Complete the step
    step.complete();

    // Test after completion
    std::cout << "After completing:\n";
    std::cout << "Is complete? " << (step.is_complete() ? "yes" : "no") << '\n';

}
