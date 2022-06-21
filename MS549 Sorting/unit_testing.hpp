﻿#ifndef MS549_TESTING
#define MS549_TESTING

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <chrono>

namespace unit_testing {
	using namespace std;

	/// <summary>
	/// A implimentation of a basic unit testing framework.
	/// </summary>
	class UnitTest {
	public:
		/// <summary>
		/// A object representing the result of a unit test. 
		/// </summary>
		class TestResult {
		public:
			/// <summary>
			/// Name of the test which the result was generated by.
			/// </summary>
			wstring name;

			/// <summary>
			/// If the test passed.
			/// </summary>
			bool passed;

			/// <summary>
			/// How long the test took to run in microseconds.
			/// </summary>
			chrono::microseconds durration;

			/// <summary>
			/// Create an instance of TestResult
			/// </summary>
			/// <param name="name">Name of the test generating the result.</param>
			/// <param name="passed">If the test passed.</param>
			TestResult(wstring name, bool passed, chrono::microseconds durration = chrono::microseconds(0)) {
				this->name = name;
				this->passed = passed;
				this->durration = durration;
			}
		};

	private:
		/// <summary>
		/// Name of the UnitTest instance.
		/// </summary>
		wstring name;

		/// <summary>
		/// Vector containing results of the UnitTest instance.
		/// </summary>
		vector<TestResult> results;

		/// <summary>
		/// The stream to which logs are sent.
		/// </summary>
		wostream& log_stream = wcout;

		/// <summary>
		/// Log the result of a test.
		/// </summary>
		void log_test(wstring testName, bool testPassed, chrono::microseconds testDurration = chrono::microseconds(0)) {
			results.push_back(TestResult(testName, testPassed, testDurration));
		}

	public:
		/// <summary>
		/// Construct and instance of unit test with a given name.
		/// </summary>
		/// <param name="name">Name of the UnitTest instance.</param>
		UnitTest(wstring name = L"Unit Test", wostream& log_stream = wcout) {
			this->name = name;
		}

		/// <summary>
		/// Log a value to the specified loging stream given a optional test name.
		/// </summary>
		/// <param name="message">Message to be logged.</param>
		/// <param name="testName">Name of the test log is sent from (if applicalbe)</param>
		void log(wstring message, wstring testName = L"") {
			this->log_stream << L"[" << this->name << L"]" << (testName.empty() ? L"" : (L"(" + testName + L")")) << L": " << message << endl;
		}

		/// <summary>
		/// Assert that the first value provided is the same as the second expected value.
		/// </summary>
		/// <typeparam name="T">Type of the value being compared.</typeparam>
		/// <param name="name">Name of the test being performed.</param>
		/// <param name="value">Value being compared to the expected value.</param>
		/// <param name="expected">What the value provided is expected to be.</param>
		template <typename T> void assert(string name, T value, T expected) {
			this->log_test(name, value == expected);
		}

		/// <summary>
		/// Run a test asserting that the value return by the provided function is equal to the expected value.
		/// </summary>
		/// <typeparam name="T">Type of the value being compared.</typeparam>
		/// <param name="name">Name of the test being performed.</param>
		/// <param name="test">Function which returns a value.</param>
		/// <param name="expected">What the value returned by the function is expected to be.</param>
		template <typename T> void assert(wstring name, function<T()> test, T expected) {
			try {
				//if printProgress is true print that the test is running
				this->log_stream << L"[Running Test]: " << name << L"\n";

				//run the function and get the result & measure how long it takes
				auto start = chrono::high_resolution_clock::now();
				T result = test();
				auto end = chrono::high_resolution_clock::now();

				//if printProgress is true print spacer
				this->log_stream << L"\n";

				//get execution durration
				auto durration = chrono::duration_cast<chrono::microseconds>(end - start);

				//log the result
				this->log_test(name, result == expected, durration);
			}
			catch (const std::exception& e) {
				this->log(L"Unhandled Exception: " + *e.what(), name);
				results.push_back(TestResult(L"[EXCEPTION] " + name, false));
			}
		}

		/// <summary>
		/// Checks all performed tests to see if any failed, if all passed true is returned, otherwise false.
		/// </summary>
		/// <returns>If all tests passed.</returns>
		bool passed() {
			for (auto result : this->results) {
				if (!result.passed) return false;
			}

			return true;
		}

		/// <summary>
		/// Log the results of the unit test to the specified stream.
		/// </summary>
		void log_results(wostream& stream = wcout) {
			stream << L"+-" << wstring(this->name.length(), L'-') << L"---------+" << endl;
			stream << L"| " << this->name << L" Results |" << endl;
			stream << L"+-" << wstring(this->name.length(), L'-') << L"---------+" << endl;
			stream << L"|" << endl;

			//log the result of each test
			for (int i = 0; i < this->results.size(); i++) {
				auto result = this->results[i];

				//log test result (pass/fail)
				stream << L"| (#" << (i + 1) << L")[" << (result.passed ? L"PASSED" : L"FAILED") << L"]: " << result.name << endl;

				//log test durration if not 0
				if (result.durration != chrono::microseconds(0)) stream << L"|   <> Test took " << result.durration.count() << L"μs <>" << endl;

				stream << L"|" << endl;
			}

			//get number of tests, passed tests, and durration of all tests combined
			int totalTests = this->results.size();
			int totalPassedTests = 0;
			chrono::microseconds totalDurration = chrono::microseconds(0);

			for (auto result : this->results) {
				if (result.passed) totalPassedTests += 1;
				totalDurration += result.durration;
			}

			stream << L"+\\" << endl;
			stream << L"|| <> RESULT <>" << endl;
			stream << L"|| - " << (this->passed() ? "TEST PASSED" : "TEST FAILED") << endl;
			stream << L"|| - " << totalPassedTests << L"/" << totalTests << L" Tests Passed" << endl;
			stream << L"|| - " << L"Tests took " << totalDurration.count() << L"μs in total" << endl;
			stream << L"+/" << endl;
		}
	};
}

#endif