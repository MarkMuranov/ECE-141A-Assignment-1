#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <sstream>

namespace ECE141
{
    class Testable
    {
    protected:
        // Make sure this variable gets incremented each time a test is added.
        size_t numberOfTests = 0;

    public:
        Testable() = default;
        virtual ~Testable() = default;

        // Retrieve the name of a specific test.
        virtual std::optional<std::string> getTestName(size_t anIndex) const = 0;

        // Run a specific test.
        virtual bool operator()(const std::string &aName) = 0;

        // Run all tests, returns number of tests passed.
        size_t runAllTests()
        {
            size_t numberOfTestsPassed = 0;
            std::stringstream theOutput;
            for(size_t i = 0; i < numberOfTests; i++)
            {
                if (auto theName = getTestName(i))
                {
                    const bool hasPassed = (*this)(theName.value());
                    if (hasPassed)
                        numberOfTestsPassed++;

                    theOutput << i + 1 << ". " << theName.value() << ": "
                              << (hasPassed ? "PASS" : "FAIL") << "\n";
                }
            }

            if (numberOfTestsPassed == numberOfTests)
                std::cout << "All";
            else
                std::cout << numberOfTestsPassed << " of " << numberOfTests;

            std::cout << " tests passed.\n" << theOutput.str() << "\n";
            return numberOfTestsPassed;
        }

    };

} // namespace ECE141
