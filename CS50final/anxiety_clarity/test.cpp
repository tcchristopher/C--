#include <iostream>
#include "action_step.h"
#include "category.h"
#include "anxiety_item.h"
#include "anxiety_list.h"


int main() {
    // Testing ActionStep
    std::cout << "=== Testing ActionStep ===\n\n";

    // Create an action step
    ActionStep step("Update my CV");

    // Test initial state
    std::cout << "Step text: " << step.text() << '\n';
    std::cout << "Is complete? " << (step.is_complete() ? "yes" : "no") << '\n';

    // Complete the step
    step.complete();
    std::cout << "\nAfter completing:\n";
    std::cout << "Is complete? " << (step.is_complete() ? "yes" : "no") << '\n';

    // Uncomplete the step (undo in the event of error)
    step.uncomplete();
    std::cout << "\nAfter uncompleting:\n";
    std::cout << "Is complete? " << (step.is_complete() ? "yes" : "no") << '\n';

    // Status Update
    std::cout << "\nActionStep works!\n";


    // Testing Category Interactivity
    std::cout << "\n=== Testing Category ===\n";
    Category cat = Category::INCOME;
    std::cout << "Category: " << category_to_string(cat) << '\n';
    Category cat2 = string_to_category("HOUSING");
    std::cout << "From string: " << category_to_string(cat2) << '\n';
    
    // Status Update
    std::cout << "\nCategory enum works!\n";


    // Testing AnxietyItem
    std::cout << "\n=== Testing AnxietyItem ===\n\n";

    // Create an anxiety
    AnxietyItem anxiety("No job, savings running out", Category::INCOME, 8, 10);

    // Test basic properties
    std::cout << "Test: " << anxiety.text() << '\n';
    std::cout << "Category: " << category_to_string(anxiety.category()) << '\n';
    std::cout << "Difficulty: " << anxiety.difficulty() << "/10\n";
    std::cout << "Impact: " << anxiety.impact() << "/10\n";
    std::cout << "Priority: " << anxiety.priority() << '\n';
    std::cout << "Resolved? " << (anxiety.is_resolved() ? "yes" : "no") << '\n';

    // Add some steps
    std::cout << "\n--- Adding steps ---\n";
    anxiety.add_step("Update CV");
    anxiety.add_step("Apply to 5 jobs");
    anxiety.add_step("Network on LinkedIn");
    std::cout << "Total steps: " << anxiety.total_steps() << '\n';
    std::cout << "Completed: " << anxiety.completed_steps() << '\n';
    std::cout << "Progress: " << anxiety.progress_percent() << "%\n";

    // Complete a step
    std::cout << "\n--- Completing step 0---\n";
    anxiety.complete_step(0);
    std::cout << "Completed: " << anxiety.completed_steps() << '\n';
    std::cout << "Progress: " << anxiety.progress_percent() << "%\n";

    // Test uncomplete (undo)
    std::cout << "\n--- Uncompleting step 0 ---\n";
    anxiety.uncomplete_step(0);
    std::cout << "Completed: " << anxiety.completed_steps() << "\n";

    // Test editing
    std::cout << "\n--- Testing edit functions ---\n";
    anxiety.set_text("Updated anxiety text");
    std::cout << "New text: " << anxiety.text() << "\n";

    anxiety.set_difficulty(5);
    std::cout << "New difficulty: " << anxiety.difficulty() << '\n';
    std::cout << "New priority: " << anxiety.priority() << '\n';

    // Test remove step
    std::cout << "\n--- Removing step 1 ---\n";
    std::cout << "Steps before: " << anxiety.total_steps() << '\n';
    anxiety.remove_step(1);
    std::cout << "Steps after: " << anxiety.total_steps() << '\n';

    // Resolve the anxiety
    std::cout << "\n--- Resolving anxiety ---\n";
    anxiety.resolve();
    std::cout << "Resolved? " << (anxiety.is_resolved() ? "yes" : "no") << '\n';

    // Status Update
    std::cout << "\nAnxietyItem class works!\n";


    // Testing AnxietyList
    std::cout << "\n=== Testing AnxietyList ===\n\n";

    AnxietyList list;

    // Add some anxieties
    AnxietyItem a1("No income", Category::INCOME, 8, 10);
    a1.add_step("Update CV");
    a1.add_step("Apply to jobs");

    AnxietyItem a2("Lease ending", Category::HOUSING, 7, 9);
    a2.add_step("Research areas");

    AnxietyItem a3("Dad's birthday", Category::FAMILY, 4, 6);
    a3.add_step("Buy gift");
    a3.complete_step(0);
    a3.resolve();

    list.add(a1);
    list.add(a2);
    list.add(a3);

    std::cout << "Total items: " << list.size() << '\n';
    std::cout << "Active: " << list.active_count() << '\n';
    std::cout << "Resolved: " << list.resolved_count() << '\n';

    // Test sorting
    std::cout << "\n-- Before sorting---\n";
    for (int i = 0; i < list.size(); i++) {
        std::cout   << i << ": " << list.get(i).text()
                    << " (priority: " << list.get(i).priority() << ")\n";
    }

    list.sort_by_priority();

    std::cout << "\n--- After sorting ---\n";
    for (int i = 0; i < list.size(); i++) {
        std::cout   << i << ": " << list.get(i).text()
                    << " (priority: " << list.get(i).priority() << ")\n";
    }

    // Test save
    std::cout << "\n--- Testing save/load ---\n";
    if (list.save("test_data.txt")) {
        std::cout << "Saved successfully!\n";
    }

    // Test load into new list
    AnxietyList list2;
    if (list2.load("test_data.txt")) {
        std::cout << "Loaded successfully!\n";
        std::cout << "Loaded " << list2.size() << " items\n";
    }

    // Test list remove
    std::cout << "\n--- Testing remove ---\n";
    std::cout << "Items before: " << list.size() << " items\n";
    list.remove(0);
    std::cout << "Items after: " << list.size() << " items\n";

    // Status Update
    std::cout << "\nAnxietyList class works!\n";
    
    return 0;
}
